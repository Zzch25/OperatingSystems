#!/bin/bash

make
cp 25KERNEL.bin ../isodir2/boot
grub-mkrescue --output=../25OS.iso ../isodir2