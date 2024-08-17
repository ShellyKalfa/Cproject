Assemble : main PreAssembler
	gcc -Wall -pedantic -ansi main.o PreAssembler.o  -o run
main:    macro.c storage.h
	gcc -c -Wall -pedantic -ansi macro.c -o main.o
PreAssembler:   storage.c storage.h
	gcc -c -Wall -pedantic -ansi storage.c -o PreAssembler.o



