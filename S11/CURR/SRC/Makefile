#Zachary Job
#10.29.13
#V 2
#25OS ALPHA01

#Makefile

NAME=25KERNEL.bin

CC="/cygdrive/c/posix/cygwin86/opt/cross/bin/i586-elf-gcc"
CFLAGS=-c -std=gnu99 -ffreestanding -O2 -Wall -Wextra

AS=nasm
ASMFLAGS=-felf

LD="/cygdrive/c/posix/cygwin86/opt/cross/bin/i586-elf-ld"
LDFLAGS= -nostdlib -fno-builtin -lgcc -T linker.ld

SOURCES= \
base/cdef.c \
hhware/descriptor_Tables.c hhware/isr.c hhware/timer.c \
memory/kheap.c memory/ordered_array.c memory/paging.c \
printing/pbuff.c \
ramdisk/fs.c ramdisk/initrd.c ramdisk/readrd.c \
tasking/task.c \
usermode/syscall.c \
main.c

SASM= \
hhware/gdt.s hhware/interrupt.s \
memory/process.s \
boot.s
CASM=$(SASM:.s=.o)

OBJECTS=$(CASM) $(SOURCES)

all: $(NAME)

.s.o:
	$(AS) $(ASMFLAGS) $<

$(NAME): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	
clean:
	-rm *.o
	-rm base/*.o
	-rm hhware/*.o
	-rm memory/*.o
	-rm printing/*.o
	-rm ramdisk/*.o
	-rm sysdef/*.o
	-rm tasking/*.o
	-rm usermode/*.o
	-rm $(NAME)
	
re: clean all clean