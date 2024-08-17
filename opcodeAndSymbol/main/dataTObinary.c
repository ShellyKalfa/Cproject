#include "symbol.h"

int getOprtion(dataOperation * myOp){
    int opcode=0,Source=0,Destination=0,bothR=0,oprtionCount=0,DestinationR=-1,SourceR=-1;
    unsigned short realShort=0;
    unsigned short *lines=NULL;
    unsigned short *tempLines;
     /*error messages */
    char EFailedAllocate[] ="Failed to allocate memory";

    opcode=myOp->opcode;
    Source=myOp->typeSourceOperand;
    Destination=myOp->typeDestinationOperand;
    
    lines = (unsigned short*)malloc(sizeof(unsigned short));
    if(lines==NULL){
      errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'y');
      return -1;
    }
    DestinationR=getOprtionNumber(Source ,myOp->sourceOperand);
    SourceR=getOprtionNumber(Destination ,myOp->destinationOperand);
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
    realShort=BitsfirstLine( opcode, Source, Destination);
    lines[0]=realShort;
     if(!oprtionCount){
         /* store */
      free(lines);
      return 1;
    }
    if(bothR){oprtionCount=1;}
    tempLines = (unsigned short*)realloc(lines, sizeof(unsigned short) * (oprtionCount+1));
    if(tempLines == NULL){
        free(lines);
        return -1;
    }
    lines = tempLines;
     if(bothR){
     lines[1]= BitsRegister(SourceR, DestinationR);
      /* store */
      free(lines);
      return 2;
    }
    if(oprtionCount==1){
      switch (Destination)
      {
        case 0:
             lines[1]=BitsgetNumber(DestinationR);
             break;
        case 1:
             /* code */
             break;
        case 2:
             lines[1]= BitsRegister(SourceR, DestinationR);
             break;
        case 3:
            lines[1]= BitsRegister(SourceR, DestinationR);
        break;
    default:
        break;
    }
       /* store */
     free(lines);
     return 2;
 }else
 {

 switch (SourceR)
    {
     case 0:
        lines[1]=BitsgetNumber(SourceR);
        break;
    case 1:
        /* code */
        break;
    case 2:
        lines[1]= BitsRegister(SourceR, 0);
        break;
    case 3:
        lines[1]= BitsRegister(SourceR, 0);
        break;
    default:
        break;
    }
     switch (Destination)
      {
        case 0:
             lines[2]=BitsgetNumber(DestinationR);
             break;
        case 1:
             /* code */
             break;
        case 2:
             lines[2]= BitsRegister(0, DestinationR);
             break;
        case 3:
            lines[2]= BitsRegister(0, DestinationR);
        break;
    default:
        break;
    }

    /* store */
    free(lines);
    return 3;
 }
 /* store */
 free(lines);
 return 0;

}
int getOprtionNumber(int type ,char *numberOp){
    int placeNumberStart=0,realNumber=0;
    if(type==-1){
     return 0;
    }
    switch (type)
    {
    case 0:
        placeNumberStart=1;
        break;
    case 2:
        placeNumberStart=2;
        break; 
    case 3:
        placeNumberStart=1;
        break;          
    default:
        break;
    }
    realNumber=atoi((numberOp+placeNumberStart));
 return realNumber;
}

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

void printBinary(unsigned short num) {
    int i;
    for ( i = 15; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
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


void printOctalToFile(const char *filename, unsigned short num) {
    
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    fprintf(file, "Octal representation of %d: %o\n", num, num);

    fclose(file);
}