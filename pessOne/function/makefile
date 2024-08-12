Assemble : main firstPass error opration directive storeFirst
	gcc -Wall -pedantic -ansi main.o firstPass.o handleError.o checkOpration.o directive.o storeFirstPess.o -o run
main:    start.c symbol.h
	gcc -c -Wall -pedantic -ansi start.c -o main.o
firstPass:   symbol.c symbol.h
	gcc -c -Wall -pedantic -ansi symbol.c -o firstPass.o
error:   handleError.c symbol.h
	gcc -c -Wall -pedantic -ansi handleError.c -o handleError.o
opration:   checkOpration.c symbol.h
	gcc -c -Wall -pedantic -ansi checkOpration.c -o checkOpration.o
directive:   directive.c symbol.h
	gcc -c -Wall -pedantic -ansi directive.c -o directive.o
storeFirst:  storeFirstPess.c symbol.h
	gcc -c -Wall -pedantic -ansi storeFirstPess.c -o storeFirstPess.o


