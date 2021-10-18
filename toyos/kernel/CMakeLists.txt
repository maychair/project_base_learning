cmake_minimum_required (VERSION 3.12)

set(CMAKE_ASM_COMPILER "clang")
set(CMAKE_C_COMPILER   "clang")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_AR           "llvm-ar")

enable_language(ASM)

project(kernel)

add_subdirectory(${CMAKE_SOURCE_DIR}/arch/riscv/riscv)
add_subdirectory(${CMAKE_SOURCE_DIR}/libc)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(LINK_FLAGS " '-T${CMAKE_SOURCE_DIR}/arch/riscv/boot/ldscript.riscv' ")

set(CMAKE_ASM_FLAGS "-fno-lto -target riscv64 -march=rv64imafdc -mabi=lp64 -DLOCORE -D_KERNEL -fuse-ld=lld -mno-relax -nostdinc -nostdlib -O0 -pipe -fno-strict-aliasing -g -DHAVE_KERNEL_OPTION_HEADERS  -fno-common -fPIE -fno-omit-frame-pointer -fno-optimize-sibling-calls -ffreestanding -fwrapv -fstack-protector -Wall -Wredundant-decls -Wnested-externs -Wstrict-prototypes -Wmissing-prototypes -Wpointer-arith -Wcast-qual -Wundef -Wno-pointer-sign -D__printf__=__freebsd_kprintf__ -Wmissing-include-dirs -fdiagnostics-show-option -Wno-unknown-pragmas -Wno-error-tautological-compare -Wno-error-empty-body -Wno-error-parentheses-equality -Wno-error-unused-function -Wno-error-pointer-sign -Wno-error-shift-negative-value -Wno-address-of-packed-member -Wno-format-zero-length -mcmodel=medium -std=iso9899:1999")

set(CMAKE_CXX_FLAGS "-target riscv64 -fPIE -fno-common -O0 -pipe -g -nostdinc -D_KERNEL -march=rv64imafdc -mabi=lp64 -mcmodel=medium -mno-relax -ffreestanding -fwrapv -fstack-protector -Wall -Wredundant-decls -Wnested-externs -Wstrict-prototypes -Wmissing-prototypes -Wpointer-arith -Wcast-qual -Wundef -Wno-pointer-sign -D__printf__=__freebsd_kprintf__ -Wmissing-include-dirs -fdiagnostics-show-option -Wno-unknown-pragmas -Wno-error-tautological-compare -Wno-error-empty-body -Wno-error-parentheses-equality -Wno-error-unused-function -Wno-error-pointer-sign -Wno-error-shift-negative-value -Wno-address-of-packed-member -Wno-format-zero-length  -std=c++17 -nostdlib -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-incompatible-pointer-types -fno-sized-deallocation -ffunction-sections -fno-stack-protector")
add_executable(kernel.elf ${CMAKE_SOURCE_DIR}/arch/riscv/boot/boot.S)
set_target_properties(kernel.elf PROPERTIES LINK_FLAGS ${LINK_FLAGS})
target_link_libraries(kernel.elf riscv libc)