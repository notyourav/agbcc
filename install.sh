#!/bin/sh
set -e
if [ "$1" != "" ]; then
    mkdir -p $1/tools/agbcc
    mkdir -p $1/tools/agbcc/bin
    mkdir -p $1/tools/agbcc/include
    mkdir -p $1/tools/agbcc/lib
    cp agbcc $1/tools/agbcc/bin/
    cp old_agbcc $1/tools/agbcc/bin/
    cp -R agbcc/libc/include/ $1/tools/agbcc/ #drop include, because we don't want include/include
    cp -R ginclude/* $1/tools/agbcc/include/
    cp libgcc.a $1/tools/agbcc/lib/
    cp libc.a $1/tools/agbcc/lib/
    cp libsiirtc.a $1/tools/agbcc/lib/
    cp siirtc/siirtc.h $1/tools/agbcc/include
    cp libagbsyscall.a $1/tools/agbcc/lib/
    cp libisagbprn.a $1/tools/agbcc/lib/
    cp libm4a.a $1/tools/agbcc/lib/
    cp librfu.a $1/tools/agbcc/lib/
    cp librfu/librfu.h $1/tools/agbcc/include/
    cp libagb_flash.a $1/tools/agbcc/lib/
    cp agb_flash/agb_flash.h $1/tools/agbcc/include/
else
    echo "Usage: install.sh PATH"
fi
