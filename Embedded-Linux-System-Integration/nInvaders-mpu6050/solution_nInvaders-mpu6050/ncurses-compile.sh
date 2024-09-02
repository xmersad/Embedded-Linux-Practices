#!/bin/bash

export CC=aarch64-rpi4-linux-gnu-gcc
export CXX=aarch64-rpi4-linux-gnu-g++
export AR=aarch64-rpi4-linux-gnu-ar
export RANLIB=aarch64-rpi4-linux-gnu-ranlib
export CXXFLAGS="-std=c++14"


# Path to the ncurses source
NCURSES_SRC_DIR=""

# Get sysroot from the toolchain
SYSROOT=$($CC --print-sysroot)

# Change to the ncurses source directory
cd $NCURSES_SRC_DIR

# Configure ncurses
./configure \
    --host=aarch64-rpi4-linux-gnu \
    --prefix=/usr \
    --with-sysroot=$SYSROOT \
    --enable-shared \
    --enable-static \
    --with-shared \
    --with-cxx-shared \
    --without-debug \
    --without-ada \
    --without-manpages \
    --without-tests \
    --with-build-cppflags="-I$SYSROOT/usr/include" \
    --with-build-ldflags="-L$SYSROOT/usr/lib" \
    --without-programs \


# Compile ncurses with sysroot
make CFLAGS="--sysroot=$SYSROOT -I$SYSROOT/usr/include" \
     LDFLAGS="--sysroot=$SYSROOT -L$SYSROOT/usr/lib" \
     -j$(nproc)


# Install ncurses with sysroot
make install 
# ALSO set DESTDIR


