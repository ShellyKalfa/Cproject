Assemble : main checkOpration dataDirectives dataDCorIC dataSymbol dataTObinary directive dataOpcode handleError filefirstPass firstPass oprationWork symbol secondPass  PreAssembler handleMacro storag
	gcc -Wall -pedantic -ansi main.o dataDirectives.o dataDCorIC.o dataSymbol.o checkOpration.o dataTObinary.o dataOpcode.o handleError.o directive.o firstPass.o oprationWork.o symbol.o secondPass.o filefirstPass.o  PreAssembler.o  handleMacro.o storag.o -o run
main:    main.c firstPassHeader.h
	gcc -c -Wall -pedantic -ansi main.c -o main.o
checkOpration:   checkOpration.c firstPassHeader.h
	gcc -c -Wall -pedantic -ansi checkOpration.c -o checkOpration.o
dataDirectives:   dataDirectives.c firstPassHeader.h
	gcc -c -Wall -pedantic -ansi dataDirectives.c -o dataDirectives.o
dataDCorIC:   dataDCorIC.c firstPassHeader.h
	gcc -c -Wall -pedantic -ansi dataDCorIC.c -o dataDCorIC.o
dataSymbol:   dataSymbol.c firstPassHeader.h
	gcc -c -Wall -pedantic -ansi dataSymbol.c -o dataSymbol.o
dataTObinary:   dataTObinary.c firstPassHeader.h
	gcc -c -Wall -pedantic -ansi dataTObinary.c -o dataTObinary.o
dataOpcode:   dataOpcode.c firstPassHeader.h
	gcc -c -Wall -pedantic -ansi dataOpcode.c -o dataOpcode.o
directive:   directive.c firstPassHeader.h
	gcc -c -Wall -pedantic -ansi directive.c -o directive.o
filefirstPass:   filefirstPass.c firstPassHeader.h
	gcc -c -Wall -pedantic -ansi filefirstPass.c -o filefirstPass.o
firstPass:   firstPass.c firstPassHeader.h
	gcc -c -Wall -pedantic -ansi firstPass.c -o firstPass.o
handleError:   handleError.c firstPassHeader.h
	gcc -c -Wall -pedantic -ansi handleError.c -o handleError.o
handleMacro:    handleMacro.c header.h
	gcc -c -Wall -pedantic -ansi handleMacro.c -o handleMacro.o
oprationWork:   oprationWork.c firstPassHeader.h
	gcc -c -Wall -pedantic -ansi oprationWork.c -o oprationWork.o
PreAssembler:    PreAssembler.c header.h
	gcc -c -Wall -pedantic -ansi PreAssembler.c -o PreAssembler.o
symbol:   symbol.c firstPassHeader.h
	gcc -c -Wall -pedantic -ansi symbol.c -o symbol.o
secondPass:   secondPass.c firstPassHeader.h
	gcc -c -Wall -pedantic -ansi secondPass.c -o secondPass.o
storag:    storag.c header.h
	gcc -c -Wall -pedantic -ansi storag.c -o storag.o
clean:
	rm -f *.o run




