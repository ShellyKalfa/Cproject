#include "firstPassHeader.h"

int getOprtion(dataOperation * myOp){
    int opcode=0,Source=0,Destination=0,bothR=0,oprtionCount=0,DestinationR=-1,SourceR=-1,isLabelOk=-1;
    char *nameSource=NULL,*nameDestination=NULL;
    unsigned short realShort=0;
    unsigned short *lines=NULL;
    unsigned short *tempLines=NULL;
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
    SourceR =getOprtionNumber(Source ,myOp->sourceOperand);
    
    DestinationR=getOprtionNumber(Destination ,myOp->destinationOperand);
    if(Source==1){
        nameSource=myOp->sourceOperand;
    }
    if(Destination==1){
       nameDestination=myOp->destinationOperand;
    }
    if(Source!=-1)
    {
       oprtionCount ++;
    }
    if(Destination!=-1)
    {
       oprtionCount ++;
    }
    if((Source==3||Source==2)&&(Destination==3||Destination==2)){
       bothR=1;
    }
    realShort=BitsfirstLine( opcode, Source, Destination);
    /*adding Bitsfirst*/
    addLineToIClist(myIClist, realShort);
    
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
    lines[1]=0;
     if(bothR){
     lines[1]= BitsRegister(SourceR, DestinationR);
     /*adding Bitsfirst*/
     addLineToIClist(myIClist, lines[1]);
      free(lines);
      if(tempLines!=lines){free(tempLines);}
      return 2;
    }
    if(oprtionCount==1){
         
      switch (Destination)
      {
        case 0:
             lines[1]=BitsgetNumber(DestinationR);
             break;
        case 1:
             isLabelOk=saveSymbolForSymbolLines(myIClist,nameDestination);
             lines[1]=0;
             if(isLabelOk==-1){
                 free(lines);
                 return -1;
            }
             break;
        case 2:
             lines[1]= BitsRegister(0, DestinationR);
             break;
        case 3:
            lines[1]= BitsRegister(0, DestinationR);
        break;
    default:
        break;
    }
      addLineToIClist(myIClist, lines[1]);
     free(lines);
     if(tempLines!=lines){free(tempLines);}
     return 2;
 }else
 {

 switch (Source)
    {
     case 0:
        lines[1]=BitsgetNumber(SourceR);
        break;
    case 1:
       isLabelOk=saveSymbolForSymbolLines(myIClist,nameSource);
        lines[1]=0;
        if(isLabelOk==-1){
                 free(lines);
                 return -1;
            }
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
    addLineToIClist(myIClist, lines[1]);
   
     switch (Destination)
      {
        case 0:
             lines[2]=BitsgetNumber(DestinationR);
             break;
        case 1:
             isLabelOk=saveSymbolForSymbolLines(myIClist,nameDestination);
             lines[2]=0;
             if(isLabelOk==-1){
                 free(lines);
                 return -1;
            }
             break;
        case 2:   
             lines[2]= BitsRegister(0, DestinationR);
             break;
        case 3:       
            lines[2]= BitsRegister(0, DestinationR);
        break;
    default:
    printf("\nsomthing is wrong");
        break;
    }
   
   addLineToIClist(myIClist, lines[2]);
    /* store */
    free(lines);
    if(tempLines!=lines){free(tempLines);}
    return 3;
 }
 /* store */
 if(tempLines!=lines){free(tempLines);}
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
int saveSymbolForSymbolLines(IClist *list , char *nameSymbol){
  int i ,length=0,succses=-1;
  char *tempNameSymbol=NULL;
  char *SymbolLines=NULL;
  char EFailedAllocate[] ="Failed to allocate memory";
   for (i = 0; i < strlen(nameSymbol); i++) {
        if (!isspace(nameSymbol[i])) {
            length++;
            
            tempNameSymbol = (char *)realloc(SymbolLines, sizeof(char) * (length + 1));
            if (tempNameSymbol == NULL) {
                errorMessagesWithText(EFailedAllocate, strlen(EFailedAllocate), 'r');
                free(SymbolLines); 
                return -1;
            }
            SymbolLines = tempNameSymbol;
            SymbolLines[length - 1] = nameSymbol[i];  
        }
    }
    SymbolLines[length]='\0';
    if(SymbolLines==NULL){
        free(tempNameSymbol);
       return -1;
    }
   succses= addSymbolToHeadSymbolLinesToFill(list ,SymbolLines);
  if(SymbolLines != tempNameSymbol)
  { free(tempNameSymbol);}
   free(SymbolLines);
   return succses;
}

unsigned short BitsfirstLine(int opcode, int Source, int Destination) {
     unsigned short result=0;
     result &= 0x7FFF;
     result |= (opcode & 0xF) << 11;
     if(Source!=-1)
     {result |= (0x1) << (7+Source);}
     if(Destination!=-1)
     {result |= (0x1) << (3+Destination);}
     result |= 0x4;
    
    
    return result;
}
unsigned short BitsRegister( int SourceR, int DestinationR) {
    unsigned short result=0;
    if(SourceR!=-1)
   { result |= (SourceR & 0xF) << 6;}
    if(DestinationR!=-1)
    {result |= (DestinationR & 0xF) << 3;}
    result |= 0x4;
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


void printOctalToFile(const char *filename, unsigned short num) {
    
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    fprintf(file, "Octal representation of %d: %o\n", num, num);

    fclose(file);
}
int putLineInDC(DClist * listDC,int directiveNumber,int length){
     int sucsses=-1;
    /*error messages*/
    char EdcUnknow[] ="Failed your dc is unknow";
     if(listDC== NULL)
     {
         errorMessagesWithText(EdcUnknow,strlen(EdcUnknow),'r');
         return -1;
     }
    switch (directiveNumber)
    {
    case 16:
        /* data */
        sucsses = printData(listDC,length);
        break;
    case 17:
        /* string */
        sucsses = printString(listDC,length);
        break;
    case 18:
        /* extern */
        sucsses=1;
        break;
    case 19:
        /* entry */
        sucsses=1;
        break;
    default:
        printf("somthing else");
        break;
    }
    return sucsses ;
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
unsigned short BitsSymbolLineInIC(int place,char E_or_R) {
   
    unsigned short result = (unsigned short)(place<<3);
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
int printString(DClist * listDC,int length){
    int i, succsses=-1;
    char tempLetter;
    unsigned short  letterInBits;
     for (i = 0; i <length ; i++) {
        tempLetter=string[i];
        letterInBits=BitsDataString(tempLetter);
        succsses=addLineToDClist(listDC, letterInBits);
        if(succsses==-1){
           return -1;
        }
     }
        letterInBits=BitsDataString(0);
        succsses=addLineToDClist(listDC, letterInBits);
     return 1;
}
int printData(DClist * listDC,int length){
    int i,temp,succsses=-1;
    unsigned short  letterInBits;
     for (i = 0; i <length ; i++) {
        temp=data[i];
        letterInBits=BitsDataNumber(temp);
        succsses=addLineToDClist(listDC, letterInBits);
        if(succsses==-1){
           return -1;
        }
     }
     return 1;
}
void printBinary(unsigned short num) {
    int i;
    for ( i = 15; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}
