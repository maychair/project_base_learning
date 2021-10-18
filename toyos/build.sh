cd build;
cmake -DCMAKE_CXX_FLAGS="-target riscv64 -nostdinc -nostdlib -mno-relax -fuse-ld=lld" ../kernel
make