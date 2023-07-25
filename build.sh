#!/usr/bin/bash

user="adailton"
server="raspberrypi.local"
dir_destination="/home/adailton/"

CC="aarch64-linux-gnu-gcc"

STANDARD="-std=c2x"
DEBUG_LEVEL="-g3"
OPTIM_LEVEL="-O3"
WARNINGS="-Wall -Wextra -Wpedantic 
          -Wformat=2 -Wformat-signedness -Winit-self
          -Wlogical-op -Wbad-function-cast 
          -Wstrict-prototypes -Wmissing-declarations -Wmissing-prototypes 
          -Wmissing-include-dirs
          -Wredundant-decls -Wnested-externs
          -Wshadow -Wundef -Wunused-macros -Walloc-zero
          -Wcast-align -Wcast-qual -Wconversion 
          -Wduplicated-branches -Wduplicated-cond 
          -Wswitch
          -Wunreachable-code -Wunused-but-set-parameter
          -Wfloat-equal -Wpointer-arith"
C_FLAGS="-static ${STANDARD} ${DEBUG_LEVEL} ${OPTIM_LEVEL} ${WARNINGS}"

LIBS=""

set -x

if [[ $1 == "clean" ]]; then
    rm -rf Build/*
elif [[ $1 == "copy" ]]; then
    echo Copying files to server
    scp Build/* "${user}@${server}":"$dir_destination"
elif [[ $1 == "login" ]]; then
    ssh "${user}@${server}"
else
    mkdir -p Build/
    $CC $C_FLAGS sh1106_driver.c sh1106_draw.c Examples/helloworld.c -o Build/helloworld.o $LIBS 
fi

set +x

exit
