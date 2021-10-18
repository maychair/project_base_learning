	.section .text.entry
	.globl _start
_start:
	//设置栈大小为 16k
	la sp, bootstacktop

	//设置中断处理入口,直转模式,非向量表
	# la	t0, cpu_exception_handler
	# csrw	stvec, t0

	//确保 sscratch 为0,后面会用此寄存器区分用户进程和内核进程; 用户进程 sscratch 为其内核栈;
	# li	t0, 0
	# csrw	sscratch, t0

	//调用c语言入口
	call Main

	.section .bss.stack
	.align 12
	.global bootstack
bootstack:
	.space 4096 * 4
	.global bootstacktop
bootstacktop: