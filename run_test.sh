#!/bin/bash
SOURCE=./src/32bit-main.asm
DESTINATION=./boot/boot.bin
INCLUDE=./src/
nasm -f bin -i $INCLUDE $SOURCE -o $DESTINATION 
qemu-system-x86_64 $DESTINATION
