#include "opration.h"

/*current opration code*/
int oprationCode=0;
/*current source Operand */
char *sourceOperand=NULL;
/*current source Operand */
char *destinationOperand=NULL;

int MinusOneTest=0;

/**/
int checkForOpration(char * line,dataOperation * newOpcode  ){
    int success=0,i,length=0,tokenLenght=0, opCodeNumber=-1;
    char *copyLine=NULL,*token,*opcode;
     /*error messages */
    char EFailedAllocate[] ="Failed to allocate memory";
    char ELineEmpty[] ="your line is empty";
    char EopcodeNotGood[] ="your opcode is not good";
    char EopcodeClean[] ="there should not be any thing after this opcode ";
    length=strlen(line);
    copyLine=(char*)malloc(sizeof(char) * (length+1));
    if(copyLine == NULL){
       errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'y');
       return -1;
    }
    strcpy(copyLine, line);
    copyLine[strlen(copyLine)]='\0';
    for ( i = 0; i < strlen(copyLine); i++)
    {
       printf(" c= %c ",*(copyLine+i));
    }
    token=strtok(copyLine," ");
     for ( i = 0; i < strlen(token); i++)
    {
       printf(" c= %c  ",*(token+i));
    }
    if(*(token+strlen(token)-1)=='\n'){
       printf("bla");
        opcode=(char*)malloc(sizeof(char) * (strlen(token)));
        tokenLenght=strlen(token)-1;
    }else{
        opcode=(char*)malloc(sizeof(char) * (strlen(token)+1));
         tokenLenght=strlen(token);
    }
    if(token==NULL || *token=='\n'|| length == 0 || tokenLenght == 1){
         errorMessagesWithText(ELineEmpty,strlen(ELineEmpty),'r');
         free(opcode);
         return -1; 
    }
    if(opcode == NULL){
       errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'y');
       free(copyLine);
       return -1;
    }
    strncpy(opcode,token,tokenLenght);
    opcode[strlen(opcode)+1]='\0';
    printf("\n");
    for ( i = 0; i < strlen(opcode); i++)
    {
       printf("c= %c",*(opcode+i));
    }
    opCodeNumber=lookForOpcode(opcode);
    if(opCodeNumber<0 ||opCodeNumber>15){
       errorMessagesWithText(EopcodeNotGood,strlen(EopcodeNotGood),'r');
       free(opcode);
       free(copyLine);
       return -1;
    }else {
      printf(" Opcode good ");
      setOpcode(newOpcode, opCodeNumber);
      if(opCodeNumber>=0&&opCodeNumber<=4){
        printf("0 to 4");
      }else if (opCodeNumber>4&&opCodeNumber<14)
      {
         printf("5 to 13");
         success=getOpration((token+strlen(token)+1),newOpcode,'d');
      }else{
          printf(" 14,15");
         success=checkEmptyLine((token+strlen(token)+1));
         if(success==-1){
             errorMessagesWithText(EopcodeClean,strlen(EopcodeClean),'r');
         }
      }
    }
    if(success !=-1){
        printf("Opcode: %d\n", newOpcode->opcode);
        printf("Type Source Operand: %d\n", newOpcode->typeSourceOperand);
        printf("Type Destination Operand: %d\n", newOpcode->typeDestinationOperand);
        printf("Source Operand: %s\n", newOpcode->sourceOperand);
        printf("Destination Operand: %s\n", newOpcode->destinationOperand);
        
    }
    
    free(opcode);
    free(copyLine);
    return success;
}
/*
function get text and return if there any thing else then space 
retrun : 1 right only space
-1 if there any thing else
*/
int checkEmptyLine(char * copyLine){
    int i;
    for ( i = 0; i < strlen(copyLine); i++)
      {
        if (!isspace(*(copyLine+i)))
        {
            return -1;
        }
      }
   return 1 ;
}
/*int getOprations(char * copyLine,dataOperation * newOpcode ){

}*/


/**/
int getOpration(char * copyLine,dataOperation * newOpcode,char whichOpration){
    int emptyLine=-1,typeOpration=0;
    char * token;
    /*error messages */
    char EopcodeClean[] ="there should not be any thing after this Opration ";
    char EoprationNotGood[] ="Your opration is not good ";
    char ENotGood[] ="something is not good ";
    char ENull[] ="your  Opration is null";

    token=strtok(copyLine," ");
    if(token== NULL || *token=='\n'||*token=='\t' ) {
             errorMessagesWithText(ENull,strlen(ENull),'r');
             return -1;
     }
    emptyLine=checkEmptyLine((token+strlen(token)+1));
    if(emptyLine==-1){
             errorMessagesWithText(EopcodeClean,strlen(EopcodeClean),'r');
             return -1;
         }

    typeOpration=checkOpration(token);
    printf(" typeOpration %d",typeOpration);
    if(typeOpration==-1){
             errorMessagesWithText(EoprationNotGood,strlen(EoprationNotGood),'r');
             return -1;
         }
    switch (whichOpration)
    {
    case 'd':
        /* destinationOperand */
        printf("\n destinationOperand \n");
        setTypeDestinationOperand(newOpcode,typeOpration);
        setDestinationOperand(newOpcode,token);
        break;
    case 's':
        /* sourceOperand */
         printf("\n sourceOperand \n");
         setTypeSourceOperand(newOpcode,typeOpration);
         setSourceOperand(newOpcode,token);
        break;
    
    default:
        errorMessagesWithText(ENotGood,strlen(ENotGood),'y');
        return -1;
        break;
    }
 
   return 1 ;
}
int checkOpration(char * token ){
    int i, number,typeOpcode=-1,checkSymbolNumber=0, length=0;
    char *text=NULL;
    /*error messages */
    char ERegisterNumber[] ="Register should be 0-7";
    char ERegisterLength[] ="Register should be r and number: 0-7 you have ";
 
      for ( i = 0; i < strlen(token); i++)
      {
        printf("d= %c",*(token+i));
      }
      if(token[strlen(token)-1]=='\n'){
          length=strlen(token)-1;
      }else
      {
           length=strlen(token);
      }
      
    if(token)
    switch (*token)
    {
    case '#':
        /* Opration =0 number */
        printf("# %c",*(token+1));
           number=getInteger((token+1),length-1);
           if(number==-1&&!MinusOneTest){
             return -1;
           }
           typeOpcode=0;
        break;
    case '*':
        /* Opration= 2 register */
        printf("strlen(token) %d",strlen(token));
        if(length-1!=2){
              errorMessagesWithText(ERegisterLength,strlen(ERegisterLength),'r');
             return -1;
        }else{
            if(*(token+1)=='r'){
                if(*(token+2)< '0'||*(token+2)>'7'){
                      errorMessagesWithText(ERegisterNumber,strlen(ERegisterNumber),'r');
                      return -1;
                    }
            }else{
                errorMessagesWithText(ERegisterNumber,strlen(ERegisterNumber),'r');
                return -1;
            }
        }
        typeOpcode=2;
        break;
    case 'r':
        /* Opration= 3 */
        if(length==2){
            printf(" =%d=",*(token+1));
              if(*(token+1)<'0'||*(token+1)>'7'){
                 errorMessagesWithText(ERegisterNumber,strlen(ERegisterNumber),'r');
                return -1; 
              }
              typeOpcode=3;
            
        }else{
            typeOpcode=1;
        }
        printf("3");
        break;
    
    default:
     /* Opration= 1 */
        printf("1");
         typeOpcode=1;
        break;
    }
    if(typeOpcode==1){
      text=(char*)malloc(sizeof(char) * (strlen(token)+1));
      strcpy(text,token);
      text[strlen(token)+1]='\0';
      checkSymbolNumber=checkSymbol(text,0);
      free(text);
      if(checkSymbolNumber==-1){
        return -1;
      }
    }

    return typeOpcode;
}

/* getInteger get  number 
and check if there ok 
if everthing is good  :the number (...,-1,0,1,....)
else return :-1
*warning: if is -1 and everthing ok send -1 and put it global 
*/
int getInteger(char *input ,int lengthInput){
      char *temp;
      int number=-1,countSpaces=0,numberFlage=0, flag=0,flageMines=0;
      size_t i;
      /*erorr messge*/
       char EnotNumber[] ="not a number";
       char EnullNumber[] ="Null number, you forgot to put number ";
       char EFailedAllocate[] ="Failed to allocate memory";
       char EforgotComma[] ="you forgot comma";
       char ETooManyHyphen[] ="Hyphen is not good";
       char EnumberoutOfRange[] ="Error: Number out of range for 15-bit 2's complement representation.\n";
       printf("\n you in c=%c , length =%d",*input,lengthInput);
       MinusOneTest=0;

       if(!lengthInput){
           printf("jjjj");
            errorMessagesWithText(EnullNumber,strlen(EnullNumber),'r');
            return number;
       }
      temp=(char*)malloc(sizeof(char) * (lengthInput+1));
      if(temp==NULL){
          errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'r');
          free(temp);
          return number;
      }
      temp[lengthInput+1]='\0';
      printf("\n");
      for (i = 0; i < lengthInput-1; i++)
      {
           printf("%c",input[i]);
         if(isdigit(input[i]) || isspace(input[i]) ||input[i]=='-' ){
            temp[i]=input[i];
            if(isspace(input[i])){
                countSpaces++;
            }
             if(input[i]=='-'){
                flageMines++;
                if(flageMines>1){
                  free(temp);
                  errorMessagesWithText(ETooManyHyphen,strlen(ETooManyHyphen),'r');
                  printf("did not good");
                  return-1;
                }
                if((i+1) == lengthInput-1 ){
                  free(temp);
                  errorMessagesWithText(ETooManyHyphen,strlen(ETooManyHyphen),'r');
                  printf("did not good");
                  return-1;
              
                }
                 if(!isdigit(input[i+1])){
                  free(temp);
                  errorMessagesWithText(ETooManyHyphen,strlen(ETooManyHyphen),'r');
                  printf("did not good");
                  return-1;

                }
            }
            if(isdigit(input[i])){
                if(!flag)
                {
                     numberFlage=countSpaces;
                     flag=1;
                }
                if(numberFlage!=countSpaces){
                  free(temp);
                  errorMessagesWithText(EforgotComma,strlen(EforgotComma),'r');
                  printf("did not good");
                  return-1;
                }
            }
          }else{
           free(temp);
           errorMessagesWithText(EnotNumber,strlen(EnotNumber),'r');
           printf("did not good");
           return-1;
          }
      }
      if(countSpaces==lengthInput-1&&(lengthInput-1)!=0){
          errorMessagesWithText(EnullNumber,strlen(EnullNumber),'r');
          free(temp);
          return number;
      }
    number= atoi(temp);
    if (number==-1){
        MinusOneTest=1;
    }
   if (number > 16383 || number < -16384) {
         errorMessagesWithText(EnumberoutOfRange,strlen(EnumberoutOfRange),'r');
         number= -1;
     }
    free(temp);
    return number;
 }

