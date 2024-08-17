#include "symbol.h"

/*
this function return the opcode of the function 
else return -1 (if it not in the opcodes)
 */
int lookForOpcode(char *input)
{
    int returnOperation = -1;
    int flag = 0;
   
    if (strstr(input, "mov") != NULL&&(strlen(input)==strlen("mov")))
    {
        flag += 1;
        returnOperation= 0;
    }
    if (strstr(input, "cmp") != NULL&&(strlen(input)==strlen("cmp")))
    {
        flag += 1;
        returnOperation= 1;
    }
    if (strstr(input, "add") != NULL&&(strlen(input)==strlen("add")))
    {
        flag += 1;
        returnOperation= 2;
    }
    if (strstr(input, "sub") != NULL&&(strlen(input)==strlen("sub")))
    {
        flag += 1;
        returnOperation= 3;
    }
    if (strstr(input, "lea") != NULL&&(strlen(input)==strlen("lea")))
    {
        flag += 1;
        returnOperation= 4;
    }
    if (strstr(input, "clr") != NULL&&(strlen(input)==strlen("clr")))
    {
        flag += 1;
        returnOperation= 5;
    }
    if (strstr(input, "not") != NULL&&(strlen(input)==strlen("not")))
    {
        flag += 1;
        returnOperation= 6;
    }
    if (strstr(input, "inc") != NULL&&(strlen(input)==strlen("inc")))
    {
        flag += 1;
        returnOperation= 7;
    }
    if (strstr(input, "dec") != NULL&&(strlen(input)==strlen("dec")))
    {
        flag += 1;
        returnOperation= 8;
    }
    if (strstr(input, "jmp") != NULL&&(strlen(input)==strlen("jmp")))
    {
        flag += 1;
        returnOperation= 9;
    }
    if (strstr(input, "bne") != NULL&&(strlen(input)==strlen("bne")))
    {
        flag += 1;
        returnOperation= 10;
    }
    if (strstr(input, "red") != NULL&&(strlen(input)==strlen("red")))
    {
        flag += 1;
        returnOperation= 11;
    }if (strstr(input, "prn") != NULL&&(strlen(input)==strlen("prn")))
    {
        flag += 1;
        returnOperation= 12;
    }
    if (strstr(input, "jsr") != NULL&&(strlen(input)==strlen("jsr")))
    {
        flag += 1;
        returnOperation= 13;
    }
     if (strstr(input, "rts") != NULL&&(strlen(input)==strlen("rts")))
    {
        flag += 1;
        returnOperation= 14;
    }
    if (strstr(input, "stop") != NULL&&(strlen(input)==strlen("stop")))
    {
        flag += 1;
        returnOperation= 15;
    }
    if (strstr(input, "data") != NULL&&(strlen(input)==strlen("data")))
    {
        flag += 1;
        returnOperation= 16;
    }
    if (strstr(input, "string") != NULL&&(strlen(input)==strlen("string")))
    {
        flag += 1;
        returnOperation= 17;
    }
     if (strstr(input, "extern") != NULL&&(strlen(input)==strlen("extern")))
    {
        flag += 1;
        returnOperation= 18;
    }
     if (strstr(input, "entry") != NULL&&(strlen(input)==strlen("entry")))
    {
        flag += 1;
        returnOperation= 19;
    }
    if (strstr(input, "macr") != NULL &&(strlen(input)==strlen("macr")))
    {
        flag += 1;
        returnOperation= 20;
    }
    if (strstr(input, "endmacr") != NULL&&(strlen(input)==strlen("endmacr")))
    {
        flag += 1;
        returnOperation= 21;
    }
    /* check for registers  */
    if (strchr(input,'r') != NULL&&(strlen(input)==2))
    { 
        if(*(input+1)>= '0'&&*(input+1)<='7'){
        flag += 1;
        returnOperation= 22;
        }
    }

    if ( flag > 1)
    {
        returnOperation= -1;
    }
    
    return returnOperation;
}

/*
function chack the The addressing method
return 1 if everthing good
else return -1 
 */
int checkDataOperation(dataOperation * myOp){
  int Opcode=-1, typeDestination=-2,typeSource=-2;
    /*erorr messge */
    char EinstructionNotCurrect[] ="your instruction is not currect";
    char ENotCurrectTypeDestinationOperand[] ="your Destination Operand Type is not currect";
    char ENotCurrectTypeSourceOperand[] ="your Source Operand Type is not currect";
    char EopcodeNotGood[] ="your opcode is not currect";

    Opcode=myOp->opcode;
    typeDestination=myOp->typeDestinationOperand;
    typeSource=myOp->typeSourceOperand;
    printf("opcode= %d ,typeSource=%d, typeDestination=%d",Opcode,typeSource,typeDestination);
    
    if(Opcode==-1){
       errorMessagesWithText(EinstructionNotCurrect,strlen(EinstructionNotCurrect),'r');
       return -1;
    } 
    switch (Opcode)
    {
    case 0:
        /* move  */
        if( typeDestination == 0){
         errorMessagesWithText(ENotCurrectTypeDestinationOperand,strlen(ENotCurrectTypeDestinationOperand),'r');
         return -1;
        }
        break;
    case 2:
        /* add  */
        if( typeDestination == 0){
         errorMessagesWithText(ENotCurrectTypeDestinationOperand,strlen(ENotCurrectTypeDestinationOperand),'r');
         return -1;
        }
        break;
    case 3:
        /* sub  */
        if( typeDestination == 0){
         errorMessagesWithText(ENotCurrectTypeDestinationOperand,strlen(ENotCurrectTypeDestinationOperand),'r');
         return -1;
        }
        break;
    case 4:
        /* lea  */
        if( typeDestination == 0){
         errorMessagesWithText(ENotCurrectTypeDestinationOperand,strlen(ENotCurrectTypeDestinationOperand),'r');
         return -1;
        }
        if( typeSource != 1){
         errorMessagesWithText(ENotCurrectTypeSourceOperand,strlen(ENotCurrectTypeSourceOperand),'r');
         return -1;
        }
        break;
    case 5:
        /* clr  */
        if( typeDestination == 0){
         errorMessagesWithText(ENotCurrectTypeDestinationOperand,strlen(ENotCurrectTypeDestinationOperand),'r');
         return -1;
        }
        if( typeSource != -1){
         errorMessagesWithText(ENotCurrectTypeSourceOperand,strlen(ENotCurrectTypeSourceOperand),'r');
         return -1;
        }
        break;
    case 6:
         /* not  */
        if( typeDestination == 0){
         errorMessagesWithText(ENotCurrectTypeDestinationOperand,strlen(ENotCurrectTypeDestinationOperand),'r');
         return -1;
        }
        if( typeSource !=-1){
         errorMessagesWithText(ENotCurrectTypeSourceOperand,strlen(ENotCurrectTypeSourceOperand),'r');
         return -1;
        }
        break;
    case 7:
        /* inc  */
        if( typeDestination==0){
         errorMessagesWithText(ENotCurrectTypeDestinationOperand,strlen(ENotCurrectTypeDestinationOperand),'r');
         return -1;
        }
        if( typeSource !=-1){
         errorMessagesWithText(ENotCurrectTypeSourceOperand,strlen(ENotCurrectTypeSourceOperand),'r');
         return -1;
        }
        break;
    case 8:
        /* dec  */
        if( typeDestination==0){
         errorMessagesWithText(ENotCurrectTypeDestinationOperand,strlen(ENotCurrectTypeDestinationOperand),'r');
         return -1;
        }
        if( typeSource !=-1){
         errorMessagesWithText(ENotCurrectTypeSourceOperand,strlen(ENotCurrectTypeSourceOperand),'r');
         return -1;
        }
        break;
    case 9:
        /* jmp  */
        if( typeDestination==0|| typeDestination==3){
         errorMessagesWithText(ENotCurrectTypeDestinationOperand,strlen(ENotCurrectTypeDestinationOperand),'r');
         return -1;
        }
        if( typeSource !=-1){
         errorMessagesWithText(ENotCurrectTypeSourceOperand,strlen(ENotCurrectTypeSourceOperand),'r');
         return -1;
        }
        break;
    case 10:
        /* bne  */
        if( typeDestination==0|| typeDestination==3){
         errorMessagesWithText(ENotCurrectTypeDestinationOperand,strlen(ENotCurrectTypeDestinationOperand),'r');
         return -1;
        }
        if( typeSource !=-1){
         errorMessagesWithText(ENotCurrectTypeSourceOperand,strlen(ENotCurrectTypeSourceOperand),'r');
         return -1;
        }
        break;
    case 11:
        /* red  */
        if( typeDestination==0){
         errorMessagesWithText(ENotCurrectTypeDestinationOperand,strlen(ENotCurrectTypeDestinationOperand),'r');
         return -1;
        }
        if( typeSource !=-1){
         errorMessagesWithText(ENotCurrectTypeSourceOperand,strlen(ENotCurrectTypeSourceOperand),'r');
         return -1;
        }
        break;
    case 12:
        /* prn  */
        if( typeSource !=-1){
         errorMessagesWithText(ENotCurrectTypeSourceOperand,strlen(ENotCurrectTypeSourceOperand),'r');
         return -1;
        }
        break;
    case 13:
        /* jsr  */
        if( typeSource !=-1){
         errorMessagesWithText(ENotCurrectTypeSourceOperand,strlen(ENotCurrectTypeSourceOperand),'r');
         return -1;
        }
        if( typeDestination==0|| typeDestination==3){
         errorMessagesWithText(ENotCurrectTypeDestinationOperand,strlen(ENotCurrectTypeDestinationOperand),'r');
         return -1;
        }
        break;
    case 14:
        /* rts  */
        if( typeSource !=-1){
         errorMessagesWithText(ENotCurrectTypeSourceOperand,strlen(ENotCurrectTypeSourceOperand),'r');
         return -1;
        }
        if( typeDestination!=-1){
         errorMessagesWithText(ENotCurrectTypeDestinationOperand,strlen(ENotCurrectTypeDestinationOperand),'r');
         return -1;
        }
        break;
    case 15:
        /* stop  */
        if( typeSource !=-1){
         errorMessagesWithText(ENotCurrectTypeSourceOperand,strlen(ENotCurrectTypeSourceOperand),'r');
         return -1;
        }
        if( typeDestination!=-1){
         errorMessagesWithText(ENotCurrectTypeDestinationOperand,strlen(ENotCurrectTypeDestinationOperand),'r');
         return -1;
        }
        break;

    default:
        if( typeDestination<0 || typeDestination>15){
         errorMessagesWithText(EopcodeNotGood,strlen(EopcodeNotGood),'r');
         return -1;
        }
        break;
    }
  return 1;
}