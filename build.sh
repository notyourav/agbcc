#!/bin/sh
set -e
CCOPT=
CXXOPT=

if [ ! -z "$CC" ]; then CCOPT=CC=$CC; fi
if [ ! -z "$CXX" ]; then CXXOPT=CXX=$CXX; fi
make -C gcc clean
make -C gcc old $CCOPT $CXXOPT
make -C g++ clean
make -C g++_arm clean
mv gcc/old_agbcc .
make -C gcc clean
make -C gcc $CCOPT $CXXOPT
mv gcc/agbcc .
# not sure if the ARM compiler is the old one or the new one (-DOLD_COMPILER)
rm -f gcc_arm/config.status gcc_arm/config.cache
cd gcc_arm && ./configure --target=arm-elf --host=i386-linux-gnu && make cc1 && cd ..
mv gcc_arm/cc1 agbcc_arm
# c++ compiler
cd g++ && ./configure --target=thumb-elf --disable-werror --with-cpu=arm7tdmi --with-no-thumb-interwork --disable-multilib --enable-languages="c++" --host=i686-pc-linux --build=i686-pc-linux && make cc1plus && cd ..
mv g++/cc1plus agbcp
cd g++_arm && ./configure --target=arm-elf --disable-werror --with-cpu=arm7tdmi --with-no-thumb-interwork --disable-multilib --enable-languages="c++" --host=i686-pc-linux --build=i686-pc-linux && make cc1plus && cd ..
mv g++_arm/cc1plus agbcp_arm
# runtime
make -C libgcc clean
make -C libgcc $CCOPT $CXXOPT
mv libgcc/libgcc.a .
make -C libc clean
make -C libc $CCOPT $CXXOPT
mv libc/libc.a .
