#include "firstPassHeader.h"

/*current opration code*/
int oprationCode=0;
/*current source Operand */
char *sourceOperand=NULL;
/*current source Operand */
char *destinationOperand=NULL;

int MinusOneTest=0;

/**/
int checkForOpration(char * line,dataOperation * newOpcode  ){
    int success=0,length=0,tokenLenght=0, opCodeNumber=-1;
    char *copyLine=NULL,*token=NULL,*opcode=NULL;
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
    token=strtok(copyLine," ");
    
    if(*(token+strlen(token)-1)=='\n'||isspace(*(token+strlen(token)-1))){
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
    opcode[tokenLenght]='\0';
    
    opCodeNumber=lookForOpcode(opcode);
    if(opCodeNumber<0 ||opCodeNumber>15){
       errorMessagesWithText(EopcodeNotGood,strlen(EopcodeNotGood),'r');
       free(opcode);
       free(copyLine);
       return -1;
    }else {
      setOpcode(newOpcode, opCodeNumber);
      if(opCodeNumber>=0&&opCodeNumber<=4){
        success=splitOprations((token+strlen(token)+1),newOpcode);
      }else{
         if (opCodeNumber>4&&opCodeNumber<14)
         {
              success=getOpration((token+strlen(token)+1),newOpcode,'d');
         }else{
            success=checkEmptyLine((token+strlen(token)));
          }
         }
        }
         if(success==-1){
             errorMessagesWithText(EopcodeClean,strlen(EopcodeClean),'r');
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
int checkEmptyLine(char * endLine){
    int i=0;
    
    for ( i = 0; i < strlen(endLine); i++)
      {
        if (!isspace(*(endLine+i)))
        {
            return -1;
        }
      }
   return 1 ;
}
int splitOprations(char * copyLine,dataOperation * newOpcode ){
    int successDestination=0,successSource=0,lengthD=0,lengthS=0;
    char *findComma=NULL,*DestinationLine=NULL,*SourceLine=NULL;
      /*error messages */
    char ENotComma[] ="there should be 2 Oprations split by comma ";
    char ENULLOpration[] ="there your Opration is null ";
    char EFailedAllocate[] ="Failed to allocate memory";
    char EFailedSource[] ="Failed your OprationSource is not good ";
    char EFailedDestination[] ="Failed  your OprationDestination is not good";

     
    if(copyLine == NULL||*copyLine=='\n'||*copyLine=='\0'){
       errorMessagesWithText(ENULLOpration,strlen(ENULLOpration),'r');
       return -1;
    }

    findComma=strchr(copyLine, ',');
    if(findComma==NULL){
             errorMessagesWithText(ENotComma,strlen(ENotComma),'r');
             return -1;
    }
    lengthS=findComma-copyLine;
    lengthD=strlen(copyLine)-(findComma-copyLine)-1;
    if(lengthS<1||lengthD<1){
        errorMessagesWithText(ENULLOpration,strlen(ENULLOpration),'r');
        return -1;
    }
    SourceLine=(char*)malloc(sizeof(char) * (lengthS+1));
    if(SourceLine==NULL){
        errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'y');
        return -1;
    }
    strncpy(SourceLine,copyLine,lengthS);
    SourceLine[lengthS]='\0';
    successSource=getOpration(SourceLine, newOpcode,'s');
    free(SourceLine);
    if(successSource ==-1){
        errorMessagesWithText(EFailedSource,strlen(EFailedSource),'r');
        return -1;
    }
    DestinationLine=(char*)malloc(sizeof(char) * (lengthD+1));
    if(DestinationLine==NULL){
        errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'y');
        return -1;
    }
    strncpy(DestinationLine,findComma+1,lengthD);
    DestinationLine[lengthD]='\0';
    successDestination=getOpration(DestinationLine, newOpcode,'d');
    free(DestinationLine);
    if(successDestination == -1){
        errorMessagesWithText(EFailedDestination,strlen(EFailedDestination),'r');
        return -1;
    }

     return 1;
}


/**/
int getOpration(char * copyLine,dataOperation * newOpcode,char whichOpration){
    int emptyLine=-1,typeOpration=0;
    char * token=NULL;
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
    emptyLine=checkEmptyLine((token+strlen(token)));
    if(emptyLine==-1){
             errorMessagesWithText(EopcodeClean,strlen(EopcodeClean),'r');
             return -1;
         }

    typeOpration=checkOpration(token);
    if(typeOpration==-1){
             errorMessagesWithText(EoprationNotGood,strlen(EoprationNotGood),'r');
             return -1;
         }
    switch (whichOpration)
    {
    case 'd':
        /* destinationOperand */
        setTypeDestinationOperand(newOpcode,typeOpration);
        setDestinationOperand(newOpcode,token);
        break;
    case 's':
        /* sourceOperand */
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
    int  number=-1,typeOpcode=-1,checkSymbolNumber=0, length=0;
    char *text=NULL;
    /*error messages */
    char ERegisterNumber[] ="Register should be 0-7";
    char ERegisterLength[] ="Register should be r and number: 0-7 you have ";
 
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
           number=getInteger((token+1),length-1);
           if(number==-1&&!MinusOneTest){
             return -1;
           }
           typeOpcode=0;
        break;
    case '*':
        /* Opration= 2 register */
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
              if(*(token+1)<'0'||*(token+1)>'7'){
                 errorMessagesWithText(ERegisterNumber,strlen(ERegisterNumber),'r');
                return -1; 
              }
              typeOpcode=3;
            
        }else{
            typeOpcode=1;
        }
        break;
    
    default:
     /* Opration= 1 */
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


