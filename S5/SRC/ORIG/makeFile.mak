#Zachary Job
#10.29.13
#V 1
#25OS PSF022

#makeFile.mak

NAME=25KERNEL.bin

CXX="/opt/cross/bin/i586-elf-g++"
AS="/opt/cross/bin/i586-elf-as"
CC="/opt/cross/bin/i586-elf-gcc"
LD="/opt/cross/bin/i586-elf-ld"
CFLAGS=-c -ffreestanding -O2 -Wall -Wextra -w -fno-exceptions -fno-rtti
LDFLAGS= -nostdlib -lgcc -T linker.ld

SOURCES=busopetc/common.cpp busopetc/descriptor_tables.cpp busopetc/isr.h \
	busopetc/isr.cpp prereq/memcpy.cpp prereq/memset.cpp prereq/memsetw.cpp \
	prereq/strlen.cpp kernel.cpp
SASM=boot.o busopetc/interrupt.o busopetc/gdt.o busopetc/kill.o
OBJECTS=$(SOURCES:.cpp=.o)
OBJECTSPA=$(SASM) $(OBJECTS)  

CRTI_OBJ=crti.o
CRTBEGIN_OBJ:=$(shell $(CXX) -ffreestanding -O2 -Wall -Wextra -w -fno-exceptions -fno-rtti -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CXX) -ffreestanding -O2 -Wall -Wextra -w -fno-exceptions -fno-rtti -print-file-name=crtend.o)
CRTN_OBJ=crtn.o

OBJ_LINK_LIST:=$(CRTI_OBJ) $(CRTBEGIN_OBJ) $(OBJECTSPA) $(CRTEND_OBJ) $(CRTN_OBJ)
INTERNAL_OBJS:=$(CRTI_OBJ) $(OBJECTSPA) $(CRTN_OBJ)

all: $(SOURCES) $(NAME)
	
$(NAME): $(OBJ_LINK_LIST)
	$(CXX) $(LDFLAGS) $(OBJ_LINK_LIST) -o $@

.cpp.o:
	$(CXX) $(CFLAGS) $< -o $@
	
clean:
	-rm *.o
	-cp CASM/*.o ./
	-rm busopetc/*.o
	-cp busopetc/CASM/*.o ./busopetc
	-rm prereq/*.o
	-cp prereq/CASM/*.o ./prereq
	-rm $(NAME)