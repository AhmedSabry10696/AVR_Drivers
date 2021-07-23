FILENAME   = main
PORT       = /dev/cu.usbserial-00000000
DEVICE     = atmega32
PROGRAMMER = arduino
BAUD       = 115200

# -Wall for show warning -Os for code size optimization
COMPILE    = avr-gcc -Wall -Os -mmcu=$(DEVICE)

# write make in shell to compile upload clean
default: compile upload clean

# write make compile to compile only

# compilation steps:
# 1- compile all .c files to .o files using -c
# 2- link all .o files to .elf file
# 3- copy only .text and .data from elf file to new .hex file
# 4- print controller name and how much memory used from target memory 
compile:
	$(COMPILE) -c $(FILENAME).c -o $(FILENAME).o
	$(COMPILE) -o $(FILENAME).elf $(FILENAME).o
	avr-objcopy -j .text -j .data -O ihex $(FILENAME).elf $(FILENAME).hex 
	avr-size --format=avr --mcu=$(DEVICE) $(FILENAME).elf

# write make upload to upload your code to controller (make sure MCU connected to PORT)
upload:
	avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(FILENAME).hex:i

# write make clean to clean files that generated from building process
clean:
	rm $(FILENAME).o
	rm $(FILENAME).elf
	rm $(FILENAME).hex