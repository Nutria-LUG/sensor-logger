#!/bin/bash

# This script perform the rebuild of the whole program. It
# clean the build folder, perform rescan of autotools and
# then run make file.
#    > ./rebuild.sh
#
# If run with --test option, this script build the test
# suite and run it. You need `cpputest` package installed.
#    > ./rebuild.sh --test


CURRENT=$(dirname ".")
CURRENT=$(readlink -f $CURRENT)

DIR=$(dirname "$0")
DIR=$(readlink -f $DIR)

if [ ! -d "$DIR/build" ]; then
    mkdir build
fi
BUILDDIR="$DIR/build"

if [ -f "$BUILDDIR/Makefile" ]; then
    cd $BUILDDIR
    make clean
fi

cd $DIR
./autogen.sh

cd $BUILDDIR
../configure
make

cd $CURRENT
