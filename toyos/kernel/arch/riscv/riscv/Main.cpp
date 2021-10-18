// #include "sbi.hpp"
#include "printk.hpp"

extern "C" int Main() {
    char str[24] = "hello world!";
    printk("%s %d\n", str, 1024);
	while (1) {}
	return 0;
}