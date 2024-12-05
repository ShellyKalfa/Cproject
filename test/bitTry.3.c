#include <stdio.h>

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

int main() {
    int bothR=0,oprtionCount=0,SourceR=3,DestinationR=-6;
    int opcode = 1;        
    int Source = -1;        
    int Destination = 0;  
    unsigned short result=0 ;
    if(Source==-1)
    {
       Source=0;
    }
    else{
       oprtionCount ++;
    }
    if(Destination==-1)
    {
       Destination=0;
    }else
    {
       oprtionCount ++;
    }
    if((Source==3||Source==2)&&(Destination==3||Destination==2)){
       bothR=1;
    }
    result= BitsfirstLine(opcode, Source, Destination);
    printf("Instruction in binary: ");
    printBinary(result);
    printf("\n");
    result= BitsNumberSymbol(103,'r');
    printf("BitsNumberSymbol: ");
    printBinary(result);
    printf("\n");

    if(!oprtionCount){
      return 1;
    }
    if(bothR){
     result= BitsRegister(SourceR, DestinationR);
     printf("print register: ");
     printBinary(result);
     return 2;
    }
    if(oprtionCount==1){
      switch (Destination)
      {
        case 0:
             result=BitsgetNumber(DestinationR);
             break;
        case 1:
             /* code */
             break;
        case 2:
             result= BitsRegister(SourceR, DestinationR);
             break;
        case 3:
            result= BitsRegister(SourceR, DestinationR);
        break;
    default:
        break;
    }
    printf("\n print DestinationR: ");
    printBinary(result);
    /*inportent*/
    printf("Octal representation of %d: %o\n", result, result);
     return 2;
 }
    switch (SourceR)
    {
     case 0:
        result=BitsgetNumber(SourceR);
        break;
    case 1:
        /* code */
        break;
    case 2:
        result= BitsRegister(SourceR, 0);
        break;
    case 3:
        result= BitsRegister(SourceR, 0);
        break;
    default:
        break;
    }
    printf("\n print SourceR: ");
    printBinary(result);
     switch (Destination)
      {
        case 0:
             result=BitsgetNumber(DestinationR);
             break;
        case 1:
             /* code */
             break;
        case 2:
             result= BitsRegister(0, DestinationR);
             break;
        case 3:
            result= BitsRegister(0, DestinationR);
        break;
    default:
        break;
    }
     printf("print DestinationR: ");
    printBinary(result);
    
    
    return 3;
}
