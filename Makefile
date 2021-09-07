#!/usr/bin/env make -f
# https://www.gnu.org/software/make/manual/html_node/Special-Targets.html
.PHONY: all clean

TARGET=pov_sensor_num
MCU = attiny2313
F_CPU = 8000000 # 8 MHz
#AVRDUDE_PORT = lpt1 # programmer connected to windows parallel
#AVRDUDE_PORT = com1 # programmer connected to serial
AVRDUDE_PORT = /dev/ttyUSB0 # programmer connected to usb serial port
AVRDUDE_PROGRAMMER = dasa
AVRDUDE_TIMING = 500

SRC=$(wildcard *.c)
HEX = $(SRC:.c=.hex)
OBJ = $(SRC:.c=.o) $(ASRC:.S=.o)
LST = $(ASRC:.S=.lst) $(SRC:.c=.lst)

# Default target.
all: program-$(TARGET) eeprom-$(TARGET)

# Program the device w/various programs
program-$(TARGET): $(TARGET).hex

eeprom-$(TARGET): $(TARGET).eep

gen.h: gen_pov
	./gen_pov $(TEXT) | tee gen.h

gen_pov: gen_pov.c
	gcc -o $@ $<

# this is necessary if you're burning the AVR for the first time...
# sets the proper fuse for 8MHz internal oscillator with no clk div
burn-fuse:
	$(AVRDUDE) $(AVRDUDE_FLAGS) -u -U lfuse:w:0xe4:m

# this programs the dependant hex file using our default avrdude flags
program-%:
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH)$<

eeprom-%:
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_EEPROM)$<

FORMAT = ihex # create a .hex file

OPT = s # assembly-level optimization

# Optional compiler flags.
#  -g:        generate debugging information (for GDB, or for COFF conversion)
#  -O*:       optimization level
#  -f...:     tuning, see gcc manual and avr-libc documentation
#  -Wall...:  warning level
#  -Wa,...:   tell GCC to pass this to the assembler.
#  -ahlms:    create assembler listing
CFLAGS = -g -O$(OPT) \
	-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums \
	-Wall -Wstrict-prototypes \
	-DF_CPU=$(F_CPU) \
	-Wa,-adhlns=$(<:.c=.lst) \
	$(patsubst %,-I%,$(EXTRAINCDIRS)) \
	-mmcu=$(MCU)

# Set a "language standard" compiler flag.
CFLAGS += -std=gnu99

# Optional assembler flags.
#  -Wa,...:   tell GCC to pass this to the assembler.
#  -ahlms:    create listing
#  -gstabs:   have the assembler create line number information; note that
#             for use in COFF files, additional information about filenames
#             and function names needs to be present in the assembler source
#             files -- see avr-libc docs [FIXME: not yet described there]
ASFLAGS = -Wa,-adhlns=$(<:.S=.lst),-gstabs

# Optional linker flags.
#  -Wl,...:   tell GCC to pass this to linker.
#  -Map:      create map file
#  --cref:    add cross reference to map file
LDFLAGS = -Wl,-Map=$(TARGET).map,--cref

# Programming support using avrdude.
AVRDUDE = avrdude

# Programming support using avrdude. Settings and variables.
AVRDUDE_WRITE_FLASH = -U flash:w:
AVRDUDE_WRITE_EEPROM = -U eeprom:w:
AVRDUDE_FLAGS = -p $(MCU) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER) -i $(AVRDUDE_TIMING)

# Define programs and commands.
CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size
REMOVE = rm -f

# Combine all necessary flags and optional flags.
# Add target processor to flags.
ALL_CFLAGS = -I. $(CFLAGS)
ALL_ASFLAGS = -mmcu=$(MCU) -I. -x assembler-with-cpp $(ASFLAGS)

# Display compiler version information.
gccversion:
	@$(CC) --version

# Create final output files (.hex) from ELF output file.
%.hex: %.elf
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

#
%.eep: %.elf
	$(OBJCOPY) --only-section=.eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --output-target=ihex $< $@

%.elf: %.o
	$(CC) $(ALL_CFLAGS) $< --output $@ $(LDFLAGS)

# Compile: create object files from C source files.
%.o: %.c
	$(CC) -c $(ALL_CFLAGS) $< -o $@

# Compile: create assembler files from C source files.
%.s: %.c
	$(CC) -S $(ALL_CFLAGS) $< -o $@

# Assemble: create object files from assembler source files.
%.o: %.S
	$(CC) -c $(ALL_ASFLAGS) $< -o $@

# Target: clean project.
clean:
	$(REMOVE) *.hex *.lst *.obj *.elf *.o *.map *.eep

dbg:
	$(foreach remote,$(shell git remote),$(shell git push $(remote)))

