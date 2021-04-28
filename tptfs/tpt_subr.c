/*-
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software donated to Berkeley by
 * Jan-Simon Pendry.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)tpt_subr.c	8.7 (Berkeley) 5/14/95
 *
 * $FreeBSD$
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/lock.h>
#include <sys/rwlock.h>
#include <sys/malloc.h>
#include <sys/mount.h>
#include <sys/proc.h>
#include <sys/vnode.h>

#include "tpt.h"

/*
 * Null layer cache:
 * Each cache entry holds a reference to the lower vnode
 * along with a pointer to the alias vnode.  When an
 * entry is added the lower vnode is VREF'd.  When the
 * alias is removed the lower vnode is vrele'd.
 */

#define	NULL_NHASH(vp) (&tpt_node_hashtbl[vfs_hash_index(vp) & tpt_hash_mask])

static LIST_HEAD(tpt_node_hashhead, tpt_node) *tpt_node_hashtbl;
static struct rwlock tpt_hash_lock;
static u_long tpt_hash_mask;

static MALLOC_DEFINE(M_NULLFSHASH, "tptfs_hash", "NULLFS hash table");
MALLOC_DEFINE(M_NULLFSNODE, "tptfs_node", "NULLFS vnode private part");

static struct vnode * tpt_hashins(struct mount *, struct tpt_node *);

/*
 * Initialise cache headers
 */
int
tptfs_init(vfsp)
	struct vfsconf *vfsp;
{

	tpt_node_hashtbl = hashinit(desiredvnodes, M_NULLFSHASH,
	    &tpt_hash_mask);
	rw_init(&tpt_hash_lock, "nullhs");
	return (0);
}

int
tptfs_uninit(vfsp)
	struct vfsconf *vfsp;
{

	rw_destroy(&tpt_hash_lock);
	hashdestroy(tpt_node_hashtbl, M_NULLFSHASH, tpt_hash_mask);
	return (0);
}

/*
 * Return a VREF'ed alias for lower vnode if already exists, else 0.
 * Lower vnode should be locked on entry and will be left locked on exit.
 */
struct vnode *
tpt_hashget(mp, lowervp)
	struct mount *mp;
	struct vnode *lowervp;
{
	struct tpt_node_hashhead *hd;
	struct tpt_node *a;
	struct vnode *vp;

	ASSERT_VOP_LOCKED(lowervp, "tpt_hashget");

	/*
	 * Find hash base, and then search the (two-way) linked
	 * list looking for a tpt_node structure which is referencing
	 * the lower vnode.  If found, the increment the tpt_node
	 * reference count (but NOT the lower vnode's VREF counter).
	 */
	hd = NULL_NHASH(lowervp);
	if (LIST_EMPTY(hd))
		return (NULLVP);
	rw_rlock(&tpt_hash_lock);
	LIST_FOREACH(a, hd, tpt_hash) {
		if (a->tpt_lowervp == lowervp && NULLTOV(a)->v_mount == mp) {
			/*
			 * Since we have the lower node locked the tptfs
			 * node can not be in the process of recycling.  If
			 * it had been recycled before we grabed the lower
			 * lock it would not have been found on the hash.
			 */
			vp = NULLTOV(a);
			vref(vp);
			rw_runlock(&tpt_hash_lock);
			return (vp);
		}
	}
	rw_runlock(&tpt_hash_lock);
	return (NULLVP);
}

/*
 * Act like tpt_hashget, but add passed tpt_node to hash if no existing
 * node found.
 */
static struct vnode *
tpt_hashins(mp, xp)
	struct mount *mp;
	struct tpt_node *xp;
{
	struct tpt_node_hashhead *hd;
	struct tpt_node *oxp;
	struct vnode *ovp;

	hd = NULL_NHASH(xp->tpt_lowervp);
	rw_wlock(&tpt_hash_lock);
	LIST_FOREACH(oxp, hd, tpt_hash) {
		if (oxp->tpt_lowervp == xp->tpt_lowervp &&
		    NULLTOV(oxp)->v_mount == mp) {
			/*
			 * See tpt_hashget for a description of this
			 * operation.
			 */
			ovp = NULLTOV(oxp);
			vref(ovp);
			rw_wunlock(&tpt_hash_lock);
			return (ovp);
		}
	}
	LIST_INSERT_HEAD(hd, xp, tpt_hash);
	rw_wunlock(&tpt_hash_lock);
	return (NULLVP);
}

static void
tpt_destroy_proto(struct vnode *vp, void *xp)
{

	lockmgr(&vp->v_lock, LK_EXCLUSIVE, NULL);
	VI_LOCK(vp);
	vp->v_data = NULL;
	vp->v_vnlock = &vp->v_lock;
	vp->v_op = &dead_vnodeops;
	VI_UNLOCK(vp);
	vgone(vp);
	vput(vp);
	free(xp, M_NULLFSNODE);
}

static void
tpt_insmntque_dtr(struct vnode *vp, void *xp)
{

	vput(((struct tpt_node *)xp)->tpt_lowervp);
	tpt_destroy_proto(vp, xp);
}

/*
 * Make a new or get existing tptfs node.
 * Vp is the alias vnode, lowervp is the lower vnode.
 * 
 * The lowervp assumed to be locked and having "spare" reference. This routine
 * vrele lowervp if tptfs node was taken from hash. Otherwise it "transfers"
 * the caller's "spare" reference to created tptfs vnode.
 */
int
tpt_nodeget(mp, lowervp, vpp)
	struct mount *mp;
	struct vnode *lowervp;
	struct vnode **vpp;
{
	struct tpt_node *xp;
	struct vnode *vp;
	int error;

	ASSERT_VOP_LOCKED(lowervp, "lowervp");
	VNPASS(lowervp->v_usecount > 0, lowervp);

	/* Lookup the hash firstly. */
	*vpp = tpt_hashget(mp, lowervp);
	if (*vpp != NULL) {
		vrele(lowervp);
		return (0);
	}

	/*
	 * The insmntque1() call below requires the exclusive lock on
	 * the tptfs vnode.  Upgrade the lock now if hash failed to
	 * provide ready to use vnode.
	 */
	if (VOP_ISLOCKED(lowervp) != LK_EXCLUSIVE) {
		vn_lock(lowervp, LK_UPGRADE | LK_RETRY);
		if (VN_IS_DOOMED(lowervp)) {
			vput(lowervp);
			return (ENOENT);
		}
	}

	/*
	 * We do not serialize vnode creation, instead we will check for
	 * duplicates later, when adding new vnode to hash.
	 * Note that duplicate can only appear in hash if the lowervp is
	 * locked LK_SHARED.
	 */
	xp = malloc(sizeof(struct tpt_node), M_NULLFSNODE, M_WAITOK);

	error = getnewvnode("tptfs", mp, &tpt_vnodeops, &vp);
	if (error) {
		vput(lowervp);
		free(xp, M_NULLFSNODE);
		return (error);
	}

	xp->tpt_vnode = vp;
	xp->tpt_lowervp = lowervp;
	xp->tpt_flags = 0;
	vp->v_type = lowervp->v_type;
	vp->v_data = xp;
	vp->v_vnlock = lowervp->v_vnlock;
	error = insmntque1(vp, mp, tpt_insmntque_dtr, xp);
	if (error != 0)
		return (error);
	if (lowervp == MOUNTTONULLMOUNT(mp)->nullm_lowerrootvp)
		vp->v_vflag |= VV_ROOT;

	/*
	 * We might miss the case where lower vnode sets VIRF_PGREAD
	 * some time after construction, which is typical case.
	 * tpt_open rechecks.
	 */
	if ((vn_irflag_read(lowervp) & VIRF_PGREAD) != 0) {
		MPASS(lowervp->v_object != NULL);
		if ((vn_irflag_read(vp) & VIRF_PGREAD) == 0) {
			if (vp->v_object == NULL)
				vp->v_object = lowervp->v_object;
			else
				MPASS(vp->v_object == lowervp->v_object);
			vn_irflag_set_cond(vp, VIRF_PGREAD);
		} else {
			MPASS(vp->v_object != NULL);
		}
	}

	/*
	 * Atomically insert our new node into the hash or vget existing 
	 * if someone else has beaten us to it.
	 */
	*vpp = tpt_hashins(mp, xp);
	if (*vpp != NULL) {
		vrele(lowervp);
		vp->v_object = NULL;	/* in case VIRF_PGREAD set it */
		tpt_destroy_proto(vp, xp);
		return (0);
	}
	*vpp = vp;

	return (0);
}

/*
 * Remove node from hash.
 */
void
tpt_hashrem(xp)
	struct tpt_node *xp;
{

	rw_wlock(&tpt_hash_lock);
	LIST_REMOVE(xp, tpt_hash);
	rw_wunlock(&tpt_hash_lock);
}

#ifdef DIAGNOSTIC

struct vnode *
tpt_checkvp(vp, fil, lno)
	struct vnode *vp;
	char *fil;
	int lno;
{
	struct tpt_node *a = VTONULL(vp);

#ifdef notyet
	/*
	 * Can't do this check because vop_reclaim runs
	 * with a funny vop vector.
	 */
	if (vp->v_op != tpt_vnodeop_p) {
		printf ("tpt_checkvp: on non-null-node\n");
		panic("tpt_checkvp");
	}
#endif
	if (a->tpt_lowervp == NULLVP) {
		/* Should never happen */
		panic("tpt_checkvp %p", vp);
	}
	VI_LOCK_FLAGS(a->tpt_lowervp, MTX_DUPOK);
	if (a->tpt_lowervp->v_usecount < 1)
		panic ("null with unref'ed lowervp, vp %p lvp %p",
		    vp, a->tpt_lowervp);
	VI_UNLOCK(a->tpt_lowervp);
#ifdef notyet
	printf("null %x/%d -> %x/%d [%s, %d]\n",
	        NULLTOV(a), vrefcnt(NULLTOV(a)),
		a->tpt_lowervp, vrefcnt(a->tpt_lowervp),
		fil, lno);
#endif
	return (a->tpt_lowervp);
}
#endif
