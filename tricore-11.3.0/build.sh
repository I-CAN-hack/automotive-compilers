#!/usr/bin/env bash
set -e

tricore-elf-gcc -mcode-pic -ffreestanding -Os -c main.c -o main.o
tricore-elf-objdump -d main.o
tricore-elf-objcopy -O binary -j .text main.o main.bin
