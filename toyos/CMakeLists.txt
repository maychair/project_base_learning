cmake_minimum_required (VERSION 3.12)

set(CMAKE_ASM_COMPILER "clang")
set(CMAKE_C_COMPILER   "clang")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_AR           "llvm-ar")

enable_language(ASM)

project(kernel)

include_directories(${CMAKE_SOURCE_DIR})

set(CMAKE_VERBOSE_MAKEFILE ON)
set(LINK_FLAGS " -fuse-ld=lld '-T${CMAKE_SOURCE_DIR}/Kernel/Arch/riscv/ldscript.riscv' ")

set(COMMON_FLAGS "-target riscv64")
set(COMMON_FLAGS " ${COMMON_FLAGS} -march=rv64imafdc")
set(COMMON_FLAGS " ${COMMON_FLAGS} -mabi=lp64")
set(COMMON_FLAGS " ${COMMON_FLAGS} -mno-relax")
set(COMMON_FLAGS " ${COMMON_FLAGS} -O0")
set(COMMON_FLAGS " ${COMMON_FLAGS} -mcmodel=medium")
set(COMMON_FLAGS " ${COMMON_FLAGS} -fPIE")
set(COMMON_FLAGS " ${COMMON_FLAGS} -nostdlib")
set(COMMON_FLAGS " ${COMMON_FLAGS} -nostdinc")
set(COMMON_FLAGS " ${COMMON_FLAGS} -fno-common")
set(COMMON_FLAGS " ${COMMON_FLAGS} -pipe")

set(CMAKE_ASM_FLAGS "${COMMON_FLAGS}")

set(CMAKE_CXX_FLAGS "${COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -fno-exceptions")

add_subdirectory(${CMAKE_SOURCE_DIR}/Kernel)
add_subdirectory(${CMAKE_SOURCE_DIR}/Library)

add_executable(kernel.elf ${CMAKE_SOURCE_DIR}/Kernel/Arch/riscv/boot.S)
set_target_properties(kernel.elf PROPERTIES LINK_FLAGS ${LINK_FLAGS})
target_link_libraries(kernel.elf riscv libc)