Assemble : main  handleError storag PreAssembler handleMacro
	gcc -Wall -pedantic -ansi main.o  handleError.o storag.o PreAssembler.o handleMacro.o -o run
main:   main.c header.h
	gcc -c -Wall -pedantic -ansi main.c -o main.o
handleError:    handleError.c header.h
	gcc -c -Wall -pedantic -ansi handleError.c -o handleError.o
handleMacro:    handleMacro.c header.h
	gcc -c -Wall -pedantic -ansi handleMacro.c -o handleMacro.o
storag:    storag.c header.h
	gcc -c -Wall -pedantic -ansi storag.c -o storag.o
PreAssembler:    PreAssembler.c header.h
	gcc -c -Wall -pedantic -ansi PreAssembler.c -o PreAssembler.o
clean:
	rm -f *.o run


