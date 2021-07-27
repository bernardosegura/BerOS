CC = gcc
ASM = as --32
LFLAG = -m32 -c
RFLAG = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
INCLUDES = -I$(shell pwd)/includes
SRCSCC = $(wildcard core/*.c)
OBJSCC = $(SRCSCC:%.c=%.o)
SRCSS = $(wildcard core/*.s)
OBJSS = $(SRCSS:%.s=%.o)	
BEROS = BerOS.elf
LLDFLAG = ld -m elf_i386 -T linker.ld 
RLDFLAG = ../objs/*.o -o ../build/boot/$(BEROS) -nostdlib

ifeq (,$(wildcard ../objs))
    $(shell mkdir ../objs)
endif

ifeq (,$(wildcard ../build))
    $(shell mkdir -p ../build)
endif

ifeq (,$(wildcard ../build/boot))
    $(shell mkdir ../build/boot)
endif

ifeq (,$(wildcard ../build/boot/grub))
    $(shell mkdir ../build/boot/grub)
endif

ifeq (,$(wildcard ../build/boot/grub/grub.cfg))
    $(shell cp grub/grub.cfg ../build/boot/grub/grub.cfg)
endif

build: $(BEROS)

$(BEROS): $(OBJSS) $(OBJSCC)
	@echo " "
	@echo "Creando BerOS..."
	$(LLDFLAG) $(RLDFLAG)
	@echo " "
	@echo "Listo :)"

%.o: %.c
	@echo " "
	@echo "Compilando "$<" ..."
	$(CC) $(LFLAG) $< -o $(patsubst core/%,../objs/%,$@) $(INCLUDES) $(RFLAG)

%.o: %.s
	@echo " "
	@echo "Compilando "$<" ..."
	$(ASM) $< -o $(patsubst core/%,../objs/%,$@)

cls:
	@echo " "
	@echo "Limpiando..."
	rm -rvf ../objs/*.o
	rm -rvf ../build/boot/$(BEROS) 
	@echo " "
