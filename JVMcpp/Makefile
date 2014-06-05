CC      	= g++
all:METODOS
	$(CC)  -o JVM.exe consolehelp.o data_control.o errors.o filereader.o java.o main.o -lm 
METODOS:
	gcc -std=c99 -Wall -lm -c consolehelp.c -o consolehelp.o
	gcc -std=c99 -Wall -lm -c data_control.c -o data_control.o
	gcc -std=c99 -Wall -lm -c errors.c -o errors.o
	gcc -std=c99 -Wall -lm -c filereader.c -o filereader.o
	gcc -std=c99 -Wall -lm -c java.c -o java.o
	gcc -std=c99 -Wall -lm -c main.c -o main.o
 
