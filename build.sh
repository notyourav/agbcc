#!/bin/sh
set -e
make -C agbcc_src/gcc clean
make -C agbcc_src/gcc old
mv agbcc_src/gcc/old_agbcc .
make -C agbcc_src/gcc clean
make -C agbcc_src/gcc
mv agbcc_src/gcc/agbcc .
make -C agbcc_src/libgcc clean
make -C agbcc_src/libgcc
mv agbcc_src/libgcc/libgcc.a .
make -C agbcc_src/libc clean
make -C agbcc_src/libc
mv agbcc_src/libc/libc.a .
make -C siirtc clean
make -C siirtc
mv siirtc/libsiirtc.a .
make -C libagbsyscall clean
make -C libagbsyscall
mv libagbsyscall/libagbsyscall.a .
make -C libisagbprn clean
make -C libisagbprn
mv libisagbprn/libisagbprn.a .
make -C m4a clean
make -C m4a
mv m4a/libm4a.a .
