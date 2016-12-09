#Zachary Job
#10.29.13
#V 1
#25OS PSF022B

#makeFile.mak

NAME=25KERNEL.bin

CXX="/opt/cross/bin/i586-elf-g++"
AS="/opt/cross/bin/i586-elf-as"
CC="/opt/cross/bin/i586-elf-gcc"
LD="/opt/cross/bin/i586-elf-ld"
CFLAGS=-c -std=gnu99 -ffreestanding -O2 -Wall -Wextra -w -fpermissive
LDFLAGS= -nostdlib -lgcc -T linker.ld

SOURCES=prereq/mem/memm.h prereq/mem/moutb.c busopetc/descriptor_tables.h \
prereq/mem/minb.c prereq/mem/minw.c busopetc/descriptor_tables.c busopetc/isr.h \
busopetc/isr.c busopetc/timer.h busopetc/timer.c prereq/str/string.h \
prereq/mem/memcpy.c prereq/mem/memset.c prereq/str/strcat.c \
prereq/str/strcmp.c prereq/str/strcpy.c prereq/str/strlen.c prereq/tdef.h \
memall/panic.c memall/panicassert.c memall/panic.h memall/halloc.c memall/halloc.h \
memall/page.c memall/page.h screenout.h screenout.c kernel.c
SASM=boot.o busopetc/interrupt.o busopetc/gdt.o busopetc/kill.o
OBJECTS=$(SOURCES)
OBJECTSPA=$(SASM) $(OBJECTS)  

CRTI_OBJ=crti.o
CRTBEGIN_OBJ:=$(shell $(CC) -ffreestanding -O2 -Wall -Wextra -w -fno-exceptions -fno-rtti -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) -ffreestanding -O2 -Wall -Wextra -w -fno-exceptions -fno-rtti -print-file-name=crtend.o)
CRTN_OBJ=crtn.o

OBJ_LINK_LIST:=$(CRTI_OBJ) $(CRTBEGIN_OBJ) $(OBJECTSPA) $(CRTEND_OBJ) $(CRTN_OBJ)
INTERNAL_OBJS:=$(CRTI_OBJ) $(OBJECTSPA) $(CRTN_OBJ)

all: $(SOURCES) $(NAME)
	
$(NAME): $(OBJ_LINK_LIST)
	$(CC) $(LDFLAGS) $(OBJ_LINK_LIST) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	-rm *.o
	-cp CASM/*.o ./
	-rm memall/*.o
	-cp memall/CASM/*.o ./busopetc
	-rm busopetc/*.o
	-cp busopetc/CASM/*.o ./busopetc
	-rm prereq/*.o
	-cp prereq/CASM/*.o ./prereq
	-rm prereq/mem/*.o
	-cp prereq/mem/CASM/*.o ./prereq/mem
	-rm prereq/str/*.o
	-cp prereq/str/CASM/*.o ./prereq/str
	-rm $(NAME)