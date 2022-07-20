/// Copyright (c) 2022-2024

#include <Library/libc/printk.h>

extern "C" int kernelMain() {
    char str[24] = "hello world!";
    printk("%s %d\n", str, 1024);
	while (1) {}
	return 0;
}