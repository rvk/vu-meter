vu.o: vu.c
	avr-gcc -mmcu=atmega8 -Os vu.c -o vu.o

vu.hex: vu.o
	avr-objcopy -j .text -j .data -O ihex vu.o vu.hex

burn: vu.hex
	avrdude -c buspirate -p m8 -P /dev/ttyUSB0 -v -U flash:w:vu.hex

clean:
	rm vu.o vu.hex
