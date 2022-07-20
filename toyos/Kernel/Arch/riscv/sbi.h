/// Copyright (c) 2022-2024

#ifndef __SBI_HPP_
#define __SBI_HPP_

#include <Library/libc/stdint.h>

#define	SBI_EXT_ID_TIME			0x54494D45
#define	SBI_TIME_SET_TIMER		0
/* Legacy Extensions */
#define	SBI_SET_TIMER			0
#define	SBI_CONSOLE_PUTCHAR		1
#define	SBI_CONSOLE_GETCHAR		2
#define	SBI_CLEAR_IPI			3
#define	SBI_SEND_IPI			4
#define	SBI_REMOTE_FENCE_I		5
#define	SBI_REMOTE_SFENCE_VMA		6
#define	SBI_REMOTE_SFENCE_VMA_ASID	7
#define	SBI_SHUTDOWN			8

typedef struct SBIRet {
	long error;
	long value;
} SBIRet;

// TODO: 继承单例，禁止拷贝构造和拷贝赋值，可以考虑不需要实例化
class SBI 
{
	// Methods
public:
	static void SBIConsolePutchar(int ch);
	static void SBISetTimer(uint64_t val);
	static void SBIShutdown();
	static int SBIConsoleGetchar();
	static void SBIClearIpi();
	static void SBISendIpi();
	static void SBIRemoteFenceI();
	static void SBIRemoteSfenceVma();
	static void SBIRemoteSfenceVmaAsid();
	// Methods
private:
	static SBIRet
	SBICall(uint64_t arg7, uint64_t arg6, uint64_t arg0 = 0, uint64_t arg1 = 0,
		uint64_t arg2 = 0, uint64_t arg3 = 0, uint64_t arg4 = 0);
};

#endif//__SBI_HPP_