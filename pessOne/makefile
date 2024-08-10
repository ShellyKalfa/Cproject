Assemble : main firstPass error
	gcc -Wall -pedantic -ansi main.o firstPass.o handleError.o -o run
main:    main.c symbol.h
	gcc -c -Wall -pedantic -ansi main.c -o main.o
firstPass:   firstPass.c symbol.h
	gcc -c -Wall -pedantic -ansi firstPass.c -o firstPass.o
error:   handleError.c symbol.h
	gcc -c -Wall -pedantic -ansi handleError.c -o handleError.o



