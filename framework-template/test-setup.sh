#!/bin/sh
set -e
DST_DIR=/tmp/rocket
for tr in "none" "qt" "ki18n" ; do
    dst=$DST_DIR-$tr
    rm -rf $dst
    ./setup.sh --tr $tr Rocket $dst
    mkdir $dst/build
    (
        cd $dst/build
        cmake ..
        make
        make install DESTDIR=$dst/install
    )
done
