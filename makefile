myset : main PreAssembler 
	gcc -Wall -pedantic -ansi main.o PreAssembler.o -o run
main:   main.c header.h
	gcc -c -Wall -pedantic -ansi main.c -o main.o
PreAssembler:    PreAssembler.c header.h
	gcc -c -Wall -pedantic -ansi PreAssembler.c -o PreAssembler.o


