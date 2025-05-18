rem @echo off
del main.elf main.hex
msp430-gcc -Os -Wall -mmcu=msp430f2001 -o main.elf main.c
msp430-objcopy -O ihex main.elf main.hex
pause