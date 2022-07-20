qemu-system-riscv64 \
    -machine virt -m 8G -smp 2 \
    -nographic \
    -bios /home/saturn/workspace/test/qihai-boot/virtio-qihai-boot/opensbi/build/platform/generic/firmware/fw_jump.elf \
    -kernel ./build/kernel.elf
