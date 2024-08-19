#include <stdio.h>

char string[4]="abcd";
int data[2]={6,-9};
 
unsigned short BitsfirstLine(int opcode, int Source, int Destination) {
     unsigned short result=0;
  
     result |= (opcode & 0xF) << 11;
     result |= (0x1) << (7+Source);
     result |= (0x1) << (3+Destination);
     result |= 0x4;
    
    return result;
}
unsigned short BitsRegister( int SourceR, int DestinationR) {
    unsigned short result=0;
    result |= (SourceR & 0xF) << 5;
    result |= (DestinationR & 0xF) << 2;
    result |= 0x2;
    return result;
}
unsigned short BitsgetNumber(int num) {
    unsigned short result = (unsigned short)(num << 3);
    result &= 0x7FFF;
    result |= 0x4;
    return result;
}
unsigned short BitsDataNumber(int num) {
    unsigned short result = (unsigned short)(num );
    result &= 0x7FFF;
    return result;
}
unsigned short BitsDataString(char letter) {
    unsigned short result = (unsigned short)(letter);
    result &= 0x7FFF;
    return result;
}
unsigned short BitsNumberSymbol(int num,char E_or_R) {
    unsigned short result = (unsigned short)(num << 3);
   result &= 0x7FFF;
    if (E_or_R=='r')
    {
      result |= 0x2;
    }
    else if (E_or_R=='e')
    {
      result |= 0x1;
    }
    else
    {
        printf("error");
    }
    return result;
}

void printBinary(unsigned short num) {
    int i;
    for ( i = 15; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}
void printOctalToFile(const char *filename, unsigned short num) {
    
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    fprintf(file, "Octal representation of %d: %o\n", num, num);

    fclose(file);
}
void printString(int length){
    int i;
    char temp;
    unsigned short  letterInBits;
     for (i = 0; i <length ; i++) {
        temp=string[i];
        letterInBits=BitsDataString(temp);
        printf("\n %c: ",temp);
        printBinary(letterInBits);
     }
}
void printData(int length){
     int i,temp;
    unsigned short  letterInBits;
     for (i = 0; i <length ; i++) {
        temp=data[i];
        letterInBits=BitsDataNumber(temp);
        printf("\n %d: ",temp);
        printBinary(letterInBits);
     }

}

int main() {
    unsigned short bothR=0,oprtionCount=0,SourceR=3,DestinationR=-6;

    DestinationR=BitsDataNumber(-100);
    
    bothR=BitsDataString('a');
    printf("DestinationR in binary: ");
    printBinary(DestinationR);
    printf("bothR in binary: ");
    printBinary(bothR);
    printString(4);
    printData(2);
    
    return 0;
}
