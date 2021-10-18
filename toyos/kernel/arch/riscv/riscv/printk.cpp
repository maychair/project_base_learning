#include <stdarg.h>
#include "sbi.hpp"
#include "string.h"
static char buf[1024];

extern "C" int32_t vsprintf(char *buf, const char *fmt, va_list args);

int printk(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	int ret = vsprintf(buf,fmt,args);
	va_end(args);

    int size = strlen(buf);
    for (int i = 0; i < size; i++) {
        SBI::SBIConsolePutchar(buf[i]);
    }
	return ret;
}
