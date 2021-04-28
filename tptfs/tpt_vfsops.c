/*-
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 1992, 1993, 1995
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
 *	@(#)tpt_vfsops.c	8.2 (Berkeley) 1/21/94
 *
 * @(#)lofs_vfsops.c	1.2 (Berkeley) 6/18/92
 * $FreeBSD$
 */

/*
 * Null Layer
 * (See tpt_vnops.c for a description of what this does.)
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/fcntl.h>
#include <sys/kernel.h>
#include <sys/lock.h>
#include <sys/malloc.h>
#include <sys/mount.h>
#include <sys/namei.h>
#include <sys/proc.h>
#include <sys/vnode.h>
#include <sys/jail.h>

#include <sys/bio.h>
#include <sys/buf.h>
#include <geom/geom.h>
#include <geom/geom_vfs.h>
#include "tpt.h"

static MALLOC_DEFINE(M_TPTFSMNT, "tptfs_mount", "TPTFS mount structure");

static vfs_fhtovp_t	tptfs_fhtovp;
static vfs_mount_t	tptfs_mount;
static vfs_quotactl_t	tptfs_quotactl;
static vfs_root_t	tptfs_root;
static vfs_sync_t	tptfs_sync;
static vfs_statfs_t	tptfs_statfs;
static vfs_unmount_t	tptfs_unmount;
static vfs_vget_t	tptfs_vget;
static vfs_extattrctl_t	tptfs_extattrctl;

static int tpt_mountfs(struct vnode *devvp, struct mount *mp);
static int tpt_compute_sb_data(struct vnode *devvp, struct tptfs *fs);

/*
 * Mount null layer
 */
static int
tptfs_mount(struct mount *mp)
{
	// struct vnode *lowerrootvp;
	// struct vnode *nullm_rootvp;
	struct tpt_mount *xmp;
	// struct tpt_node *nn;
	struct nameidata nd, *ndp = &nd;
	int error, len;
	// bool isvnunlocked;

	char *fspec;
	struct vnode *devvp;
	struct tptfs *fs;
	struct thread *td;

	td = curthread;
	uprintf("tptfs_mount\n");

	if (mp->mnt_flag & MNT_ROOTFS)
		return (EOPNOTSUPP);

	//1. 解析参数
	uprintf("解析参数\n");
	error = vfs_getopt(mp->mnt_optnew, "from", (void **)&fspec, &len);
	if (error || fspec[len - 1] != '\0')
		return (EINVAL);
	uprintf("fspec=%s\n", fspec);

	//2. 根据名字找到对应的vnode并校验
	uprintf("根据名字找到对应的vnode,并校验这个vnode是否一个磁盘设备\n");
	if (fspec == NULL)
		return (EINVAL);
	NDINIT(ndp, LOOKUP, FOLLOW | LOCKLEAF, UIO_SYSSPACE, fspec, td);
	if ((error = namei(ndp)) != 0)
		return (error);
	NDFREE(ndp, NDF_ONLY_PNBUF);
	devvp = ndp->ni_vp;

	if (!vn_isdisk_error(devvp, &error)) {
		vput(devvp);
		return (error);
	}

	//3. TODO 当挂载的不是 / 时, 校验用户的权限
	//4. 挂载
	uprintf("开始执行 tpt_mountfs, 挂载磁盘\n");
	error = tpt_mountfs(devvp, mp);
	if (error) {
		vrele(devvp);
		return error;
	}
	uprintf("结束 tpt_mountfs, 挂载磁盘成功\n");

	xmp = (struct tpt_mount*)(mp->mnt_data);
	fs = xmp->fs;
	vfs_mountedfrom(mp, fspec);

	return (0);
}

static int 
tpt_mountfs(struct vnode *devvp, struct mount *mp) {
	// struct ext2mount *ump;
	struct buf *bp;
	// struct m_ext2fs *fs;
	// struct ext2fs *es;
	// struct cdev *dev = devvp->v_rdev;
	struct g_consumer *cp;
	struct bufobj *bo;
	// struct csum *sump;
	int error;
	int ronly;
	// int i;
	// u_long size;
	// int32_t *lp;
	// int32_t e2fs_maxcontig;
	struct tptfs *tmpfs, *fs;
	struct tpt_mount* tptmp;

	//1. 从 geom 层,获取磁盘的 consumer,默认 sbsize=1k, sector=512b, 不校验磁盘sector大小
	uprintf("从 geom 层获取磁盘的 consumer, begin---------------------\n");
	ronly = vfs_flagopt(mp->mnt_optnew, "ro", NULL, 0);
	g_topology_lock();
	error = g_vfs_open(devvp, &cp, "tptfs", ronly ? 0 : 1);
	g_topology_unlock();
	VOP_UNLOCK(devvp);
	if (error)
		return (error);
	
	//2. 创建 buf 和 bufobj, 从磁盘设备中读取 sb
	uprintf("创建 buf 和 bufobj, 从磁盘设备中读取 sb, begin------------------\n");
	bo = &devvp->v_bufobj;
	bo->bo_private = cp;
	bo->bo_ops = g_vfs_bufops;

	bp = NULL;
	// tmp = NULL;
	if ((error = bread(devvp, 0, 1024, NOCRED, &bp)) != 0) {
		uprintf("bread fail\n");
		goto out;
	}
	tmpfs = (struct tptfs *)bp->b_data;
	//TODO 校验魔数
	uprintf("fs->magic=%x \n", tmpfs->magic); //DONE

	//TODO inode bitmap/block bitmap 数据的填充

	//3. 创建 tpt_mount 和 tptfs 结构, 使用 sb 中的数据填充, 并校验
	uprintf("创建 tpt_mount 和 tptfs 结构, 使用 sb 中的数据填充, begin--------------------- \n");
	tptmp = malloc(sizeof(*tptmp), M_TPTFSMNT, M_WAITOK | M_ZERO);
	fs = malloc(sizeof(struct tptfs), M_TPTFSMNT, M_WAITOK | M_ZERO);
	tptmp->fs = fs;
	bcopy(tmpfs, fs, (u_int)sizeof(struct tptfs));

	uprintf("使用 superblock 中的 metedata 初始化 \n");
	//4. 使用 superblock 中的 metedata 初始化
	if ((error = tpt_compute_sb_data(devvp, fs)))
		goto out;

	mp->mnt_data = tptmp;
	tptmp->nullm_vfs = mp;
	tptmp->nullm_lowerrootvp = devvp;

	return 0;
out:
	if (bp) {
		brelse(bp);
	}
	if (cp != NULL) {
		g_topology_lock();
		g_vfs_close(cp);
		g_topology_unlock();		
	}
	return -1;
}

static int
tpt_compute_sb_data(struct vnode *devvp, struct tptfs *fs) {
	//TODO
	return 0;
}


/*
 * Free reference to null layer
 */
static int
tptfs_unmount(mp, mntflags)
	struct mount *mp;
	int mntflags;
{
	struct tpt_mount *mntdata;
	struct mount *ump;
	int error, flags;

	NULLFSDEBUG("tptfs_unmount: mp = %p\n", (void *)mp);

	if (mntflags & MNT_FORCE)
		flags = FORCECLOSE;
	else
		flags = 0;

	for (;;) {
		/* There is 1 extra root vnode reference (nullm_rootvp). */
		error = vflush(mp, 0, flags, curthread);
		if (error)
			return (error);
		MNT_ILOCK(mp);
		if (mp->mnt_nvnodelistsize == 0) {
			MNT_IUNLOCK(mp);
			break;
		}
		MNT_IUNLOCK(mp);
		if ((mntflags & MNT_FORCE) == 0)
			return (EBUSY);
	}

	/*
	 * Finally, throw away the tpt_mount structure
	 */
	mntdata = mp->mnt_data;
	ump = mntdata->nullm_vfs;
	if ((mntdata->nullm_flags & NULLM_CACHE) != 0) {
		MNT_ILOCK(ump);
		while ((ump->mnt_kern_flag & MNTK_VGONE_UPPER) != 0) {
			ump->mnt_kern_flag |= MNTK_VGONE_WAITER;
			msleep(&ump->mnt_uppers, &ump->mnt_mtx, 0, "vgnupw", 0);
		}
		TAILQ_REMOVE(&ump->mnt_uppers, mp, mnt_upper_link);
		MNT_IUNLOCK(ump);
	}
	vrele(mntdata->nullm_lowerrootvp);
	mp->mnt_data = NULL;
	free(mntdata, M_TPTFSMNT);
	return (0);
}


static int
tptfs_root(mp, flags, vpp)
	struct mount *mp;
	int flags;
	struct vnode **vpp;
{
	struct vnode *vp;
	struct tpt_mount *mntdata;
	int error;

	mntdata = MOUNTTONULLMOUNT(mp);
	NULLFSDEBUG("tptfs_root(mp = %p, vp = %p)\n", mp,
	    mntdata->nullm_lowerrootvp);

	error = vget(mntdata->nullm_lowerrootvp, flags);
	if (error == 0) {
		error = tpt_nodeget(mp, mntdata->nullm_lowerrootvp, &vp);
		if (error == 0) {
			*vpp = vp;
		}
	}
	return (error);
}

static int
tptfs_quotactl(mp, cmd, uid, arg)
	struct mount *mp;
	int cmd;
	uid_t uid;
	void *arg;
{
	return VFS_QUOTACTL(MOUNTTONULLMOUNT(mp)->nullm_vfs, cmd, uid, arg);
}

static int
tptfs_statfs(mp, sbp)
	struct mount *mp;
	struct statfs *sbp;
{
	int error;
	struct statfs *mstat;

	NULLFSDEBUG("tptfs_statfs(mp = %p, vp = %p->%p)\n", (void *)mp,
	    (void *)MOUNTTONULLMOUNT(mp)->nullm_rootvp,
	    (void *)NULLVPTOLOWERVP(MOUNTTONULLMOUNT(mp)->nullm_rootvp));

	mstat = malloc(sizeof(struct statfs), M_STATFS, M_WAITOK | M_ZERO);

	error = VFS_STATFS(MOUNTTONULLMOUNT(mp)->nullm_vfs, mstat);
	if (error) {
		free(mstat, M_STATFS);
		return (error);
	}

	/* now copy across the "interesting" information and fake the rest */
	sbp->f_type = mstat->f_type;
	sbp->f_flags = (sbp->f_flags & (MNT_RDONLY | MNT_NOEXEC | MNT_NOSUID |
	    MNT_UNION | MNT_NOSYMFOLLOW | MNT_AUTOMOUNTED)) |
	    (mstat->f_flags & ~(MNT_ROOTFS | MNT_AUTOMOUNTED));
	sbp->f_bsize = mstat->f_bsize;
	sbp->f_iosize = mstat->f_iosize;
	sbp->f_blocks = mstat->f_blocks;
	sbp->f_bfree = mstat->f_bfree;
	sbp->f_bavail = mstat->f_bavail;
	sbp->f_files = mstat->f_files;
	sbp->f_ffree = mstat->f_ffree;

	free(mstat, M_STATFS);
	return (0);
}

static int
tptfs_sync(mp, waitfor)
	struct mount *mp;
	int waitfor;
{
	/*
	 * XXX - Assumes no data cached at null layer.
	 */
	return (0);
}

static int
tptfs_vget(mp, ino, flags, vpp)
	struct mount *mp;
	ino_t ino;
	int flags;
	struct vnode **vpp;
{
	int error;

	KASSERT((flags & LK_TYPE_MASK) != 0,
	    ("tptfs_vget: no lock requested"));

	error = VFS_VGET(MOUNTTONULLMOUNT(mp)->nullm_vfs, ino, flags, vpp);
	if (error != 0)
		return (error);
	return (tpt_nodeget(mp, *vpp, vpp));
}

static int
tptfs_fhtovp(mp, fidp, flags, vpp)
	struct mount *mp;
	struct fid *fidp;
	int flags;
	struct vnode **vpp;
{
	int error;

	error = VFS_FHTOVP(MOUNTTONULLMOUNT(mp)->nullm_vfs, fidp, flags,
	    vpp);
	if (error != 0)
		return (error);
	return (tpt_nodeget(mp, *vpp, vpp));
}

static int                        
tptfs_extattrctl(mp, cmd, filename_vp, namespace, attrname)
	struct mount *mp;
	int cmd;
	struct vnode *filename_vp;
	int namespace;
	const char *attrname;
{

	return (VFS_EXTATTRCTL(MOUNTTONULLMOUNT(mp)->nullm_vfs, cmd,
	    filename_vp, namespace, attrname));
}

static void
tptfs_reclaim_lowervp(struct mount *mp, struct vnode *lowervp)
{
	struct vnode *vp;

	vp = tpt_hashget(mp, lowervp);
	if (vp == NULL)
		return;
	VTONULL(vp)->tpt_flags |= NULLV_NOUNLOCK;
	vgone(vp);
	vput(vp);
}

static void
tptfs_unlink_lowervp(struct mount *mp, struct vnode *lowervp)
{
	struct vnode *vp;
	struct tpt_node *xp;

	vp = tpt_hashget(mp, lowervp);
	if (vp == NULL)
		return;
	xp = VTONULL(vp);
	xp->tpt_flags |= NULLV_DROP | NULLV_NOUNLOCK;
	vhold(vp);
	vunref(vp);

	if (vp->v_usecount == 0) {
		/*
		 * If vunref() dropped the last use reference on the
		 * tptfs vnode, it must be reclaimed, and its lock
		 * was split from the lower vnode lock.  Need to do
		 * extra unlock before allowing the final vdrop() to
		 * free the vnode.
		 */
		KASSERT(VN_IS_DOOMED(vp),
		    ("not reclaimed tptfs vnode %p", vp));
		VOP_UNLOCK(vp);
	} else {
		/*
		 * Otherwise, the tptfs vnode still shares the lock
		 * with the lower vnode, and must not be unlocked.
		 * Also clear the NULLV_NOUNLOCK, the flag is not
		 * relevant for future reclamations.
		 */
		ASSERT_VOP_ELOCKED(vp, "unlink_lowervp");
		KASSERT(!VN_IS_DOOMED(vp),
		    ("reclaimed tptfs vnode %p", vp));
		xp->tpt_flags &= ~NULLV_NOUNLOCK;
	}
	vdrop(vp);
}

static struct vfsops tpt_vfsops = {
	.vfs_extattrctl =	tptfs_extattrctl,
	.vfs_fhtovp =		tptfs_fhtovp,
	.vfs_init =		tptfs_init,
	.vfs_mount =		tptfs_mount,
	.vfs_quotactl =		tptfs_quotactl,
	.vfs_root =		tptfs_root,
	.vfs_statfs =		tptfs_statfs,
	.vfs_sync =		tptfs_sync,
	.vfs_uninit =		tptfs_uninit,
	.vfs_unmount =		tptfs_unmount,
	.vfs_vget =		tptfs_vget,
	.vfs_reclaim_lowervp =	tptfs_reclaim_lowervp,
	.vfs_unlink_lowervp =	tptfs_unlink_lowervp,
};

VFS_SET(tpt_vfsops, tptfs, VFCF_LOOPBACK | VFCF_JAIL);
