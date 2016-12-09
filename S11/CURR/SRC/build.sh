#!/bin/bash

make
cp 25KERNEL.bin ../isodir/boot
mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o ../25OS.iso ../isodir