Assemble : main  handleError storag PreAssembler handleMacro opration
	gcc -Wall -pedantic -ansi main.o  handleError.o storag.o PreAssembler.o handleMacro.o checkOpration.o -o run
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
opration:   checkOpration.c header.h
	gcc -c -Wall -pedantic -ansi checkOpration.c -o checkOpration.o
clean:
	rm -f *.o run


