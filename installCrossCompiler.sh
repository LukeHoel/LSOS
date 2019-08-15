#!/bin/bash
mkdir $HOME/src
cd $HOME/src

export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

# Get stable binutils
wget https://ftp.gnu.org/gnu/binutils/binutils-2.32.tar.gz
tar xpvf binutils-2.32.tar.gz
cd binutils-2.32
# Build it
./configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install
cd ..

# Get stable gcc
wget https://ftp.gnu.org/gnu/gcc/gcc-9.2.0/gcc-9.2.0.tar.gz
tar xpvf gcc-9.2.0.tar.gz
cd gcc-9.2.0
# Build it
./configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
cd ..