OBJS:=kernel.o boot.o linker.ld

CRTI_OBJ=crti.o
CRTBEGIN_OBJ:=$(shell $(CXX) -ffreestanding -O2 -Wall -Wextra -w -fno-exceptions -fno-rtti -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CXX) -ffreestanding -O2 -Wall -Wextra -w -fno-exceptions -fno-rtti -print-file-name=crtend.o)
CRTN_OBJ=crtn.o
 
OBJ_LINK_LIST:=$(CRTI_OBJ) $(CRTBEGIN_OBJ) $(OBJS) $(CRTEND_OBJ) $(CRTN_OBJ)
INTERNAL_OBJS:=$(CRTI_OBJ) $(OBJS) $(CRTN_OBJ)
 
myos.bin: $(OBJ_LINK_LIST)
	$(CXX) -o myos.bin $(OBJ_LINK_LIST) -nostdlib -lgcc
 
clean:
	rm -f myos.bin $(INTERNAL_OBJS)