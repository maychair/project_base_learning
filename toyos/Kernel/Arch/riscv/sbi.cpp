/// Copyright (c) 2022-2024

#include "sbi.h"
#include "riscvreg.h"

typedef int uintptr_t;

SBIRet SBI::SBICall(uint64_t arg7, uint64_t arg6, uint64_t arg0, uint64_t arg1,
	uint64_t arg2, uint64_t arg3, uint64_t arg4) {
	SBIRet ret;

	register uintptr_t a0 __asm ("a0") = (uintptr_t)(arg0);
	register uintptr_t a1 __asm ("a1") = (uintptr_t)(arg1);
	register uintptr_t a2 __asm ("a2") = (uintptr_t)(arg2);
	register uintptr_t a3 __asm ("a3") = (uintptr_t)(arg3);
	register uintptr_t a4 __asm ("a4") = (uintptr_t)(arg4);
	register uintptr_t a6 __asm ("a6") = (uintptr_t)(arg6);
	register uintptr_t a7 __asm ("a7") = (uintptr_t)(arg7);

	__asm __volatile(			\
		"ecall"				\
		:"+r"(a0), "+r"(a1)		\
		:"r"(a2), "r"(a3), "r"(a4), "r"(a6), "r"(a7)	\
		:"memory");

	ret.error = a0;
	ret.value = a1;
	return (ret);	
}

void SBI::SBIConsolePutchar(int ch) {
	SBICall(SBI_CONSOLE_PUTCHAR, 0, ch);
}

int SBI::SBIConsoleGetchar(void)
{
	return SBICall(SBI_CONSOLE_GETCHAR, 0).error;
}
void SBI::SBISetTimer(uint64_t val) {
	SBICall(SBI_EXT_ID_TIME, SBI_TIME_SET_TIMER, val);
}

void SBI::SBIShutdown() {
	SBICall(SBI_SHUTDOWN, 0);
}