all: GUI CALCULATOR COLOR
	gcc -g main.c gui.o calc.o color.o -o main `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`
	./main

GUI: 
	gcc -g -c gui.c -o gui.o `pkg-config --cflags gtk+-3.0`

CALCULATOR:
	gcc -g -c calculator.c -o calc.o

COLOR:
	gcc -g -c color.c -o color.o