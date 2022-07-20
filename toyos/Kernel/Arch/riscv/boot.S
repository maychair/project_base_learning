	.section .text.entry
	.globl _start
_start:
	/// Set kenrel stack, size=16K
	la sp, bootstacktop

	/// Set exception handler entry
	# la	t0, cpu_exception_handler
	# csrw	stvec, t0

	/// Use sscratch to seperate S mode and U mode, which S mode sscratch = 0.
	# li	t0, 0
	# csrw	sscratch, t0

	/// Call first c function and not return.
	call kernelMain

	.section .bss.stack
	.align 12
	.global bootstack
bootstack:
	.space 4096 * 4
	.global bootstacktop
bootstacktop: