#!/usr/bin/env bash
set -e

powerpc-eabivle-gcc -fPIC -ffreestanding -mcpu=e200z0 -mvle -Os -c main.c -o main.o
powerpc-eabivle-objdump -d main.o
powerpc-eabivle-objcopy -O binary -j .text main.o main.bin
