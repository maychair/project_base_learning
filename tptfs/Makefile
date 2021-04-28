KERN_IDENT=GENERIC
MACHINE=riscv
MACHINE_ARCH=riscv64
WITH_CTF=1
DEBUG=-g
S=/work/qihai/sys
# Makefile.riscv -- with config changes.
# Copyright 1990 W. Jolitz
#	from: @(#)Makefile.i386	7.1 5/10/91
#	from FreeBSD: src/sys/conf/Makefile.i386,v 1.255 2002/02/20 23:35:49
# $FreeBSD: releng/12.2/sys/conf/Makefile.riscv 362729 2020-06-28 17:45:13Z mhorne $
#
# Makefile for FreeBSD
#
# RISCVTODO: copy pasted from aarch64, needs to be
# constructed from a machine description:
#	config machineid
# Most changes should be made in the machine description
#	/sys/riscv/conf/``machineid''
# after which you should do
#	 config machineid
# Generic makefile changes should be made in
#	/sys/conf/Makefile.riscv
# after which config should be rerun for all machines.
#

# Which version of config(8) is required.

.if !defined(S)
S=	../../..
.endif
.include "$S/conf/kern.pre.mk"

INCLUDES+= -I$S/contrib/libfdt

# Set the ELF LMA to the address that OpenSBI's fw_jump jumps to. This allows
# us to load the kernel with the -kernel flag in QEMU without having to embed
# it inside BBL or OpenSBI's fw_payload first.
# Note: For rv32 the start address is different (0x80400000).
# We set this value using --defsym rather than hardcoding it in ldscript.riscv
# so that different kernel configs can override the load address.
KERNEL_LMA?=	0x80200000
LDFLAGS+= --defsym='kernel_lma=${KERNEL_LMA}'

.if !empty(DDB_ENABLED)
CFLAGS += -fno-omit-frame-pointer -fno-optimize-sibling-calls
.endif

# hack because genassym.c includes sys/bus.h which includes these.
genassym.o: bus_if.h device_if.h

BEFORE_DEPEND=miidevs.h pccarddevs.h 

OBJS=opensolaris.o opensolaris_cmn_err.o opensolaris_kmem.o \
	opensolaris_misc.o opensolaris_proc.o opensolaris_sunddi.o \
	opensolaris_taskq.o dtrace.o dtrace_xoroshiro128_plus.o \
	dtmalloc.o profile.o sdt.o fbt.o systrace.o prototype.o \
	nfs_clkdtrace.o ck_array.o ck_barrier_centralized.o \
	ck_barrier_combining.o ck_barrier_dissemination.o \
	ck_barrier_mcs.o ck_barrier_tournament.o ck_epoch.o ck_hp.o \
	ck_hs.o ck_ht.o ck_rhs.o fdt.o fdt_ro.o fdt_rw.o fdt_strerror.o \
	fdt_sw.o fdt_wip.o cnvlist.o dnvlist.o nvlist.o nvpair.o \
	zstd_kmalloc.o zstd_common.o fse_decompress.o entropy_common.o \
	error_private.o xxhash.o zstd_compress.o fse_compress.o \
	huf_compress.o zstd_double_fast.o zstd_fast.o zstd_lazy.o \
	zstd_ldm.o zstd_opt.o zstd_decompress.o huf_decompress.o \
	blake2b-ref.o blake2s-ref.o blake2-sw.o bf_ecb.o bf_skey.o \
	camellia.o camellia-api.o chacha.o chacha-sw.o des_ecb.o \
	des_setkey.o rijndael-alg-fst.o rijndael-api-fst.o \
	rijndael-api.o sha1.o sha256c.o sha512c.o skein.o skein_block.o \
	siphash.o siphash_test.o fb_if.o fdt_common.o simplebus.o led.o \
	md.o memdev.o memutil.o acphy.o amphy.o atphy.o axphy.o bmtphy.o \
	brgphy.o ciphy.o e1000phy.o gentbi.o icsphy.o ip1000phy.o \
	jmphy.o lxtphy.o micphy.o mii.o mii_bitbang.o mii_physubr.o \
	mii_fdt.o miibus_if.o mlphy.o nsgphy.o nsphy.o nsphyter.o \
	pnaphy.o qsphy.o rdcphy.o rgephy.o rlphy.o smcphy.o smscphy.o \
	tdkphy.o tlphy.o truephy.o ukphy.o ukphy_subr.o vscphy.o xmphy.o \
	mmcbr_if.o mmcbus_if.o null.o ofw_bus_if.o ofw_bus_subr.o \
	ofw_cpu.o ofw_fdt.o ofw_if.o ofw_graph.o ofw_subr.o ofwbus.o \
	openfirm.o openfirmio.o card_if.o power_if.o pci_if.o \
	pci_iov_if.o pcib_if.o pcib_support.o random_infra.o \
	random_harvestq.o randomdev.o fortuna.o hash.o uart_bus_fdt.o \
	uart_core.o uart_dev_ns8250.o uart_if.o uart_subr.o uart_tty.o \
	virtio.o virtqueue.o virtio_bus_if.o virtio_if.o virtio_pci.o \
	virtio_mmio.o virtio_mmio_if.o if_vtnet.o virtio_blk.o \
	watchdog.o xdma.o xdma_bank.o xdma_bio.o xdma_if.o xdma_mbuf.o \
	xdma_queue.o xdma_sg.o xdma_sglist.o dead_vnops.o devfs_devs.o \
	devfs_dir.o devfs_rule.o devfs_vfsops.o devfs_vnops.o \
	fifo_vnops.o msdosfs_conv.o msdosfs_denode.o msdosfs_fat.o \
	msdosfs_lookup.o msdosfs_vfsops.o msdosfs_vnops.o \
	nfs_commonkrpc.o nfs_commonsubs.o nfs_commonport.o \
	nfs_commonacl.o nfs_clcomsubs.o nfs_clsubs.o nfs_clstate.o \
	nfs_clkrpc.o nfs_clrpcops.o nfs_clvnops.o nfs_clnode.o \
	nfs_clvfsops.o nfs_clport.o nfs_clbio.o nfs_clnfsiod.o \
	nfs_fha_new.o nfs_nfsdsocket.o nfs_nfsdsubs.o nfs_nfsdstate.o \
	nfs_nfsdkrpc.o nfs_nfsdserv.o nfs_nfsdport.o nfs_nfsdcache.o \
	procfs.o procfs_dbregs.o procfs_fpregs.o procfs_ioctl.o \
	procfs_map.o procfs_mem.o procfs_note.o procfs_osrel.o \
	procfs_regs.o procfs_rlimit.o procfs_status.o procfs_type.o \
	pseudofs.o pseudofs_fileno.o pseudofs_vncache.o pseudofs_vnops.o \
	geom_bsd_enc.o geom_ctl.o geom_dev.o geom_disk.o geom_dump.o \
	geom_event.o geom_io.o geom_kern.o geom_slice.o geom_subr.o \
	geom_vfs.o g_label.o g_label_ext2fs.o g_label_flashmap.o \
	g_label_iso9660.o g_label_msdosfs.o g_label_ntfs.o \
	g_label_reiserfs.o g_label_ufs.o g_label_gpt.o \
	g_label_disk_ident.o g_part.o g_part_if.o g_part_bsd.o \
	g_part_gpt.o g_part_mbr.o g_raid.o g_raid_ctl.o g_raid_md_if.o \
	g_raid_tr_if.o md_ddf.o md_intel.o md_jmicron.o md_nvidia.o \
	md_promise.o md_sii.o tr_concat.o tr_raid0.o tr_raid1.o \
	tr_raid1e.o tr_raid5.o isa_if.o cd9660_bmap.o cd9660_lookup.o \
	cd9660_node.o cd9660_rrip.o cd9660_util.o cd9660_vfsops.o \
	cd9660_vnops.o bus_if.o clock_if.o cpufreq_if.o device_if.o \
	imgact_elf.o imgact_shell.o init_main.o init_sysent.o ksched.o \
	kern_acct.o kern_clock.o kern_condvar.o kern_conf.o kern_cons.o \
	kern_cpu.o kern_cpuset.o kern_context.o kern_descrip.o \
	kern_dtrace.o kern_dump.o kern_environment.o kern_et.o \
	kern_event.o kern_exec.o kern_exit.o kern_fail.o kern_ffclock.o \
	kern_fork.o kern_hhook.o kern_idle.o kern_intr.o kern_jail.o \
	kern_khelp.o kern_kthread.o kern_ktrace.o kern_linker.o \
	kern_lock.o kern_lockf.o kern_lockstat.o kern_loginclass.o \
	kern_malloc.o kern_mbuf.o kern_mib.o kern_module.o \
	kern_mtxpool.o kern_mutex.o kern_ntptime.o kern_osd.o \
	kern_physio.o kern_pmc.o kern_priv.o kern_proc.o kern_procctl.o \
	kern_prot.o kern_racct.o kern_rangelock.o kern_rctl.o \
	kern_resource.o kern_rmlock.o kern_rwlock.o kern_sdt.o \
	kern_sema.o kern_sendfile.o kern_sharedpage.o kern_shutdown.o \
	kern_sig.o kern_switch.o kern_sx.o kern_synch.o kern_syscalls.o \
	kern_sysctl.o kern_tc.o kern_thr.o kern_thread.o kern_time.o \
	kern_timeout.o kern_umtx.o kern_uuid.o kern_xxx.o link_elf.o \
	linker_if.o md5c.o p1003_1b.o posix4_mib.o sched_ule.o \
	serdev_if.o stack_protector.o subr_acl_nfs4.o subr_acl_posix1e.o \
	subr_autoconf.o subr_blist.o subr_boot.o subr_bus.o \
	subr_bus_dma.o subr_bufring.o subr_capability.o subr_clock.o \
	subr_compressor.o subr_counter.o subr_devstat.o subr_disk.o \
	subr_early.o subr_epoch.o subr_eventhandler.o subr_fattime.o \
	subr_firmware.o subr_gtaskqueue.o subr_hash.o subr_hints.o \
	subr_kdb.o subr_kobj.o subr_lock.o subr_log.o subr_module.o \
	subr_msgbuf.o subr_param.o subr_pcpu.o subr_pctrie.o \
	subr_pidctrl.o subr_power.o subr_prf.o subr_prof.o \
	subr_rangeset.o subr_rman.o subr_rtc.o subr_sbuf.o subr_scanf.o \
	subr_sglist.o subr_sleepqueue.o subr_smp.o subr_stack.o \
	subr_taskqueue.o subr_trap.o subr_turnstile.o subr_uio.o \
	subr_unit.o subr_vmem.o sys_capability.o sys_generic.o \
	sys_getrandom.o sys_pipe.o sys_procdesc.o sys_process.o \
	sys_socket.o syscalls.o sysv_ipc.o sysv_msg.o sysv_sem.o \
	sysv_shm.o tty.o tty_info.o tty_inq.o tty_outq.o tty_pts.o \
	tty_tty.o tty_ttydisc.o uipc_accf.o uipc_domain.o uipc_mbuf.o \
	uipc_mbuf2.o uipc_mbufhash.o uipc_shm.o uipc_sockbuf.o \
	uipc_socket.o uipc_syscalls.o uipc_usrreq.o vfs_acl.o vfs_aio.o \
	vfs_bio.o vfs_cache.o vfs_cluster.o vfs_default.o vfs_export.o \
	vfs_extattr.o vfs_hash.o vfs_init.o vfs_lookup.o vfs_mount.o \
	vfs_mountroot.o vfs_subr.o vfs_syscalls.o vfs_vnops.o \
	arc4random.o arc4random_uniform.o asprintf.o bcd.o bsearch.o \
	crc32.o explicit_bzero.o fnmatch.o inet_aton.o inet_ntoa.o \
	inet_ntop.o inet_pton.o jenkins_hash.o murmur3_32.o memcchr.o \
	memchr.o qsort.o qsort_r.o random.o scanc.o strcasecmp.o \
	strcat.o strchr.o strcmp.o strcpy.o strcspn.o strdup.o strndup.o \
	strlcat.o strlcpy.o strlen.o strncat.o strncmp.o strncpy.o \
	strnlen.o strrchr.o strsep.o strspn.o strstr.o strtol.o strtoq.o \
	strtoul.o strtouq.o strvalid.o timingsafe_bcmp.o zlib.o bpf.o \
	bpf_buffer.o bpf_filter.o bpf_zerocopy.o if.o if_clone.o \
	if_dead.o if_ethersubr.o if_gif.o if_ipsec.o if_loop.o \
	if_llatbl.o if_media.o if_mib.o if_tuntap.o if_vlan.o netisr.o \
	pfil.o radix.o radix_mpath.o raw_cb.o raw_usrreq.o route.o \
	rtsock.o vnet.o if_ether.o igmp.o in.o in_kdtrace.o in_fib.o \
	in_gif.o ip_id.o in_jail.o in_mcast.o in_pcb.o in_prot.o \
	in_proto.o in_rmx.o ip_ecn.o ip_encap.o ip_fastfwd.o ip_icmp.o \
	ip_input.o ip_options.o ip_output.o ip_reass.o raw_ip.o cc.o \
	cc_newreno.o sctp_asconf.o sctp_auth.o sctp_bsd_addr.o \
	sctp_cc_functions.o sctp_crc32.o sctp_indata.o sctp_input.o \
	sctp_kdtrace.o sctp_output.o sctp_pcb.o sctp_peeloff.o \
	sctp_ss_functions.o sctp_syscalls.o sctp_sysctl.o sctp_timer.o \
	sctp_usrreq.o sctputil.o tcp_hostcache.o tcp_input.o tcp_lro.o \
	tcp_output.o tcp_offload.o tcp_reass.o tcp_sack.o tcp_subr.o \
	tcp_syncache.o tcp_timer.o tcp_timewait.o tcp_usrreq.o \
	udp_usrreq.o dest6.o frag6.o icmp6.o in6.o in6_cksum.o in6_fib.o \
	in6_gif.o in6_ifattach.o in6_jail.o in6_mcast.o in6_pcb.o \
	in6_proto.o in6_rmx.o in6_src.o ip6_fastfwd.o ip6_forward.o \
	ip6_id.o ip6_input.o ip6_output.o mld6.o nd6.o nd6_nbr.o \
	nd6_rtr.o raw_ip6.o route6.o scope6.o sctp6_usrreq.o \
	udp6_usrreq.o ipsec.o ipsec_input.o ipsec_mbuf.o ipsec_mod.o \
	ipsec_output.o ipsec_pcb.o key.o key_debug.o keysock.o \
	subr_ipsec.o udpencap.o xform_ah.o xform_esp.o xform_ipcomp.o \
	nfs_diskless.o nfs_fha.o nfs_lock.o nfs_nfssvc.o nlm_advlock.o \
	nlm_prot_clnt.o nlm_prot_impl.o nlm_prot_server.o nlm_prot_svc.o \
	nlm_prot_xdr.o sm_inter_xdr.o cast.o criov.o crypto.o \
	cryptodev_if.o cryptosoft.o cryptodeflate.o gmac.o gfmult.o \
	rmd160.o skipjack.o xform.o xform_poly1305.o \
	onetimeauth_poly1305.o poly1305_donna.o verify.o randombytes.o \
	utils.o cbc_mac.o xform_cbc_mac.o auth_none.o auth_unix.o \
	authunix_prot.o clnt_bck.o clnt_dg.o clnt_rc.o clnt_vc.o \
	getnetconfig.o replay.o rpc_callmsg.o rpc_generic.o rpc_prot.o \
	rpcb_clnt.o rpcb_prot.o svc.o svc_auth.o svc_auth_unix.o \
	svc_dg.o svc_generic.o svc_vc.o audit.o audit_arg.o audit_bsm.o \
	audit_bsm_db.o audit_bsm_klib.o audit_dtrace.o audit_pipe.o \
	audit_syscalls.o audit_trigger.o audit_worker.o bsm_domain.o \
	bsm_errno.o bsm_fcntl.o bsm_socket_type.o bsm_token.o \
	mac_audit.o mac_cred.o mac_framework.o mac_inet.o mac_inet6.o \
	mac_label.o mac_net.o mac_pipe.o mac_posix_sem.o mac_posix_shm.o \
	mac_priv.o mac_process.o mac_socket.o mac_syscalls.o \
	mac_system.o mac_sysv_msg.o mac_sysv_sem.o mac_sysv_shm.o \
	mac_vfs.o ffs_alloc.o ffs_balloc.o ffs_inode.o ffs_snapshot.o \
	ffs_softdep.o ffs_subr.o ffs_tables.o ffs_vfsops.o ffs_vnops.o \
	ffs_suspend.o ufs_acl.o ufs_bmap.o ufs_dirhash.o ufs_extattr.o \
	ufs_gjournal.o ufs_inode.o ufs_lookup.o ufs_quota.o ufs_vfsops.o \
	ufs_vnops.o default_pager.o device_pager.o phys_pager.o \
	sg_pager.o swap_pager.o uma_core.o uma_dbg.o vm_domainset.o \
	vm_fault.o vm_glue.o vm_init.o vm_kern.o vm_map.o vm_meter.o \
	vm_mmap.o vm_object.o vm_page.o vm_pageout.o vm_pager.o \
	vm_phys.o vm_radix.o vm_reserv.o vm_swapout.o vm_unix.o \
	vnode_pager.o xdr.o xdr_array.o xdr_mbuf.o xdr_mem.o \
	xdr_reference.o xdr_sizeof.o new.o dtrace_asm.o dtrace_subr.o \
	fbt_isa.o bf_enc.o des_enc.o if_cgem.o uart_cpu_fdt.o \
	uart_dev_lowrisc.o axidma.o if_xae.o kern_clocksource.o msi_if.o \
	pic_if.o subr_devmap.o subr_dummy_vdso_tc.o subr_intr.o bcmp.o \
	bcopy.o ffs.o ffsl.o ffsll.o fls.o flsl.o flsll.o memcmp.o \
	memset.o autoconf.o bus_machdep.o bus_space_asm.o \
	busdma_bounce.o busdma_machdep.o clock.o copyinout.o copystr.o \
	cpufunc_asm.o dump_machdep.o elf_machdep.o exception.o \
	intr_machdep.o in_cksum.o identcpu.o machdep.o Sbi.o \
	minidump_machdep.o mp_machdep.o mem.o nexus.o ofw_machdep.o \
	plic.o pmap.o riscv_console.o sbi.o soc.o stack_machdep.o \
	support.o swtch.o sys_machdep.o trap.o timer.o uio_machdep.o \
	uma_machdep.o unwind.o vm_machdep.o zstd_kfreebsd.o 

CFILES=$S/cddl/compat/opensolaris/kern/opensolaris.c \
	$S/cddl/compat/opensolaris/kern/opensolaris_cmn_err.c \
	$S/cddl/compat/opensolaris/kern/opensolaris_kmem.c \
	$S/cddl/compat/opensolaris/kern/opensolaris_misc.c \
	$S/cddl/compat/opensolaris/kern/opensolaris_proc.c \
	$S/cddl/compat/opensolaris/kern/opensolaris_sunddi.c \
	$S/cddl/compat/opensolaris/kern/opensolaris_taskq.c \
	$S/cddl/contrib/opensolaris/uts/common/dtrace/dtrace.c \
	$S/cddl/contrib/opensolaris/uts/common/dtrace/dtrace_xoroshiro128_plus.c \
	$S/cddl/dev/dtmalloc/dtmalloc.c $S/cddl/dev/profile/profile.c \
	$S/cddl/dev/sdt/sdt.c $S/cddl/dev/fbt/fbt.c \
	$S/cddl/dev/systrace/systrace.c $S/cddl/dev/prototype.c \
	$S/fs/nfsclient/nfs_clkdtrace.c $S/contrib/ck/src/ck_array.c \
	$S/contrib/ck/src/ck_barrier_centralized.c \
	$S/contrib/ck/src/ck_barrier_combining.c \
	$S/contrib/ck/src/ck_barrier_dissemination.c \
	$S/contrib/ck/src/ck_barrier_mcs.c \
	$S/contrib/ck/src/ck_barrier_tournament.c \
	$S/contrib/ck/src/ck_epoch.c $S/contrib/ck/src/ck_hp.c \
	$S/contrib/ck/src/ck_hs.c $S/contrib/ck/src/ck_ht.c \
	$S/contrib/ck/src/ck_rhs.c $S/contrib/libfdt/fdt.c \
	$S/contrib/libfdt/fdt_ro.c $S/contrib/libfdt/fdt_rw.c \
	$S/contrib/libfdt/fdt_strerror.c $S/contrib/libfdt/fdt_sw.c \
	$S/contrib/libfdt/fdt_wip.c $S/contrib/libnv/cnvlist.c \
	$S/contrib/libnv/dnvlist.c $S/contrib/libnv/nvlist.c \
	$S/contrib/libnv/nvpair.c \
	$S/contrib/zstd/lib/freebsd/zstd_kmalloc.c \
	$S/contrib/zstd/lib/common/zstd_common.c \
	$S/contrib/zstd/lib/common/fse_decompress.c \
	$S/contrib/zstd/lib/common/entropy_common.c \
	$S/contrib/zstd/lib/common/error_private.c \
	$S/contrib/zstd/lib/common/xxhash.c \
	$S/contrib/zstd/lib/compress/zstd_compress.c \
	$S/contrib/zstd/lib/compress/fse_compress.c \
	$S/contrib/zstd/lib/compress/huf_compress.c \
	$S/contrib/zstd/lib/compress/zstd_double_fast.c \
	$S/contrib/zstd/lib/compress/zstd_fast.c \
	$S/contrib/zstd/lib/compress/zstd_lazy.c \
	$S/contrib/zstd/lib/compress/zstd_ldm.c \
	$S/contrib/zstd/lib/compress/zstd_opt.c \
	$S/contrib/zstd/lib/decompress/zstd_decompress.c \
	$S/contrib/zstd/lib/decompress/huf_decompress.c \
	$S/contrib/libb2/blake2b-ref.c $S/contrib/libb2/blake2s-ref.c \
	$S/crypto/blake2/blake2-sw.c $S/crypto/blowfish/bf_ecb.c \
	$S/crypto/blowfish/bf_skey.c $S/crypto/camellia/camellia.c \
	$S/crypto/camellia/camellia-api.c $S/crypto/chacha20/chacha.c \
	$S/crypto/chacha20/chacha-sw.c $S/crypto/des/des_ecb.c \
	$S/crypto/des/des_setkey.c $S/crypto/rijndael/rijndael-alg-fst.c \
	$S/crypto/rijndael/rijndael-api-fst.c \
	$S/crypto/rijndael/rijndael-api.c $S/crypto/sha1.c \
	$S/crypto/sha2/sha256c.c $S/crypto/sha2/sha512c.c \
	$S/crypto/skein/skein.c $S/crypto/skein/skein_block.c \
	$S/crypto/siphash/siphash.c $S/crypto/siphash/siphash_test.c \
	$S/dev/fdt/fdt_common.c $S/dev/fdt/simplebus.c $S/dev/led/led.c \
	$S/dev/md/md.c $S/dev/mem/memdev.c $S/dev/mem/memutil.c \
	$S/dev/mii/acphy.c $S/dev/mii/amphy.c $S/dev/mii/atphy.c \
	$S/dev/mii/axphy.c $S/dev/mii/bmtphy.c $S/dev/mii/brgphy.c \
	$S/dev/mii/ciphy.c $S/dev/mii/e1000phy.c $S/dev/mii/gentbi.c \
	$S/dev/mii/icsphy.c $S/dev/mii/ip1000phy.c $S/dev/mii/jmphy.c \
	$S/dev/mii/lxtphy.c $S/dev/mii/micphy.c $S/dev/mii/mii.c \
	$S/dev/mii/mii_bitbang.c $S/dev/mii/mii_physubr.c \
	$S/dev/mii/mii_fdt.c $S/dev/mii/mlphy.c $S/dev/mii/nsgphy.c \
	$S/dev/mii/nsphy.c $S/dev/mii/nsphyter.c $S/dev/mii/pnaphy.c \
	$S/dev/mii/qsphy.c $S/dev/mii/rdcphy.c $S/dev/mii/rgephy.c \
	$S/dev/mii/rlphy.c $S/dev/mii/smcphy.c $S/dev/mii/smscphy.c \
	$S/dev/mii/tdkphy.c $S/dev/mii/tlphy.c $S/dev/mii/truephy.c \
	$S/dev/mii/ukphy.c $S/dev/mii/ukphy_subr.c $S/dev/mii/vscphy.c \
	$S/dev/mii/xmphy.c $S/dev/null/null.c $S/dev/ofw/ofw_bus_subr.c \
	$S/dev/ofw/ofw_cpu.c $S/dev/ofw/ofw_fdt.c $S/dev/ofw/ofw_graph.c \
	$S/dev/ofw/ofw_subr.c $S/dev/ofw/ofwbus.c $S/dev/ofw/openfirm.c \
	$S/dev/ofw/openfirmio.c $S/dev/pci/pcib_support.c \
	$S/dev/random/random_infra.c $S/dev/random/random_harvestq.c \
	$S/dev/random/randomdev.c $S/dev/random/fortuna.c \
	$S/dev/random/hash.c $S/dev/uart/uart_bus_fdt.c \
	$S/dev/uart/uart_core.c $S/dev/uart/uart_dev_ns8250.c \
	$S/dev/uart/uart_subr.c $S/dev/uart/uart_tty.c \
	$S/dev/virtio/virtio.c $S/dev/virtio/virtqueue.c \
	$S/dev/virtio/pci/virtio_pci.c $S/dev/virtio/mmio/virtio_mmio.c \
	$S/dev/virtio/network/if_vtnet.c \
	$S/dev/virtio/block/virtio_blk.c $S/dev/watchdog/watchdog.c \
	$S/dev/xdma/xdma.c $S/dev/xdma/xdma_bank.c \
	$S/dev/xdma/xdma_bio.c $S/dev/xdma/xdma_mbuf.c \
	$S/dev/xdma/xdma_queue.c $S/dev/xdma/xdma_sg.c \
	$S/dev/xdma/xdma_sglist.c $S/fs/deadfs/dead_vnops.c \
	$S/fs/devfs/devfs_devs.c $S/fs/devfs/devfs_dir.c \
	$S/fs/devfs/devfs_rule.c $S/fs/devfs/devfs_vfsops.c \
	$S/fs/devfs/devfs_vnops.c $S/fs/fifofs/fifo_vnops.c \
	$S/fs/msdosfs/msdosfs_conv.c $S/fs/msdosfs/msdosfs_denode.c \
	$S/fs/msdosfs/msdosfs_fat.c $S/fs/msdosfs/msdosfs_lookup.c \
	$S/fs/msdosfs/msdosfs_vfsops.c $S/fs/msdosfs/msdosfs_vnops.c \
	$S/fs/nfs/nfs_commonkrpc.c $S/fs/nfs/nfs_commonsubs.c \
	$S/fs/nfs/nfs_commonport.c $S/fs/nfs/nfs_commonacl.c \
	$S/fs/nfsclient/nfs_clcomsubs.c $S/fs/nfsclient/nfs_clsubs.c \
	$S/fs/nfsclient/nfs_clstate.c $S/fs/nfsclient/nfs_clkrpc.c \
	$S/fs/nfsclient/nfs_clrpcops.c $S/fs/nfsclient/nfs_clvnops.c \
	$S/fs/nfsclient/nfs_clnode.c $S/fs/nfsclient/nfs_clvfsops.c \
	$S/fs/nfsclient/nfs_clport.c $S/fs/nfsclient/nfs_clbio.c \
	$S/fs/nfsclient/nfs_clnfsiod.c $S/fs/nfsserver/nfs_fha_new.c \
	$S/fs/nfsserver/nfs_nfsdsocket.c $S/fs/nfsserver/nfs_nfsdsubs.c \
	$S/fs/nfsserver/nfs_nfsdstate.c $S/fs/nfsserver/nfs_nfsdkrpc.c \
	$S/fs/nfsserver/nfs_nfsdserv.c $S/fs/nfsserver/nfs_nfsdport.c \
	$S/fs/nfsserver/nfs_nfsdcache.c $S/fs/procfs/procfs.c \
	$S/fs/procfs/procfs_dbregs.c $S/fs/procfs/procfs_fpregs.c \
	$S/fs/procfs/procfs_ioctl.c $S/fs/procfs/procfs_map.c \
	$S/fs/procfs/procfs_mem.c $S/fs/procfs/procfs_note.c \
	$S/fs/procfs/procfs_osrel.c $S/fs/procfs/procfs_regs.c \
	$S/fs/procfs/procfs_rlimit.c $S/fs/procfs/procfs_status.c \
	$S/fs/procfs/procfs_type.c $S/fs/pseudofs/pseudofs.c \
	$S/fs/pseudofs/pseudofs_fileno.c \
	$S/fs/pseudofs/pseudofs_vncache.c \
	$S/fs/pseudofs/pseudofs_vnops.c $S/geom/geom_bsd_enc.c \
	$S/geom/geom_ctl.c $S/geom/geom_dev.c $S/geom/geom_disk.c \
	$S/geom/geom_dump.c $S/geom/geom_event.c $S/geom/geom_io.c \
	$S/geom/geom_kern.c $S/geom/geom_slice.c $S/geom/geom_subr.c \
	$S/geom/geom_vfs.c $S/geom/label/g_label.c \
	$S/geom/label/g_label_ext2fs.c $S/geom/label/g_label_flashmap.c \
	$S/geom/label/g_label_iso9660.c $S/geom/label/g_label_msdosfs.c \
	$S/geom/label/g_label_ntfs.c $S/geom/label/g_label_reiserfs.c \
	$S/geom/label/g_label_ufs.c $S/geom/label/g_label_gpt.c \
	$S/geom/label/g_label_disk_ident.c $S/geom/part/g_part.c \
	$S/geom/part/g_part_bsd.c $S/geom/part/g_part_gpt.c \
	$S/geom/part/g_part_mbr.c $S/geom/raid/g_raid.c \
	$S/geom/raid/g_raid_ctl.c $S/geom/raid/md_ddf.c \
	$S/geom/raid/md_intel.c $S/geom/raid/md_jmicron.c \
	$S/geom/raid/md_nvidia.c $S/geom/raid/md_promise.c \
	$S/geom/raid/md_sii.c $S/geom/raid/tr_concat.c \
	$S/geom/raid/tr_raid0.c $S/geom/raid/tr_raid1.c \
	$S/geom/raid/tr_raid1e.c $S/geom/raid/tr_raid5.c \
	$S/fs/cd9660/cd9660_bmap.c $S/fs/cd9660/cd9660_lookup.c \
	$S/fs/cd9660/cd9660_node.c $S/fs/cd9660/cd9660_rrip.c \
	$S/fs/cd9660/cd9660_util.c $S/fs/cd9660/cd9660_vfsops.c \
	$S/fs/cd9660/cd9660_vnops.c $S/kern/imgact_elf.c \
	$S/kern/imgact_shell.c $S/kern/init_main.c $S/kern/init_sysent.c \
	$S/kern/ksched.c $S/kern/kern_acct.c $S/kern/kern_clock.c \
	$S/kern/kern_condvar.c $S/kern/kern_conf.c $S/kern/kern_cons.c \
	$S/kern/kern_cpu.c $S/kern/kern_cpuset.c $S/kern/kern_context.c \
	$S/kern/kern_descrip.c $S/kern/kern_dtrace.c $S/kern/kern_dump.c \
	$S/kern/kern_environment.c $S/kern/kern_et.c \
	$S/kern/kern_event.c $S/kern/kern_exec.c $S/kern/kern_exit.c \
	$S/kern/kern_fail.c $S/kern/kern_ffclock.c $S/kern/kern_fork.c \
	$S/kern/kern_hhook.c $S/kern/kern_idle.c $S/kern/kern_intr.c \
	$S/kern/kern_jail.c $S/kern/kern_khelp.c $S/kern/kern_kthread.c \
	$S/kern/kern_ktrace.c $S/kern/kern_linker.c $S/kern/kern_lock.c \
	$S/kern/kern_lockf.c $S/kern/kern_lockstat.c \
	$S/kern/kern_loginclass.c $S/kern/kern_malloc.c \
	$S/kern/kern_mbuf.c $S/kern/kern_mib.c $S/kern/kern_module.c \
	$S/kern/kern_mtxpool.c $S/kern/kern_mutex.c \
	$S/kern/kern_ntptime.c $S/kern/kern_osd.c $S/kern/kern_physio.c \
	$S/kern/kern_pmc.c $S/kern/kern_priv.c $S/kern/kern_proc.c \
	$S/kern/kern_procctl.c $S/kern/kern_prot.c $S/kern/kern_racct.c \
	$S/kern/kern_rangelock.c $S/kern/kern_rctl.c \
	$S/kern/kern_resource.c $S/kern/kern_rmlock.c \
	$S/kern/kern_rwlock.c $S/kern/kern_sdt.c $S/kern/kern_sema.c \
	$S/kern/kern_sendfile.c $S/kern/kern_sharedpage.c \
	$S/kern/kern_shutdown.c $S/kern/kern_sig.c $S/kern/kern_switch.c \
	$S/kern/kern_sx.c $S/kern/kern_synch.c $S/kern/kern_syscalls.c \
	$S/kern/kern_sysctl.c $S/kern/kern_tc.c $S/kern/kern_thr.c \
	$S/kern/kern_thread.c $S/kern/kern_time.c $S/kern/kern_timeout.c \
	$S/kern/kern_umtx.c $S/kern/kern_uuid.c $S/kern/kern_xxx.c \
	$S/kern/link_elf.c $S/kern/md5c.c $S/kern/p1003_1b.c \
	$S/kern/posix4_mib.c $S/kern/sched_ule.c \
	$S/kern/stack_protector.c $S/kern/subr_acl_nfs4.c \
	$S/kern/subr_acl_posix1e.c $S/kern/subr_autoconf.c \
	$S/kern/subr_blist.c $S/kern/subr_boot.c $S/kern/subr_bus.c \
	$S/kern/subr_bus_dma.c $S/kern/subr_bufring.c \
	$S/kern/subr_capability.c $S/kern/subr_clock.c \
	$S/kern/subr_compressor.c $S/kern/subr_counter.c \
	$S/kern/subr_devstat.c $S/kern/subr_disk.c $S/kern/subr_early.c \
	$S/kern/subr_epoch.c $S/kern/subr_eventhandler.c \
	$S/kern/subr_fattime.c $S/kern/subr_firmware.c \
	$S/kern/subr_gtaskqueue.c $S/kern/subr_hash.c \
	$S/kern/subr_hints.c $S/kern/subr_kdb.c $S/kern/subr_kobj.c \
	$S/kern/subr_lock.c $S/kern/subr_log.c $S/kern/subr_module.c \
	$S/kern/subr_msgbuf.c $S/kern/subr_param.c $S/kern/subr_pcpu.c \
	$S/kern/subr_pctrie.c $S/kern/subr_pidctrl.c \
	$S/kern/subr_power.c $S/kern/subr_prf.c $S/kern/subr_prof.c \
	$S/kern/subr_rangeset.c $S/kern/subr_rman.c $S/kern/subr_rtc.c \
	$S/kern/subr_sbuf.c $S/kern/subr_scanf.c $S/kern/subr_sglist.c \
	$S/kern/subr_sleepqueue.c $S/kern/subr_smp.c \
	$S/kern/subr_stack.c $S/kern/subr_taskqueue.c \
	$S/kern/subr_trap.c $S/kern/subr_turnstile.c $S/kern/subr_uio.c \
	$S/kern/subr_unit.c $S/kern/subr_vmem.c $S/kern/sys_capability.c \
	$S/kern/sys_generic.c $S/kern/sys_getrandom.c $S/kern/sys_pipe.c \
	$S/kern/sys_procdesc.c $S/kern/sys_process.c \
	$S/kern/sys_socket.c $S/kern/syscalls.c $S/kern/sysv_ipc.c \
	$S/kern/sysv_msg.c $S/kern/sysv_sem.c $S/kern/sysv_shm.c \
	$S/kern/tty.c $S/kern/tty_info.c $S/kern/tty_inq.c \
	$S/kern/tty_outq.c $S/kern/tty_pts.c $S/kern/tty_tty.c \
	$S/kern/tty_ttydisc.c $S/kern/uipc_accf.c $S/kern/uipc_domain.c \
	$S/kern/uipc_mbuf.c $S/kern/uipc_mbuf2.c $S/kern/uipc_mbufhash.c \
	$S/kern/uipc_shm.c $S/kern/uipc_sockbuf.c $S/kern/uipc_socket.c \
	$S/kern/uipc_syscalls.c $S/kern/uipc_usrreq.c $S/kern/vfs_acl.c \
	$S/kern/vfs_aio.c $S/kern/vfs_bio.c $S/kern/vfs_cache.c \
	$S/kern/vfs_cluster.c $S/kern/vfs_default.c $S/kern/vfs_export.c \
	$S/kern/vfs_extattr.c $S/kern/vfs_hash.c $S/kern/vfs_init.c \
	$S/kern/vfs_lookup.c $S/kern/vfs_mount.c $S/kern/vfs_mountroot.c \
	$S/kern/vfs_subr.c $S/kern/vfs_syscalls.c $S/kern/vfs_vnops.c \
	$S/libkern/arc4random.c $S/libkern/arc4random_uniform.c \
	$S/libkern/asprintf.c $S/libkern/bcd.c $S/libkern/bsearch.c \
	$S/libkern/crc32.c $S/libkern/explicit_bzero.c \
	$S/libkern/fnmatch.c $S/libkern/inet_aton.c \
	$S/libkern/inet_ntoa.c $S/libkern/inet_ntop.c \
	$S/libkern/inet_pton.c $S/libkern/jenkins_hash.c \
	$S/libkern/murmur3_32.c $S/libkern/memcchr.c $S/libkern/memchr.c \
	$S/libkern/qsort.c $S/libkern/qsort_r.c $S/libkern/random.c \
	$S/libkern/scanc.c $S/libkern/strcasecmp.c $S/libkern/strcat.c \
	$S/libkern/strchr.c $S/libkern/strcmp.c $S/libkern/strcpy.c \
	$S/libkern/strcspn.c $S/libkern/strdup.c $S/libkern/strndup.c \
	$S/libkern/strlcat.c $S/libkern/strlcpy.c $S/libkern/strlen.c \
	$S/libkern/strncat.c $S/libkern/strncmp.c $S/libkern/strncpy.c \
	$S/libkern/strnlen.c $S/libkern/strrchr.c $S/libkern/strsep.c \
	$S/libkern/strspn.c $S/libkern/strstr.c $S/libkern/strtol.c \
	$S/libkern/strtoq.c $S/libkern/strtoul.c $S/libkern/strtouq.c \
	$S/libkern/strvalid.c $S/libkern/timingsafe_bcmp.c \
	$S/libkern/zlib.c $S/net/bpf.c $S/net/bpf_buffer.c \
	$S/net/bpf_filter.c $S/net/bpf_zerocopy.c $S/net/if.c \
	$S/net/if_clone.c $S/net/if_dead.c $S/net/if_ethersubr.c \
	$S/net/if_gif.c $S/net/if_ipsec.c $S/net/if_loop.c \
	$S/net/if_llatbl.c $S/net/if_media.c $S/net/if_mib.c \
	$S/net/if_tuntap.c $S/net/if_vlan.c $S/net/netisr.c \
	$S/net/pfil.c $S/net/radix.c $S/net/radix_mpath.c \
	$S/net/raw_cb.c $S/net/raw_usrreq.c $S/net/route.c \
	$S/net/rtsock.c $S/net/vnet.c $S/netinet/if_ether.c \
	$S/netinet/igmp.c $S/netinet/in.c $S/netinet/in_kdtrace.c \
	$S/netinet/in_fib.c $S/netinet/in_gif.c $S/netinet/ip_id.c \
	$S/netinet/in_jail.c $S/netinet/in_mcast.c $S/netinet/in_pcb.c \
	$S/netinet/in_prot.c $S/netinet/in_proto.c $S/netinet/in_rmx.c \
	$S/netinet/ip_ecn.c $S/netinet/ip_encap.c \
	$S/netinet/ip_fastfwd.c $S/netinet/ip_icmp.c \
	$S/netinet/ip_input.c $S/netinet/ip_options.c \
	$S/netinet/ip_output.c $S/netinet/ip_reass.c $S/netinet/raw_ip.c \
	$S/netinet/cc/cc.c $S/netinet/cc/cc_newreno.c \
	$S/netinet/sctp_asconf.c $S/netinet/sctp_auth.c \
	$S/netinet/sctp_bsd_addr.c $S/netinet/sctp_cc_functions.c \
	$S/netinet/sctp_crc32.c $S/netinet/sctp_indata.c \
	$S/netinet/sctp_input.c $S/netinet/sctp_kdtrace.c \
	$S/netinet/sctp_output.c $S/netinet/sctp_pcb.c \
	$S/netinet/sctp_peeloff.c $S/netinet/sctp_ss_functions.c \
	$S/netinet/sctp_syscalls.c $S/netinet/sctp_sysctl.c \
	$S/netinet/sctp_timer.c $S/netinet/sctp_usrreq.c \
	$S/netinet/sctputil.c $S/netinet/tcp_hostcache.c \
	$S/netinet/tcp_input.c $S/netinet/tcp_lro.c \
	$S/netinet/tcp_output.c $S/netinet/tcp_offload.c \
	$S/netinet/tcp_reass.c $S/netinet/tcp_sack.c \
	$S/netinet/tcp_subr.c $S/netinet/tcp_syncache.c \
	$S/netinet/tcp_timer.c $S/netinet/tcp_timewait.c \
	$S/netinet/tcp_usrreq.c $S/netinet/udp_usrreq.c \
	$S/netinet6/dest6.c $S/netinet6/frag6.c $S/netinet6/icmp6.c \
	$S/netinet6/in6.c $S/netinet6/in6_cksum.c $S/netinet6/in6_fib.c \
	$S/netinet6/in6_gif.c $S/netinet6/in6_ifattach.c \
	$S/netinet6/in6_jail.c $S/netinet6/in6_mcast.c \
	$S/netinet6/in6_pcb.c $S/netinet6/in6_proto.c \
	$S/netinet6/in6_rmx.c $S/netinet6/in6_src.c \
	$S/netinet6/ip6_fastfwd.c $S/netinet6/ip6_forward.c \
	$S/netinet6/ip6_id.c $S/netinet6/ip6_input.c \
	$S/netinet6/ip6_output.c $S/netinet6/mld6.c $S/netinet6/nd6.c \
	$S/netinet6/nd6_nbr.c $S/netinet6/nd6_rtr.c \
	$S/netinet6/raw_ip6.c $S/netinet6/route6.c $S/netinet6/scope6.c \
	$S/netinet6/sctp6_usrreq.c $S/netinet6/udp6_usrreq.c \
	$S/netipsec/ipsec.c $S/netipsec/ipsec_input.c \
	$S/netipsec/ipsec_mbuf.c $S/netipsec/ipsec_mod.c \
	$S/netipsec/ipsec_output.c $S/netipsec/ipsec_pcb.c \
	$S/netipsec/key.c $S/netipsec/key_debug.c $S/netipsec/keysock.c \
	$S/netipsec/subr_ipsec.c $S/netipsec/udpencap.c \
	$S/netipsec/xform_ah.c $S/netipsec/xform_esp.c \
	$S/netipsec/xform_ipcomp.c $S/nfs/nfs_diskless.c \
	$S/nfs/nfs_fha.c $S/nfs/nfs_lock.c $S/nfs/nfs_nfssvc.c \
	$S/nlm/nlm_advlock.c $S/nlm/nlm_prot_clnt.c \
	$S/nlm/nlm_prot_impl.c $S/nlm/nlm_prot_server.c \
	$S/nlm/nlm_prot_svc.c $S/nlm/nlm_prot_xdr.c \
	$S/nlm/sm_inter_xdr.c $S/opencrypto/cast.c $S/opencrypto/criov.c \
	$S/opencrypto/crypto.c $S/opencrypto/cryptosoft.c \
	$S/opencrypto/cryptodeflate.c $S/opencrypto/gmac.c \
	$S/opencrypto/gfmult.c $S/opencrypto/rmd160.c \
	$S/opencrypto/skipjack.c $S/opencrypto/xform.c \
	$S/opencrypto/xform_poly1305.c \
	$S/contrib/libsodium/src/libsodium/crypto_onetimeauth/poly1305/onetimeauth_poly1305.c \
	$S/contrib/libsodium/src/libsodium/crypto_onetimeauth/poly1305/donna/poly1305_donna.c \
	$S/contrib/libsodium/src/libsodium/crypto_verify/sodium/verify.c \
	$S/crypto/libsodium/randombytes.c $S/crypto/libsodium/utils.c \
	$S/opencrypto/cbc_mac.c $S/opencrypto/xform_cbc_mac.c \
	$S/rpc/auth_none.c $S/rpc/auth_unix.c $S/rpc/authunix_prot.c \
	$S/rpc/clnt_bck.c $S/rpc/clnt_dg.c $S/rpc/clnt_rc.c \
	$S/rpc/clnt_vc.c $S/rpc/getnetconfig.c $S/rpc/replay.c \
	$S/rpc/rpc_callmsg.c $S/rpc/rpc_generic.c $S/rpc/rpc_prot.c \
	$S/rpc/rpcb_clnt.c $S/rpc/rpcb_prot.c $S/rpc/svc.c \
	$S/rpc/svc_auth.c $S/rpc/svc_auth_unix.c $S/rpc/svc_dg.c \
	$S/rpc/svc_generic.c $S/rpc/svc_vc.c $S/security/audit/audit.c \
	$S/security/audit/audit_arg.c $S/security/audit/audit_bsm.c \
	$S/security/audit/audit_bsm_db.c \
	$S/security/audit/audit_bsm_klib.c \
	$S/security/audit/audit_dtrace.c $S/security/audit/audit_pipe.c \
	$S/security/audit/audit_syscalls.c \
	$S/security/audit/audit_trigger.c \
	$S/security/audit/audit_worker.c $S/security/audit/bsm_domain.c \
	$S/security/audit/bsm_errno.c $S/security/audit/bsm_fcntl.c \
	$S/security/audit/bsm_socket_type.c \
	$S/security/audit/bsm_token.c $S/security/mac/mac_audit.c \
	$S/security/mac/mac_cred.c $S/security/mac/mac_framework.c \
	$S/security/mac/mac_inet.c $S/security/mac/mac_inet6.c \
	$S/security/mac/mac_label.c $S/security/mac/mac_net.c \
	$S/security/mac/mac_pipe.c $S/security/mac/mac_posix_sem.c \
	$S/security/mac/mac_posix_shm.c $S/security/mac/mac_priv.c \
	$S/security/mac/mac_process.c $S/security/mac/mac_socket.c \
	$S/security/mac/mac_syscalls.c $S/security/mac/mac_system.c \
	$S/security/mac/mac_sysv_msg.c $S/security/mac/mac_sysv_sem.c \
	$S/security/mac/mac_sysv_shm.c $S/security/mac/mac_vfs.c \
	$S/ufs/ffs/ffs_alloc.c $S/ufs/ffs/ffs_balloc.c \
	$S/ufs/ffs/ffs_inode.c $S/ufs/ffs/ffs_snapshot.c \
	$S/ufs/ffs/ffs_softdep.c $S/ufs/ffs/ffs_subr.c \
	$S/ufs/ffs/ffs_tables.c $S/ufs/ffs/ffs_vfsops.c \
	$S/ufs/ffs/ffs_vnops.c $S/ufs/ffs/ffs_suspend.c \
	$S/ufs/ufs/ufs_acl.c $S/ufs/ufs/ufs_bmap.c \
	$S/ufs/ufs/ufs_dirhash.c $S/ufs/ufs/ufs_extattr.c \
	$S/ufs/ufs/ufs_gjournal.c $S/ufs/ufs/ufs_inode.c \
	$S/ufs/ufs/ufs_lookup.c $S/ufs/ufs/ufs_quota.c \
	$S/ufs/ufs/ufs_vfsops.c $S/ufs/ufs/ufs_vnops.c \
	$S/vm/default_pager.c $S/vm/device_pager.c $S/vm/phys_pager.c \
	$S/vm/sg_pager.c $S/vm/swap_pager.c $S/vm/uma_core.c \
	$S/vm/uma_dbg.c $S/vm/vm_domainset.c $S/vm/vm_fault.c \
	$S/vm/vm_glue.c $S/vm/vm_init.c $S/vm/vm_kern.c $S/vm/vm_map.c \
	$S/vm/vm_meter.c $S/vm/vm_mmap.c $S/vm/vm_object.c \
	$S/vm/vm_page.c $S/vm/vm_pageout.c $S/vm/vm_pager.c \
	$S/vm/vm_phys.c $S/vm/vm_radix.c $S/vm/vm_reserv.c \
	$S/vm/vm_swapout.c $S/vm/vm_unix.c $S/vm/vnode_pager.c \
	$S/xdr/xdr.c $S/xdr/xdr_array.c $S/xdr/xdr_mbuf.c \
	$S/xdr/xdr_mem.c $S/xdr/xdr_reference.c $S/xdr/xdr_sizeof.c \
	$S/cddl/dev/dtrace/riscv/dtrace_subr.c \
	$S/cddl/dev/fbt/riscv/fbt_isa.c $S/crypto/blowfish/bf_enc.c \
	$S/crypto/des/des_enc.c $S/dev/cadence/if_cgem.c \
	$S/dev/uart/uart_cpu_fdt.c $S/dev/uart/uart_dev_lowrisc.c \
	$S/dev/xilinx/axidma.c $S/dev/xilinx/if_xae.c \
	$S/kern/kern_clocksource.c $S/kern/subr_devmap.c \
	$S/kern/subr_dummy_vdso_tc.c $S/kern/subr_intr.c \
	$S/libkern/bcmp.c $S/libkern/bcopy.c $S/libkern/ffs.c \
	$S/libkern/ffsl.c $S/libkern/ffsll.c $S/libkern/fls.c \
	$S/libkern/flsl.c $S/libkern/flsll.c $S/libkern/memcmp.c \
	$S/libkern/memset.c $S/riscv/riscv/autoconf.c \
	$S/riscv/riscv/bus_machdep.c $S/riscv/riscv/busdma_bounce.c \
	$S/riscv/riscv/busdma_machdep.c $S/riscv/riscv/clock.c \
	$S/riscv/riscv/copystr.c $S/riscv/riscv/dump_machdep.c \
	$S/riscv/riscv/elf_machdep.c $S/riscv/riscv/intr_machdep.c \
	$S/riscv/riscv/in_cksum.c $S/riscv/riscv/identcpu.c \
	$S/riscv/riscv/minidump_machdep.c $S/riscv/riscv/mp_machdep.c \
	$S/riscv/riscv/mem.c $S/riscv/riscv/nexus.c \
	$S/riscv/riscv/ofw_machdep.c $S/riscv/riscv/plic.c \
	$S/riscv/riscv/pmap.c $S/riscv/riscv/riscv_console.c \
	$S/riscv/riscv/sbi.c $S/riscv/riscv/soc.c \
	$S/riscv/riscv/stack_machdep.c $S/riscv/riscv/sys_machdep.c \
	$S/riscv/riscv/trap.c $S/riscv/riscv/uio_machdep.c \
	$S/riscv/riscv/uma_machdep.c $S/riscv/riscv/unwind.c \
	$S/riscv/riscv/vm_machdep.c \
	$S/contrib/zstd/lib/freebsd/zstd_kfreebsd.c 

CPPFILES=$S/kern/new.cpp $S/riscv/riscv/machdep.cpp \
	$S/riscv/riscv/Sbi.cpp $S/riscv/riscv/timer.cpp 

SFILES=$S/cddl/dev/dtrace/riscv/dtrace_asm.S \
	$S/riscv/riscv/bus_space_asm.S $S/riscv/riscv/copyinout.S \
	$S/riscv/riscv/cpufunc_asm.S $S/riscv/riscv/exception.S \
	$S/riscv/riscv/locore.S $S/riscv/riscv/support.S \
	$S/riscv/riscv/swtch.S 

MFILES=$S/dev/fb/fb_if.m $S/dev/mii/miibus_if.m $S/dev/mmc/mmcbr_if.m \
	$S/dev/mmc/mmcbus_if.m $S/dev/ofw/ofw_bus_if.m \
	$S/dev/ofw/ofw_if.m $S/dev/pccard/card_if.m \
	$S/dev/pccard/power_if.m $S/dev/pci/pci_if.m \
	$S/dev/pci/pci_iov_if.m $S/dev/pci/pcib_if.m \
	$S/dev/uart/uart_if.m $S/dev/virtio/virtio_bus_if.m \
	$S/dev/virtio/virtio_if.m $S/dev/virtio/mmio/virtio_mmio_if.m \
	$S/dev/xdma/xdma_if.m $S/geom/part/g_part_if.m \
	$S/geom/raid/g_raid_md_if.m $S/geom/raid/g_raid_tr_if.m \
	$S/isa/isa_if.m $S/kern/bus_if.m $S/kern/clock_if.m \
	$S/kern/cpufreq_if.m $S/kern/device_if.m $S/kern/linker_if.m \
	$S/kern/serdev_if.m $S/opencrypto/cryptodev_if.m \
	$S/kern/msi_if.m $S/kern/pic_if.m 

CLEAN=miidevs.h pccarddevs.h 

miidevs.h: $S/tools/miidevs2h.awk $S/dev/mii/miidevs
	${AWK} -f $S/tools/miidevs2h.awk $S/dev/mii/miidevs

pccarddevs.h: $S/tools/pccarddevs2h.awk $S/dev/pccard/pccarddevs
	${AWK} -f $S/tools/pccarddevs2h.awk $S/dev/pccard/pccarddevs

opensolaris.o: $S/cddl/compat/opensolaris/kern/opensolaris.c
	${CDDL_C}
	${NORMAL_CTFCONVERT}

opensolaris_cmn_err.o: $S/cddl/compat/opensolaris/kern/opensolaris_cmn_err.c
	${CDDL_C}
	${NORMAL_CTFCONVERT}

opensolaris_kmem.o: $S/cddl/compat/opensolaris/kern/opensolaris_kmem.c
	${CDDL_C}
	${NORMAL_CTFCONVERT}

opensolaris_misc.o: $S/cddl/compat/opensolaris/kern/opensolaris_misc.c
	${CDDL_C}
	${NORMAL_CTFCONVERT}

opensolaris_proc.o: $S/cddl/compat/opensolaris/kern/opensolaris_proc.c
	${CDDL_C}
	${NORMAL_CTFCONVERT}

opensolaris_sunddi.o: $S/cddl/compat/opensolaris/kern/opensolaris_sunddi.c
	${CDDL_C}
	${NORMAL_CTFCONVERT}

opensolaris_taskq.o: $S/cddl/compat/opensolaris/kern/opensolaris_taskq.c
	${CDDL_C}
	${NORMAL_CTFCONVERT}

dtrace.o: $S/cddl/contrib/opensolaris/uts/common/dtrace/dtrace.c
	${DTRACE_C}
	${NORMAL_CTFCONVERT}

dtrace_xoroshiro128_plus.o: $S/cddl/contrib/opensolaris/uts/common/dtrace/dtrace_xoroshiro128_plus.c
	${DTRACE_C}
	${NORMAL_CTFCONVERT}

dtmalloc.o: $S/cddl/dev/dtmalloc/dtmalloc.c
	${CDDL_C}
	${NORMAL_CTFCONVERT}

profile.o: $S/cddl/dev/profile/profile.c
	${CDDL_C}
	${NORMAL_CTFCONVERT}

sdt.o: $S/cddl/dev/sdt/sdt.c
	${CDDL_C}
	${NORMAL_CTFCONVERT}

fbt.o: $S/cddl/dev/fbt/fbt.c
	${FBT_C}
	${NORMAL_CTFCONVERT}

systrace.o: $S/cddl/dev/systrace/systrace.c
	${CDDL_C}
	${NORMAL_CTFCONVERT}

prototype.o: $S/cddl/dev/prototype.c
	${CDDL_C}
	${NORMAL_CTFCONVERT}

nfs_clkdtrace.o: $S/fs/nfsclient/nfs_clkdtrace.c
	${CDDL_C}
	${NORMAL_CTFCONVERT}

ck_array.o: $S/contrib/ck/src/ck_array.c
	${NORMAL_C} -I$S/contrib/ck/include
	${NORMAL_CTFCONVERT}

ck_barrier_centralized.o: $S/contrib/ck/src/ck_barrier_centralized.c
	${NORMAL_C} -I$S/contrib/ck/include
	${NORMAL_CTFCONVERT}

ck_barrier_combining.o: $S/contrib/ck/src/ck_barrier_combining.c
	${NORMAL_C} -I$S/contrib/ck/include
	${NORMAL_CTFCONVERT}

ck_barrier_dissemination.o: $S/contrib/ck/src/ck_barrier_dissemination.c
	${NORMAL_C} -I$S/contrib/ck/include
	${NORMAL_CTFCONVERT}

ck_barrier_mcs.o: $S/contrib/ck/src/ck_barrier_mcs.c
	${NORMAL_C} -I$S/contrib/ck/include
	${NORMAL_CTFCONVERT}

ck_barrier_tournament.o: $S/contrib/ck/src/ck_barrier_tournament.c
	${NORMAL_C} -I$S/contrib/ck/include
	${NORMAL_CTFCONVERT}

ck_epoch.o: $S/contrib/ck/src/ck_epoch.c
	${NORMAL_C} -I$S/contrib/ck/include
	${NORMAL_CTFCONVERT}

ck_hp.o: $S/contrib/ck/src/ck_hp.c
	${NORMAL_C} -I$S/contrib/ck/include
	${NORMAL_CTFCONVERT}

ck_hs.o: $S/contrib/ck/src/ck_hs.c
	${NORMAL_C} -I$S/contrib/ck/include
	${NORMAL_CTFCONVERT}

ck_ht.o: $S/contrib/ck/src/ck_ht.c
	${NORMAL_C} -I$S/contrib/ck/include
	${NORMAL_CTFCONVERT}

ck_rhs.o: $S/contrib/ck/src/ck_rhs.c
	${NORMAL_C} -I$S/contrib/ck/include
	${NORMAL_CTFCONVERT}

fdt.o: $S/contrib/libfdt/fdt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

fdt_ro.o: $S/contrib/libfdt/fdt_ro.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

fdt_rw.o: $S/contrib/libfdt/fdt_rw.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

fdt_strerror.o: $S/contrib/libfdt/fdt_strerror.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

fdt_sw.o: $S/contrib/libfdt/fdt_sw.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

fdt_wip.o: $S/contrib/libfdt/fdt_wip.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cnvlist.o: $S/contrib/libnv/cnvlist.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

dnvlist.o: $S/contrib/libnv/dnvlist.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nvlist.o: $S/contrib/libnv/nvlist.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nvpair.o: $S/contrib/libnv/nvpair.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

zstd_kmalloc.o: $S/contrib/zstd/lib/freebsd/zstd_kmalloc.c
	${ZSTD_C}
	${NORMAL_CTFCONVERT}

zstd_common.o: $S/contrib/zstd/lib/common/zstd_common.c
	${ZSTD_C}
	${NORMAL_CTFCONVERT}

fse_decompress.o: $S/contrib/zstd/lib/common/fse_decompress.c
	${ZSTD_C}
	${NORMAL_CTFCONVERT}

entropy_common.o: $S/contrib/zstd/lib/common/entropy_common.c
	${ZSTD_C}
	${NORMAL_CTFCONVERT}

error_private.o: $S/contrib/zstd/lib/common/error_private.c
	${ZSTD_C}
	${NORMAL_CTFCONVERT}

xxhash.o: $S/contrib/zstd/lib/common/xxhash.c
	${ZSTD_C}
	${NORMAL_CTFCONVERT}

zstd_compress.o: $S/contrib/zstd/lib/compress/zstd_compress.c
	${ZSTD_C}
	${NORMAL_CTFCONVERT}

fse_compress.o: $S/contrib/zstd/lib/compress/fse_compress.c
	${ZSTD_C}
	${NORMAL_CTFCONVERT}

huf_compress.o: $S/contrib/zstd/lib/compress/huf_compress.c
	${ZSTD_C}
	${NORMAL_CTFCONVERT}

zstd_double_fast.o: $S/contrib/zstd/lib/compress/zstd_double_fast.c
	${ZSTD_C}
	${NORMAL_CTFCONVERT}

zstd_fast.o: $S/contrib/zstd/lib/compress/zstd_fast.c
	${ZSTD_C}
	${NORMAL_CTFCONVERT}

zstd_lazy.o: $S/contrib/zstd/lib/compress/zstd_lazy.c
	${ZSTD_C}
	${NORMAL_CTFCONVERT}

zstd_ldm.o: $S/contrib/zstd/lib/compress/zstd_ldm.c
	${ZSTD_C}
	${NORMAL_CTFCONVERT}

zstd_opt.o: $S/contrib/zstd/lib/compress/zstd_opt.c
	${ZSTD_C}
	${NORMAL_CTFCONVERT}

zstd_decompress.o: $S/contrib/zstd/lib/decompress/zstd_decompress.c
	${ZSTD_C}
	${NORMAL_CTFCONVERT}

huf_decompress.o: $S/contrib/zstd/lib/decompress/huf_decompress.c
	${ZSTD_C}
	${NORMAL_CTFCONVERT}

blake2b-ref.o: $S/contrib/libb2/blake2b-ref.c
	${NORMAL_C} -I$S/crypto/blake2 -Wno-cast-qual -DSUFFIX=_ref -Wno-unused-function
	${NORMAL_CTFCONVERT}

blake2s-ref.o: $S/contrib/libb2/blake2s-ref.c
	${NORMAL_C} -I$S/crypto/blake2 -Wno-cast-qual -DSUFFIX=_ref -Wno-unused-function
	${NORMAL_CTFCONVERT}

blake2-sw.o: $S/crypto/blake2/blake2-sw.c
	${NORMAL_C} -I$S/crypto/blake2 -Wno-cast-qual
	${NORMAL_CTFCONVERT}

bf_ecb.o: $S/crypto/blowfish/bf_ecb.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bf_skey.o: $S/crypto/blowfish/bf_skey.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

camellia.o: $S/crypto/camellia/camellia.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

camellia-api.o: $S/crypto/camellia/camellia-api.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

chacha.o: $S/crypto/chacha20/chacha.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

chacha-sw.o: $S/crypto/chacha20/chacha-sw.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

des_ecb.o: $S/crypto/des/des_ecb.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

des_setkey.o: $S/crypto/des/des_setkey.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rijndael-alg-fst.o: $S/crypto/rijndael/rijndael-alg-fst.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rijndael-api-fst.o: $S/crypto/rijndael/rijndael-api-fst.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rijndael-api.o: $S/crypto/rijndael/rijndael-api.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sha1.o: $S/crypto/sha1.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sha256c.o: $S/crypto/sha2/sha256c.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sha512c.o: $S/crypto/sha2/sha512c.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

skein.o: $S/crypto/skein/skein.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

skein_block.o: $S/crypto/skein/skein_block.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

siphash.o: $S/crypto/siphash/siphash.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

siphash_test.o: $S/crypto/siphash/siphash_test.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

fb_if.o: $S/dev/fb/fb_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

fdt_common.o: $S/dev/fdt/fdt_common.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

simplebus.o: $S/dev/fdt/simplebus.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

led.o: $S/dev/led/led.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

md.o: $S/dev/md/md.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

memdev.o: $S/dev/mem/memdev.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

memutil.o: $S/dev/mem/memutil.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

acphy.o: $S/dev/mii/acphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

amphy.o: $S/dev/mii/amphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

atphy.o: $S/dev/mii/atphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

axphy.o: $S/dev/mii/axphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bmtphy.o: $S/dev/mii/bmtphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

brgphy.o: $S/dev/mii/brgphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ciphy.o: $S/dev/mii/ciphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

e1000phy.o: $S/dev/mii/e1000phy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

gentbi.o: $S/dev/mii/gentbi.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

icsphy.o: $S/dev/mii/icsphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ip1000phy.o: $S/dev/mii/ip1000phy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

jmphy.o: $S/dev/mii/jmphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

lxtphy.o: $S/dev/mii/lxtphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

micphy.o: $S/dev/mii/micphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mii.o: $S/dev/mii/mii.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mii_bitbang.o: $S/dev/mii/mii_bitbang.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mii_physubr.o: $S/dev/mii/mii_physubr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mii_fdt.o: $S/dev/mii/mii_fdt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

miibus_if.o: $S/dev/mii/miibus_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

mlphy.o: $S/dev/mii/mlphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nsgphy.o: $S/dev/mii/nsgphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nsphy.o: $S/dev/mii/nsphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nsphyter.o: $S/dev/mii/nsphyter.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pnaphy.o: $S/dev/mii/pnaphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

qsphy.o: $S/dev/mii/qsphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rdcphy.o: $S/dev/mii/rdcphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rgephy.o: $S/dev/mii/rgephy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rlphy.o: $S/dev/mii/rlphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

smcphy.o: $S/dev/mii/smcphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

smscphy.o: $S/dev/mii/smscphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tdkphy.o: $S/dev/mii/tdkphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tlphy.o: $S/dev/mii/tlphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

truephy.o: $S/dev/mii/truephy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ukphy.o: $S/dev/mii/ukphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ukphy_subr.o: $S/dev/mii/ukphy_subr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vscphy.o: $S/dev/mii/vscphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xmphy.o: $S/dev/mii/xmphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mmcbr_if.o: $S/dev/mmc/mmcbr_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

mmcbus_if.o: $S/dev/mmc/mmcbus_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

null.o: $S/dev/null/null.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ofw_bus_if.o: $S/dev/ofw/ofw_bus_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

ofw_bus_subr.o: $S/dev/ofw/ofw_bus_subr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ofw_cpu.o: $S/dev/ofw/ofw_cpu.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ofw_fdt.o: $S/dev/ofw/ofw_fdt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ofw_if.o: $S/dev/ofw/ofw_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

ofw_graph.o: $S/dev/ofw/ofw_graph.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ofw_subr.o: $S/dev/ofw/ofw_subr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ofwbus.o: $S/dev/ofw/ofwbus.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

openfirm.o: $S/dev/ofw/openfirm.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

openfirmio.o: $S/dev/ofw/openfirmio.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

card_if.o: $S/dev/pccard/card_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

power_if.o: $S/dev/pccard/power_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

pci_if.o: $S/dev/pci/pci_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

pci_iov_if.o: $S/dev/pci/pci_iov_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

pcib_if.o: $S/dev/pci/pcib_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

pcib_support.o: $S/dev/pci/pcib_support.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

random_infra.o: $S/dev/random/random_infra.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

random_harvestq.o: $S/dev/random/random_harvestq.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

randomdev.o: $S/dev/random/randomdev.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

fortuna.o: $S/dev/random/fortuna.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

hash.o: $S/dev/random/hash.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uart_bus_fdt.o: $S/dev/uart/uart_bus_fdt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uart_core.o: $S/dev/uart/uart_core.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uart_dev_ns8250.o: $S/dev/uart/uart_dev_ns8250.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uart_if.o: $S/dev/uart/uart_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

uart_subr.o: $S/dev/uart/uart_subr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uart_tty.o: $S/dev/uart/uart_tty.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

virtio.o: $S/dev/virtio/virtio.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

virtqueue.o: $S/dev/virtio/virtqueue.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

virtio_bus_if.o: $S/dev/virtio/virtio_bus_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

virtio_if.o: $S/dev/virtio/virtio_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

virtio_pci.o: $S/dev/virtio/pci/virtio_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

virtio_mmio.o: $S/dev/virtio/mmio/virtio_mmio.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

virtio_mmio_if.o: $S/dev/virtio/mmio/virtio_mmio_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

if_vtnet.o: $S/dev/virtio/network/if_vtnet.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

virtio_blk.o: $S/dev/virtio/block/virtio_blk.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

watchdog.o: $S/dev/watchdog/watchdog.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xdma.o: $S/dev/xdma/xdma.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xdma_bank.o: $S/dev/xdma/xdma_bank.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xdma_bio.o: $S/dev/xdma/xdma_bio.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xdma_if.o: $S/dev/xdma/xdma_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

xdma_mbuf.o: $S/dev/xdma/xdma_mbuf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xdma_queue.o: $S/dev/xdma/xdma_queue.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xdma_sg.o: $S/dev/xdma/xdma_sg.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xdma_sglist.o: $S/dev/xdma/xdma_sglist.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

dead_vnops.o: $S/fs/deadfs/dead_vnops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

devfs_devs.o: $S/fs/devfs/devfs_devs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

devfs_dir.o: $S/fs/devfs/devfs_dir.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

devfs_rule.o: $S/fs/devfs/devfs_rule.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

devfs_vfsops.o: $S/fs/devfs/devfs_vfsops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

devfs_vnops.o: $S/fs/devfs/devfs_vnops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

fifo_vnops.o: $S/fs/fifofs/fifo_vnops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

msdosfs_conv.o: $S/fs/msdosfs/msdosfs_conv.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

msdosfs_denode.o: $S/fs/msdosfs/msdosfs_denode.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

msdosfs_fat.o: $S/fs/msdosfs/msdosfs_fat.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

msdosfs_lookup.o: $S/fs/msdosfs/msdosfs_lookup.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

msdosfs_vfsops.o: $S/fs/msdosfs/msdosfs_vfsops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

msdosfs_vnops.o: $S/fs/msdosfs/msdosfs_vnops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_commonkrpc.o: $S/fs/nfs/nfs_commonkrpc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_commonsubs.o: $S/fs/nfs/nfs_commonsubs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_commonport.o: $S/fs/nfs/nfs_commonport.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_commonacl.o: $S/fs/nfs/nfs_commonacl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_clcomsubs.o: $S/fs/nfsclient/nfs_clcomsubs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_clsubs.o: $S/fs/nfsclient/nfs_clsubs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_clstate.o: $S/fs/nfsclient/nfs_clstate.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_clkrpc.o: $S/fs/nfsclient/nfs_clkrpc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_clrpcops.o: $S/fs/nfsclient/nfs_clrpcops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_clvnops.o: $S/fs/nfsclient/nfs_clvnops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_clnode.o: $S/fs/nfsclient/nfs_clnode.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_clvfsops.o: $S/fs/nfsclient/nfs_clvfsops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_clport.o: $S/fs/nfsclient/nfs_clport.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_clbio.o: $S/fs/nfsclient/nfs_clbio.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_clnfsiod.o: $S/fs/nfsclient/nfs_clnfsiod.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_fha_new.o: $S/fs/nfsserver/nfs_fha_new.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_nfsdsocket.o: $S/fs/nfsserver/nfs_nfsdsocket.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_nfsdsubs.o: $S/fs/nfsserver/nfs_nfsdsubs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_nfsdstate.o: $S/fs/nfsserver/nfs_nfsdstate.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_nfsdkrpc.o: $S/fs/nfsserver/nfs_nfsdkrpc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_nfsdserv.o: $S/fs/nfsserver/nfs_nfsdserv.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_nfsdport.o: $S/fs/nfsserver/nfs_nfsdport.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_nfsdcache.o: $S/fs/nfsserver/nfs_nfsdcache.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

procfs.o: $S/fs/procfs/procfs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

procfs_dbregs.o: $S/fs/procfs/procfs_dbregs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

procfs_fpregs.o: $S/fs/procfs/procfs_fpregs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

procfs_ioctl.o: $S/fs/procfs/procfs_ioctl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

procfs_map.o: $S/fs/procfs/procfs_map.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

procfs_mem.o: $S/fs/procfs/procfs_mem.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

procfs_note.o: $S/fs/procfs/procfs_note.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

procfs_osrel.o: $S/fs/procfs/procfs_osrel.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

procfs_regs.o: $S/fs/procfs/procfs_regs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

procfs_rlimit.o: $S/fs/procfs/procfs_rlimit.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

procfs_status.o: $S/fs/procfs/procfs_status.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

procfs_type.o: $S/fs/procfs/procfs_type.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pseudofs.o: $S/fs/pseudofs/pseudofs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pseudofs_fileno.o: $S/fs/pseudofs/pseudofs_fileno.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pseudofs_vncache.o: $S/fs/pseudofs/pseudofs_vncache.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pseudofs_vnops.o: $S/fs/pseudofs/pseudofs_vnops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

geom_bsd_enc.o: $S/geom/geom_bsd_enc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

geom_ctl.o: $S/geom/geom_ctl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

geom_dev.o: $S/geom/geom_dev.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

geom_disk.o: $S/geom/geom_disk.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

geom_dump.o: $S/geom/geom_dump.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

geom_event.o: $S/geom/geom_event.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

geom_io.o: $S/geom/geom_io.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

geom_kern.o: $S/geom/geom_kern.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

geom_slice.o: $S/geom/geom_slice.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

geom_subr.o: $S/geom/geom_subr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

geom_vfs.o: $S/geom/geom_vfs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_label.o: $S/geom/label/g_label.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_label_ext2fs.o: $S/geom/label/g_label_ext2fs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_label_flashmap.o: $S/geom/label/g_label_flashmap.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_label_iso9660.o: $S/geom/label/g_label_iso9660.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_label_msdosfs.o: $S/geom/label/g_label_msdosfs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_label_ntfs.o: $S/geom/label/g_label_ntfs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_label_reiserfs.o: $S/geom/label/g_label_reiserfs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_label_ufs.o: $S/geom/label/g_label_ufs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_label_gpt.o: $S/geom/label/g_label_gpt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_label_disk_ident.o: $S/geom/label/g_label_disk_ident.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_part.o: $S/geom/part/g_part.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_part_if.o: $S/geom/part/g_part_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

g_part_bsd.o: $S/geom/part/g_part_bsd.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_part_gpt.o: $S/geom/part/g_part_gpt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_part_mbr.o: $S/geom/part/g_part_mbr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_raid.o: $S/geom/raid/g_raid.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_raid_ctl.o: $S/geom/raid/g_raid_ctl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_raid_md_if.o: $S/geom/raid/g_raid_md_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

g_raid_tr_if.o: $S/geom/raid/g_raid_tr_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

md_ddf.o: $S/geom/raid/md_ddf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

md_intel.o: $S/geom/raid/md_intel.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

md_jmicron.o: $S/geom/raid/md_jmicron.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

md_nvidia.o: $S/geom/raid/md_nvidia.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

md_promise.o: $S/geom/raid/md_promise.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

md_sii.o: $S/geom/raid/md_sii.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tr_concat.o: $S/geom/raid/tr_concat.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tr_raid0.o: $S/geom/raid/tr_raid0.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tr_raid1.o: $S/geom/raid/tr_raid1.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tr_raid1e.o: $S/geom/raid/tr_raid1e.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tr_raid5.o: $S/geom/raid/tr_raid5.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

isa_if.o: $S/isa/isa_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

cd9660_bmap.o: $S/fs/cd9660/cd9660_bmap.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cd9660_lookup.o: $S/fs/cd9660/cd9660_lookup.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cd9660_node.o: $S/fs/cd9660/cd9660_node.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cd9660_rrip.o: $S/fs/cd9660/cd9660_rrip.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cd9660_util.o: $S/fs/cd9660/cd9660_util.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cd9660_vfsops.o: $S/fs/cd9660/cd9660_vfsops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cd9660_vnops.o: $S/fs/cd9660/cd9660_vnops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bus_if.o: $S/kern/bus_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

clock_if.o: $S/kern/clock_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

cpufreq_if.o: $S/kern/cpufreq_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

device_if.o: $S/kern/device_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

imgact_elf.o: $S/kern/imgact_elf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

imgact_shell.o: $S/kern/imgact_shell.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

init_main.o: $S/kern/init_main.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

init_sysent.o: $S/kern/init_sysent.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ksched.o: $S/kern/ksched.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_acct.o: $S/kern/kern_acct.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_clock.o: $S/kern/kern_clock.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_condvar.o: $S/kern/kern_condvar.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_conf.o: $S/kern/kern_conf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_cons.o: $S/kern/kern_cons.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_cpu.o: $S/kern/kern_cpu.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_cpuset.o: $S/kern/kern_cpuset.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_context.o: $S/kern/kern_context.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_descrip.o: $S/kern/kern_descrip.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_dtrace.o: $S/kern/kern_dtrace.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_dump.o: $S/kern/kern_dump.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_environment.o: $S/kern/kern_environment.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_et.o: $S/kern/kern_et.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_event.o: $S/kern/kern_event.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_exec.o: $S/kern/kern_exec.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_exit.o: $S/kern/kern_exit.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_fail.o: $S/kern/kern_fail.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_ffclock.o: $S/kern/kern_ffclock.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_fork.o: $S/kern/kern_fork.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_hhook.o: $S/kern/kern_hhook.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_idle.o: $S/kern/kern_idle.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_intr.o: $S/kern/kern_intr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_jail.o: $S/kern/kern_jail.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_khelp.o: $S/kern/kern_khelp.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_kthread.o: $S/kern/kern_kthread.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_ktrace.o: $S/kern/kern_ktrace.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_linker.o: $S/kern/kern_linker.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_lock.o: $S/kern/kern_lock.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_lockf.o: $S/kern/kern_lockf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_lockstat.o: $S/kern/kern_lockstat.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_loginclass.o: $S/kern/kern_loginclass.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_malloc.o: $S/kern/kern_malloc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_mbuf.o: $S/kern/kern_mbuf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_mib.o: $S/kern/kern_mib.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_module.o: $S/kern/kern_module.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_mtxpool.o: $S/kern/kern_mtxpool.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_mutex.o: $S/kern/kern_mutex.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_ntptime.o: $S/kern/kern_ntptime.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_osd.o: $S/kern/kern_osd.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_physio.o: $S/kern/kern_physio.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_pmc.o: $S/kern/kern_pmc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_priv.o: $S/kern/kern_priv.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_proc.o: $S/kern/kern_proc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_procctl.o: $S/kern/kern_procctl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_prot.o: $S/kern/kern_prot.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_racct.o: $S/kern/kern_racct.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_rangelock.o: $S/kern/kern_rangelock.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_rctl.o: $S/kern/kern_rctl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_resource.o: $S/kern/kern_resource.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_rmlock.o: $S/kern/kern_rmlock.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_rwlock.o: $S/kern/kern_rwlock.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_sdt.o: $S/kern/kern_sdt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_sema.o: $S/kern/kern_sema.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_sendfile.o: $S/kern/kern_sendfile.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_sharedpage.o: $S/kern/kern_sharedpage.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_shutdown.o: $S/kern/kern_shutdown.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_sig.o: $S/kern/kern_sig.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_switch.o: $S/kern/kern_switch.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_sx.o: $S/kern/kern_sx.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_synch.o: $S/kern/kern_synch.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_syscalls.o: $S/kern/kern_syscalls.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_sysctl.o: $S/kern/kern_sysctl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_tc.o: $S/kern/kern_tc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_thr.o: $S/kern/kern_thr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_thread.o: $S/kern/kern_thread.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_time.o: $S/kern/kern_time.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_timeout.o: $S/kern/kern_timeout.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_umtx.o: $S/kern/kern_umtx.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_uuid.o: $S/kern/kern_uuid.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_xxx.o: $S/kern/kern_xxx.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

link_elf.o: $S/kern/link_elf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

linker_if.o: $S/kern/linker_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

md5c.o: $S/kern/md5c.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

p1003_1b.o: $S/kern/p1003_1b.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

posix4_mib.o: $S/kern/posix4_mib.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sched_ule.o: $S/kern/sched_ule.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

serdev_if.o: $S/kern/serdev_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

stack_protector.o: $S/kern/stack_protector.c
	${NORMAL_C:N-fstack-protector*}
	${NORMAL_CTFCONVERT}

subr_acl_nfs4.o: $S/kern/subr_acl_nfs4.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_acl_posix1e.o: $S/kern/subr_acl_posix1e.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_autoconf.o: $S/kern/subr_autoconf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_blist.o: $S/kern/subr_blist.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_boot.o: $S/kern/subr_boot.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_bus.o: $S/kern/subr_bus.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_bus_dma.o: $S/kern/subr_bus_dma.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_bufring.o: $S/kern/subr_bufring.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_capability.o: $S/kern/subr_capability.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_clock.o: $S/kern/subr_clock.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_compressor.o: $S/kern/subr_compressor.c
	${NORMAL_C} -I$S/contrib/zstd/lib/freebsd
	${NORMAL_CTFCONVERT}

subr_counter.o: $S/kern/subr_counter.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_devstat.o: $S/kern/subr_devstat.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_disk.o: $S/kern/subr_disk.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_early.o: $S/kern/subr_early.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_epoch.o: $S/kern/subr_epoch.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_eventhandler.o: $S/kern/subr_eventhandler.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_fattime.o: $S/kern/subr_fattime.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_firmware.o: $S/kern/subr_firmware.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_gtaskqueue.o: $S/kern/subr_gtaskqueue.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_hash.o: $S/kern/subr_hash.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_hints.o: $S/kern/subr_hints.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_kdb.o: $S/kern/subr_kdb.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_kobj.o: $S/kern/subr_kobj.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_lock.o: $S/kern/subr_lock.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_log.o: $S/kern/subr_log.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_module.o: $S/kern/subr_module.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_msgbuf.o: $S/kern/subr_msgbuf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_param.o: $S/kern/subr_param.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_pcpu.o: $S/kern/subr_pcpu.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_pctrie.o: $S/kern/subr_pctrie.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_pidctrl.o: $S/kern/subr_pidctrl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_power.o: $S/kern/subr_power.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_prf.o: $S/kern/subr_prf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_prof.o: $S/kern/subr_prof.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_rangeset.o: $S/kern/subr_rangeset.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_rman.o: $S/kern/subr_rman.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_rtc.o: $S/kern/subr_rtc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_sbuf.o: $S/kern/subr_sbuf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_scanf.o: $S/kern/subr_scanf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_sglist.o: $S/kern/subr_sglist.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_sleepqueue.o: $S/kern/subr_sleepqueue.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_smp.o: $S/kern/subr_smp.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_stack.o: $S/kern/subr_stack.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_taskqueue.o: $S/kern/subr_taskqueue.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_trap.o: $S/kern/subr_trap.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_turnstile.o: $S/kern/subr_turnstile.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_uio.o: $S/kern/subr_uio.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_unit.o: $S/kern/subr_unit.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_vmem.o: $S/kern/subr_vmem.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sys_capability.o: $S/kern/sys_capability.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sys_generic.o: $S/kern/sys_generic.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sys_getrandom.o: $S/kern/sys_getrandom.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sys_pipe.o: $S/kern/sys_pipe.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sys_procdesc.o: $S/kern/sys_procdesc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sys_process.o: $S/kern/sys_process.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sys_socket.o: $S/kern/sys_socket.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

syscalls.o: $S/kern/syscalls.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sysv_ipc.o: $S/kern/sysv_ipc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sysv_msg.o: $S/kern/sysv_msg.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sysv_sem.o: $S/kern/sysv_sem.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sysv_shm.o: $S/kern/sysv_shm.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tty.o: $S/kern/tty.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tty_info.o: $S/kern/tty_info.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tty_inq.o: $S/kern/tty_inq.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tty_outq.o: $S/kern/tty_outq.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tty_pts.o: $S/kern/tty_pts.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tty_tty.o: $S/kern/tty_tty.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tty_ttydisc.o: $S/kern/tty_ttydisc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uipc_accf.o: $S/kern/uipc_accf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uipc_domain.o: $S/kern/uipc_domain.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uipc_mbuf.o: $S/kern/uipc_mbuf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uipc_mbuf2.o: $S/kern/uipc_mbuf2.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uipc_mbufhash.o: $S/kern/uipc_mbufhash.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uipc_shm.o: $S/kern/uipc_shm.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uipc_sockbuf.o: $S/kern/uipc_sockbuf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uipc_socket.o: $S/kern/uipc_socket.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uipc_syscalls.o: $S/kern/uipc_syscalls.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uipc_usrreq.o: $S/kern/uipc_usrreq.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_acl.o: $S/kern/vfs_acl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_aio.o: $S/kern/vfs_aio.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_bio.o: $S/kern/vfs_bio.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_cache.o: $S/kern/vfs_cache.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_cluster.o: $S/kern/vfs_cluster.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_default.o: $S/kern/vfs_default.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_export.o: $S/kern/vfs_export.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_extattr.o: $S/kern/vfs_extattr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_hash.o: $S/kern/vfs_hash.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_init.o: $S/kern/vfs_init.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_lookup.o: $S/kern/vfs_lookup.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_mount.o: $S/kern/vfs_mount.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_mountroot.o: $S/kern/vfs_mountroot.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_subr.o: $S/kern/vfs_subr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_syscalls.o: $S/kern/vfs_syscalls.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_vnops.o: $S/kern/vfs_vnops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

arc4random.o: $S/libkern/arc4random.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

arc4random_uniform.o: $S/libkern/arc4random_uniform.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

asprintf.o: $S/libkern/asprintf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bcd.o: $S/libkern/bcd.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bsearch.o: $S/libkern/bsearch.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

crc32.o: $S/libkern/crc32.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

explicit_bzero.o: $S/libkern/explicit_bzero.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

fnmatch.o: $S/libkern/fnmatch.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

inet_aton.o: $S/libkern/inet_aton.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

inet_ntoa.o: $S/libkern/inet_ntoa.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

inet_ntop.o: $S/libkern/inet_ntop.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

inet_pton.o: $S/libkern/inet_pton.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

jenkins_hash.o: $S/libkern/jenkins_hash.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

murmur3_32.o: $S/libkern/murmur3_32.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

memcchr.o: $S/libkern/memcchr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

memchr.o: $S/libkern/memchr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

qsort.o: $S/libkern/qsort.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

qsort_r.o: $S/libkern/qsort_r.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

random.o: $S/libkern/random.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scanc.o: $S/libkern/scanc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strcasecmp.o: $S/libkern/strcasecmp.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strcat.o: $S/libkern/strcat.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strchr.o: $S/libkern/strchr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strcmp.o: $S/libkern/strcmp.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strcpy.o: $S/libkern/strcpy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strcspn.o: $S/libkern/strcspn.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strdup.o: $S/libkern/strdup.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strndup.o: $S/libkern/strndup.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strlcat.o: $S/libkern/strlcat.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strlcpy.o: $S/libkern/strlcpy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strlen.o: $S/libkern/strlen.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strncat.o: $S/libkern/strncat.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strncmp.o: $S/libkern/strncmp.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strncpy.o: $S/libkern/strncpy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strnlen.o: $S/libkern/strnlen.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strrchr.o: $S/libkern/strrchr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strsep.o: $S/libkern/strsep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strspn.o: $S/libkern/strspn.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strstr.o: $S/libkern/strstr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strtol.o: $S/libkern/strtol.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strtoq.o: $S/libkern/strtoq.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strtoul.o: $S/libkern/strtoul.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strtouq.o: $S/libkern/strtouq.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strvalid.o: $S/libkern/strvalid.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

timingsafe_bcmp.o: $S/libkern/timingsafe_bcmp.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

zlib.o: $S/libkern/zlib.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bpf.o: $S/net/bpf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bpf_buffer.o: $S/net/bpf_buffer.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bpf_filter.o: $S/net/bpf_filter.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bpf_zerocopy.o: $S/net/bpf_zerocopy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if.o: $S/net/if.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_clone.o: $S/net/if_clone.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_dead.o: $S/net/if_dead.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_ethersubr.o: $S/net/if_ethersubr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_gif.o: $S/net/if_gif.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_ipsec.o: $S/net/if_ipsec.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_loop.o: $S/net/if_loop.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_llatbl.o: $S/net/if_llatbl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_media.o: $S/net/if_media.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_mib.o: $S/net/if_mib.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_tuntap.o: $S/net/if_tuntap.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_vlan.o: $S/net/if_vlan.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

netisr.o: $S/net/netisr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pfil.o: $S/net/pfil.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

radix.o: $S/net/radix.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

radix_mpath.o: $S/net/radix_mpath.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

raw_cb.o: $S/net/raw_cb.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

raw_usrreq.o: $S/net/raw_usrreq.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

route.o: $S/net/route.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rtsock.o: $S/net/rtsock.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vnet.o: $S/net/vnet.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_ether.o: $S/netinet/if_ether.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

igmp.o: $S/netinet/igmp.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in.o: $S/netinet/in.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in_kdtrace.o: $S/netinet/in_kdtrace.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in_fib.o: $S/netinet/in_fib.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in_gif.o: $S/netinet/in_gif.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ip_id.o: $S/netinet/ip_id.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in_jail.o: $S/netinet/in_jail.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in_mcast.o: $S/netinet/in_mcast.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in_pcb.o: $S/netinet/in_pcb.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in_prot.o: $S/netinet/in_prot.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in_proto.o: $S/netinet/in_proto.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in_rmx.o: $S/netinet/in_rmx.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ip_ecn.o: $S/netinet/ip_ecn.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ip_encap.o: $S/netinet/ip_encap.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ip_fastfwd.o: $S/netinet/ip_fastfwd.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ip_icmp.o: $S/netinet/ip_icmp.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ip_input.o: $S/netinet/ip_input.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ip_options.o: $S/netinet/ip_options.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ip_output.o: $S/netinet/ip_output.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ip_reass.o: $S/netinet/ip_reass.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

raw_ip.o: $S/netinet/raw_ip.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cc.o: $S/netinet/cc/cc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cc_newreno.o: $S/netinet/cc/cc_newreno.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_asconf.o: $S/netinet/sctp_asconf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_auth.o: $S/netinet/sctp_auth.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_bsd_addr.o: $S/netinet/sctp_bsd_addr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_cc_functions.o: $S/netinet/sctp_cc_functions.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_crc32.o: $S/netinet/sctp_crc32.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_indata.o: $S/netinet/sctp_indata.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_input.o: $S/netinet/sctp_input.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_kdtrace.o: $S/netinet/sctp_kdtrace.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_output.o: $S/netinet/sctp_output.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_pcb.o: $S/netinet/sctp_pcb.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_peeloff.o: $S/netinet/sctp_peeloff.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_ss_functions.o: $S/netinet/sctp_ss_functions.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_syscalls.o: $S/netinet/sctp_syscalls.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_sysctl.o: $S/netinet/sctp_sysctl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_timer.o: $S/netinet/sctp_timer.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_usrreq.o: $S/netinet/sctp_usrreq.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctputil.o: $S/netinet/sctputil.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tcp_hostcache.o: $S/netinet/tcp_hostcache.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tcp_input.o: $S/netinet/tcp_input.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tcp_lro.o: $S/netinet/tcp_lro.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tcp_output.o: $S/netinet/tcp_output.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tcp_offload.o: $S/netinet/tcp_offload.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tcp_reass.o: $S/netinet/tcp_reass.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tcp_sack.o: $S/netinet/tcp_sack.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tcp_subr.o: $S/netinet/tcp_subr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tcp_syncache.o: $S/netinet/tcp_syncache.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tcp_timer.o: $S/netinet/tcp_timer.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tcp_timewait.o: $S/netinet/tcp_timewait.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tcp_usrreq.o: $S/netinet/tcp_usrreq.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

udp_usrreq.o: $S/netinet/udp_usrreq.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

dest6.o: $S/netinet6/dest6.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

frag6.o: $S/netinet6/frag6.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

icmp6.o: $S/netinet6/icmp6.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in6.o: $S/netinet6/in6.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in6_cksum.o: $S/netinet6/in6_cksum.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in6_fib.o: $S/netinet6/in6_fib.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in6_gif.o: $S/netinet6/in6_gif.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in6_ifattach.o: $S/netinet6/in6_ifattach.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in6_jail.o: $S/netinet6/in6_jail.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in6_mcast.o: $S/netinet6/in6_mcast.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in6_pcb.o: $S/netinet6/in6_pcb.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in6_proto.o: $S/netinet6/in6_proto.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in6_rmx.o: $S/netinet6/in6_rmx.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in6_src.o: $S/netinet6/in6_src.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ip6_fastfwd.o: $S/netinet6/ip6_fastfwd.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ip6_forward.o: $S/netinet6/ip6_forward.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ip6_id.o: $S/netinet6/ip6_id.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ip6_input.o: $S/netinet6/ip6_input.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ip6_output.o: $S/netinet6/ip6_output.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mld6.o: $S/netinet6/mld6.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nd6.o: $S/netinet6/nd6.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nd6_nbr.o: $S/netinet6/nd6_nbr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nd6_rtr.o: $S/netinet6/nd6_rtr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

raw_ip6.o: $S/netinet6/raw_ip6.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

route6.o: $S/netinet6/route6.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scope6.o: $S/netinet6/scope6.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp6_usrreq.o: $S/netinet6/sctp6_usrreq.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

udp6_usrreq.o: $S/netinet6/udp6_usrreq.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ipsec.o: $S/netipsec/ipsec.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ipsec_input.o: $S/netipsec/ipsec_input.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ipsec_mbuf.o: $S/netipsec/ipsec_mbuf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ipsec_mod.o: $S/netipsec/ipsec_mod.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ipsec_output.o: $S/netipsec/ipsec_output.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ipsec_pcb.o: $S/netipsec/ipsec_pcb.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

key.o: $S/netipsec/key.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

key_debug.o: $S/netipsec/key_debug.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

keysock.o: $S/netipsec/keysock.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_ipsec.o: $S/netipsec/subr_ipsec.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

udpencap.o: $S/netipsec/udpencap.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xform_ah.o: $S/netipsec/xform_ah.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xform_esp.o: $S/netipsec/xform_esp.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xform_ipcomp.o: $S/netipsec/xform_ipcomp.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_diskless.o: $S/nfs/nfs_diskless.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_fha.o: $S/nfs/nfs_fha.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_lock.o: $S/nfs/nfs_lock.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_nfssvc.o: $S/nfs/nfs_nfssvc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nlm_advlock.o: $S/nlm/nlm_advlock.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nlm_prot_clnt.o: $S/nlm/nlm_prot_clnt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nlm_prot_impl.o: $S/nlm/nlm_prot_impl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nlm_prot_server.o: $S/nlm/nlm_prot_server.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nlm_prot_svc.o: $S/nlm/nlm_prot_svc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nlm_prot_xdr.o: $S/nlm/nlm_prot_xdr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sm_inter_xdr.o: $S/nlm/sm_inter_xdr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cast.o: $S/opencrypto/cast.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

criov.o: $S/opencrypto/criov.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

crypto.o: $S/opencrypto/crypto.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cryptodev_if.o: $S/opencrypto/cryptodev_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

cryptosoft.o: $S/opencrypto/cryptosoft.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cryptodeflate.o: $S/opencrypto/cryptodeflate.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

gmac.o: $S/opencrypto/gmac.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

gfmult.o: $S/opencrypto/gfmult.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rmd160.o: $S/opencrypto/rmd160.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

skipjack.o: $S/opencrypto/skipjack.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xform.o: $S/opencrypto/xform.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xform_poly1305.o: $S/opencrypto/xform_poly1305.c
	${NORMAL_C} -I$S/contrib/libsodium/src/libsodium/include -I$S/crypto/libsodium
	${NORMAL_CTFCONVERT}

onetimeauth_poly1305.o: $S/contrib/libsodium/src/libsodium/crypto_onetimeauth/poly1305/onetimeauth_poly1305.c
	${NORMAL_C} -I$S/contrib/libsodium/src/libsodium/include/sodium -I$S/crypto/libsodium
	${NORMAL_CTFCONVERT}

poly1305_donna.o: $S/contrib/libsodium/src/libsodium/crypto_onetimeauth/poly1305/donna/poly1305_donna.c
	${NORMAL_C} -I$S/contrib/libsodium/src/libsodium/include/sodium -I$S/crypto/libsodium
	${NORMAL_CTFCONVERT}

verify.o: $S/contrib/libsodium/src/libsodium/crypto_verify/sodium/verify.c
	${NORMAL_C} -I$S/contrib/libsodium/src/libsodium/include/sodium -I$S/crypto/libsodium
	${NORMAL_CTFCONVERT}

randombytes.o: $S/crypto/libsodium/randombytes.c
	${NORMAL_C} -I$S/contrib/libsodium/src/libsodium/include -I$S/crypto/libsodium
	${NORMAL_CTFCONVERT}

utils.o: $S/crypto/libsodium/utils.c
	${NORMAL_C} -I$S/contrib/libsodium/src/libsodium/include -I$S/crypto/libsodium
	${NORMAL_CTFCONVERT}

cbc_mac.o: $S/opencrypto/cbc_mac.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xform_cbc_mac.o: $S/opencrypto/xform_cbc_mac.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

auth_none.o: $S/rpc/auth_none.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

auth_unix.o: $S/rpc/auth_unix.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

authunix_prot.o: $S/rpc/authunix_prot.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

clnt_bck.o: $S/rpc/clnt_bck.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

clnt_dg.o: $S/rpc/clnt_dg.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

clnt_rc.o: $S/rpc/clnt_rc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

clnt_vc.o: $S/rpc/clnt_vc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

getnetconfig.o: $S/rpc/getnetconfig.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

replay.o: $S/rpc/replay.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rpc_callmsg.o: $S/rpc/rpc_callmsg.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rpc_generic.o: $S/rpc/rpc_generic.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rpc_prot.o: $S/rpc/rpc_prot.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rpcb_clnt.o: $S/rpc/rpcb_clnt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rpcb_prot.o: $S/rpc/rpcb_prot.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

svc.o: $S/rpc/svc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

svc_auth.o: $S/rpc/svc_auth.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

svc_auth_unix.o: $S/rpc/svc_auth_unix.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

svc_dg.o: $S/rpc/svc_dg.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

svc_generic.o: $S/rpc/svc_generic.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

svc_vc.o: $S/rpc/svc_vc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

audit.o: $S/security/audit/audit.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

audit_arg.o: $S/security/audit/audit_arg.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

audit_bsm.o: $S/security/audit/audit_bsm.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

audit_bsm_db.o: $S/security/audit/audit_bsm_db.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

audit_bsm_klib.o: $S/security/audit/audit_bsm_klib.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

audit_dtrace.o: $S/security/audit/audit_dtrace.c
	${CDDL_C}
	${NORMAL_CTFCONVERT}

audit_pipe.o: $S/security/audit/audit_pipe.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

audit_syscalls.o: $S/security/audit/audit_syscalls.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

audit_trigger.o: $S/security/audit/audit_trigger.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

audit_worker.o: $S/security/audit/audit_worker.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bsm_domain.o: $S/security/audit/bsm_domain.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bsm_errno.o: $S/security/audit/bsm_errno.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bsm_fcntl.o: $S/security/audit/bsm_fcntl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bsm_socket_type.o: $S/security/audit/bsm_socket_type.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bsm_token.o: $S/security/audit/bsm_token.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_audit.o: $S/security/mac/mac_audit.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_cred.o: $S/security/mac/mac_cred.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_framework.o: $S/security/mac/mac_framework.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_inet.o: $S/security/mac/mac_inet.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_inet6.o: $S/security/mac/mac_inet6.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_label.o: $S/security/mac/mac_label.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_net.o: $S/security/mac/mac_net.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_pipe.o: $S/security/mac/mac_pipe.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_posix_sem.o: $S/security/mac/mac_posix_sem.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_posix_shm.o: $S/security/mac/mac_posix_shm.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_priv.o: $S/security/mac/mac_priv.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_process.o: $S/security/mac/mac_process.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_socket.o: $S/security/mac/mac_socket.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_syscalls.o: $S/security/mac/mac_syscalls.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_system.o: $S/security/mac/mac_system.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_sysv_msg.o: $S/security/mac/mac_sysv_msg.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_sysv_sem.o: $S/security/mac/mac_sysv_sem.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_sysv_shm.o: $S/security/mac/mac_sysv_shm.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_vfs.o: $S/security/mac/mac_vfs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ffs_alloc.o: $S/ufs/ffs/ffs_alloc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ffs_balloc.o: $S/ufs/ffs/ffs_balloc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ffs_inode.o: $S/ufs/ffs/ffs_inode.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ffs_snapshot.o: $S/ufs/ffs/ffs_snapshot.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ffs_softdep.o: $S/ufs/ffs/ffs_softdep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ffs_subr.o: $S/ufs/ffs/ffs_subr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ffs_tables.o: $S/ufs/ffs/ffs_tables.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ffs_vfsops.o: $S/ufs/ffs/ffs_vfsops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ffs_vnops.o: $S/ufs/ffs/ffs_vnops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ffs_suspend.o: $S/ufs/ffs/ffs_suspend.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ufs_acl.o: $S/ufs/ufs/ufs_acl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ufs_bmap.o: $S/ufs/ufs/ufs_bmap.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ufs_dirhash.o: $S/ufs/ufs/ufs_dirhash.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ufs_extattr.o: $S/ufs/ufs/ufs_extattr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ufs_gjournal.o: $S/ufs/ufs/ufs_gjournal.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ufs_inode.o: $S/ufs/ufs/ufs_inode.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ufs_lookup.o: $S/ufs/ufs/ufs_lookup.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ufs_quota.o: $S/ufs/ufs/ufs_quota.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ufs_vfsops.o: $S/ufs/ufs/ufs_vfsops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ufs_vnops.o: $S/ufs/ufs/ufs_vnops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

default_pager.o: $S/vm/default_pager.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

device_pager.o: $S/vm/device_pager.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

phys_pager.o: $S/vm/phys_pager.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sg_pager.o: $S/vm/sg_pager.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

swap_pager.o: $S/vm/swap_pager.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uma_core.o: $S/vm/uma_core.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uma_dbg.o: $S/vm/uma_dbg.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_domainset.o: $S/vm/vm_domainset.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_fault.o: $S/vm/vm_fault.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_glue.o: $S/vm/vm_glue.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_init.o: $S/vm/vm_init.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_kern.o: $S/vm/vm_kern.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_map.o: $S/vm/vm_map.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_meter.o: $S/vm/vm_meter.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_mmap.o: $S/vm/vm_mmap.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_object.o: $S/vm/vm_object.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_page.o: $S/vm/vm_page.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_pageout.o: $S/vm/vm_pageout.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_pager.o: $S/vm/vm_pager.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_phys.o: $S/vm/vm_phys.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_radix.o: $S/vm/vm_radix.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_reserv.o: $S/vm/vm_reserv.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_swapout.o: $S/vm/vm_swapout.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_unix.o: $S/vm/vm_unix.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vnode_pager.o: $S/vm/vnode_pager.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xdr.o: $S/xdr/xdr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xdr_array.o: $S/xdr/xdr_array.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xdr_mbuf.o: $S/xdr/xdr_mbuf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xdr_mem.o: $S/xdr/xdr_mem.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xdr_reference.o: $S/xdr/xdr_reference.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xdr_sizeof.o: $S/xdr/xdr_sizeof.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

new.o: $S/kern/new.cpp
	${NORMAL_CPP}
	${NORMAL_CTFCONVERT}

dtrace_asm.o: $S/cddl/dev/dtrace/riscv/dtrace_asm.S
	${DTRACE_S}
	${NORMAL_CTFCONVERT}

dtrace_subr.o: $S/cddl/dev/dtrace/riscv/dtrace_subr.c
	${DTRACE_C}
	${NORMAL_CTFCONVERT}

fbt_isa.o: $S/cddl/dev/fbt/riscv/fbt_isa.c
	${FBT_C}
	${NORMAL_CTFCONVERT}

bf_enc.o: $S/crypto/blowfish/bf_enc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

des_enc.o: $S/crypto/des/des_enc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_cgem.o: $S/dev/cadence/if_cgem.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uart_cpu_fdt.o: $S/dev/uart/uart_cpu_fdt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uart_dev_lowrisc.o: $S/dev/uart/uart_dev_lowrisc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

axidma.o: $S/dev/xilinx/axidma.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_xae.o: $S/dev/xilinx/if_xae.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_clocksource.o: $S/kern/kern_clocksource.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

msi_if.o: $S/kern/msi_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

pic_if.o: $S/kern/pic_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

subr_devmap.o: $S/kern/subr_devmap.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_dummy_vdso_tc.o: $S/kern/subr_dummy_vdso_tc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_intr.o: $S/kern/subr_intr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bcmp.o: $S/libkern/bcmp.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bcopy.o: $S/libkern/bcopy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ffs.o: $S/libkern/ffs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ffsl.o: $S/libkern/ffsl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ffsll.o: $S/libkern/ffsll.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

fls.o: $S/libkern/fls.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

flsl.o: $S/libkern/flsl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

flsll.o: $S/libkern/flsll.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

memcmp.o: $S/libkern/memcmp.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

memset.o: $S/libkern/memset.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

autoconf.o: $S/riscv/riscv/autoconf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bus_machdep.o: $S/riscv/riscv/bus_machdep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bus_space_asm.o: $S/riscv/riscv/bus_space_asm.S
	${NORMAL_S}
	${NORMAL_CTFCONVERT}

busdma_bounce.o: $S/riscv/riscv/busdma_bounce.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

busdma_machdep.o: $S/riscv/riscv/busdma_machdep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

clock.o: $S/riscv/riscv/clock.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

copyinout.o: $S/riscv/riscv/copyinout.S
	${NORMAL_S}
	${NORMAL_CTFCONVERT}

copystr.o: $S/riscv/riscv/copystr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cpufunc_asm.o: $S/riscv/riscv/cpufunc_asm.S
	${NORMAL_S}
	${NORMAL_CTFCONVERT}

dump_machdep.o: $S/riscv/riscv/dump_machdep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

elf_machdep.o: $S/riscv/riscv/elf_machdep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

exception.o: $S/riscv/riscv/exception.S
	${NORMAL_S}
	${NORMAL_CTFCONVERT}

intr_machdep.o: $S/riscv/riscv/intr_machdep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in_cksum.o: $S/riscv/riscv/in_cksum.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

identcpu.o: $S/riscv/riscv/identcpu.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

locore.o: $S/riscv/riscv/locore.S
	${NORMAL_S}

machdep.o: $S/riscv/riscv/machdep.cpp
	${NORMAL_CPP}
	${NORMAL_CTFCONVERT}

Sbi.o: $S/riscv/riscv/Sbi.cpp
	${NORMAL_CPP}
	${NORMAL_CTFCONVERT}

minidump_machdep.o: $S/riscv/riscv/minidump_machdep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mp_machdep.o: $S/riscv/riscv/mp_machdep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mem.o: $S/riscv/riscv/mem.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nexus.o: $S/riscv/riscv/nexus.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ofw_machdep.o: $S/riscv/riscv/ofw_machdep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

plic.o: $S/riscv/riscv/plic.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pmap.o: $S/riscv/riscv/pmap.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

riscv_console.o: $S/riscv/riscv/riscv_console.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sbi.o: $S/riscv/riscv/sbi.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

soc.o: $S/riscv/riscv/soc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

stack_machdep.o: $S/riscv/riscv/stack_machdep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

support.o: $S/riscv/riscv/support.S
	${NORMAL_S}
	${NORMAL_CTFCONVERT}

swtch.o: $S/riscv/riscv/swtch.S
	${NORMAL_S}
	${NORMAL_CTFCONVERT}

sys_machdep.o: $S/riscv/riscv/sys_machdep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

trap.o: $S/riscv/riscv/trap.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

timer.o: $S/riscv/riscv/timer.cpp
	${NORMAL_CPP}
	${NORMAL_CTFCONVERT}

uio_machdep.o: $S/riscv/riscv/uio_machdep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uma_machdep.o: $S/riscv/riscv/uma_machdep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

unwind.o: $S/riscv/riscv/unwind.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_machdep.o: $S/riscv/riscv/vm_machdep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

zstd_kfreebsd.o: $S/contrib/zstd/lib/freebsd/zstd_kfreebsd.c
	${ZSTD_C}
	${NORMAL_CTFCONVERT}


.include "$S/conf/kern.post.mk"
