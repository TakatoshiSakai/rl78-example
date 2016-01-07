TARGET=main

CC=rl78-elf-gcc
LD=rl78-elf-ld 
AR=rl78-elf-ar
AS=rl78-elf-as
CP=rl78-elf-objcopy
OD=rl78-elf-objdump

BIN=$(TARGET).mot
SIGNED=$(BIN).signed
EXECUTABLE=$(TARGET).elf

STARTUP = reset_program.s

# We need to specify a linker script for the linker
LDSCRIPT = YRPBRL78L12.ld
LDFLAGS  = -M=YRPBRL78L12_LCD_Demo_SW.map,-e_PowerON_Reset,-N,-n,-stats,-traditional-format

SRC = $(STARTUP) \
      $(TARGET).c \
      hardware_setup.c \
      interrupt_handlers.c \
      vector_table.c \
      r_systeminit.c \
      lcd_panel.c \
      r_cg_lcd.c \
      r_cg_cgc.c \
      
INC = -I./ \

   
#  C source files
CFILES = $(filter %.c, $(SRC))
#  Assembly source files
ASMFILES = $(filter %.s, $(SRC))

# Object files
COBJ = $(CFILES:.c=.o)
SOBJ = $(ASMFILES:.s=.o)
OBJ  = $(COBJ) $(SOBJ)


MCFLAGS = -mmul=g13
OPTIMIZE=-O3 -ffloat-store -ffunction-sections -fno-inline-functions -fno-defer-pop -fno-peephole
DEBUG   =-g2
CFLAGS  =$(MCFLAGS) $(DEBUG)  $(OPTIMIZE) -Wall -MP -MMD

ASFLAGS = $(DEBUG)

# Defines to be passed to the compiler


all: $(BIN)

$(BIN): $(EXECUTABLE)
	$(CP) -O srec $^ $@

$(EXECUTABLE): $(OBJ) $(LDSCRIPT)
	$(CC) $(sort $(OBJ)) -T$(LDSCRIPT) -Wl,$(LDFLAGS) -nostartfiles -o $@

$(COBJ): %.o: %.c
	$(CC) -c $(DEFINES) $(INC) $(CFLAGS) $< -o $@

$(SOBJ): %.o: %.s
	$(AS) -c $(ASFLAGS) $< -o $@

clean:
	rm -f $(OBJ) $(BIN) $(EXECUTABLE) $(COBJ:.o=.d)

program: $(BIN)
	../../rl78flash/rl78flash -im3 /dev/ttyUSB0 -w $(BIN)
	

-include  $(COBJ:.o=.d)

.PHONY: clean program dfu
