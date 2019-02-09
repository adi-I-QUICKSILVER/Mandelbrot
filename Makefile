all: GUI CALCULATOR
	gcc -g main.c gui.o calc.o -o main `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`
	./main

GUI: 
	gcc -g -c gui.c -o gui.o `pkg-config --cflags gtk+-3.0`

CALCULATOR:
	gcc -g -c calculator.c -o calc.o