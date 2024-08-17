Assemble : main  error opration checkOpration dataOpration symbol
	gcc -Wall -pedantic -ansi main.o handleError.o checkOpration.o oprationWork.o  dataOpcode.o symbol.o -o run
main:    start.c opration.h
	gcc -c -Wall -pedantic -ansi start.c -o main.o
error:   handleError.c opration.h
	gcc -c -Wall -pedantic -ansi handleError.c -o handleError.o
checkOpration:   checkOpration.c opration.h
	gcc -c -Wall -pedantic -ansi checkOpration.c -o checkOpration.o
opration:   oprationWork.c opration.h
	gcc -c -Wall -pedantic -ansi oprationWork.c -o oprationWork.o
dataOpration:   dataOpcode.c opration.h
	gcc -c -Wall -pedantic -ansi dataOpcode.c -o dataOpcode.o
symbol:   symbol.c opration.h
	gcc -c -Wall -pedantic -ansi symbol.c -o symbol.o


