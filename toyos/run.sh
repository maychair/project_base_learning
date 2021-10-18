qemu-system-riscv64 \
    -machine virt \
    -nographic \
    -bios $OPENSBI/fw_jump.bin \
    -kernel ./build/kernel.elf
