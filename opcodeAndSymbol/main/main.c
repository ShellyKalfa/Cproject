#include "symbol.h"

#define MAX_LINE_LENGTH 80

int main(int argc, char const *argv[])
{
    char line[MAX_LINE_LENGTH+1];
    char *continueLine=NULL;
    int McheckForOpration=-1,MwhichDirective=-1,McheckDataOperation=0,i;  
    int IC=100;
    int lineNmber=5,m=-1;
    int isCheckDirective=0;

 while (1)
 {
    /*symbol*/
    printf("\nEnter a line:\n ");
    if (fgets(line, sizeof(line), stdin) != NULL) {
      continueLine=thereIsSymbol(line,IC);
    } else {
        printf("Error reading input.\n");
    }
    if(continueLine==NULL){
      errorMessagesInLine(lineNmber,'r',0);
      return -1;
    }

    /*for me */
     printf("\n continueLine:");
       for (i = 0; i < strlen(continueLine); i++)
        {
          printf("%c", *(continueLine+i));
        }
        /*check directive*/
      isCheckDirective=checkDirective(continueLine);
      printf("isCheckDirective=%d",isCheckDirective);
      if(isCheckDirective==-1){
          errorMessagesInLine(lineNmber,'r',0);
         return -1;
      }
      if (isCheckDirective){
          MwhichDirective=whichDirective(isCheckDirective,continueLine);
          printf("MwhichDirective=%d \n",MwhichDirective);
          /*store info*/
          return 1;
      }
      if(!isCheckDirective){
        dataOperation* myOp = createDataOperation();
        McheckForOpration=checkForOpration(continueLine,myOp);
         printf("McheckForOpration=%d \n",McheckForOpration);
        if(McheckForOpration!=-1){
        printf("Opcode: %d\n", myOp->opcode);
        printf("Type Source Operand: %d\n", myOp->typeSourceOperand);
        printf("Type Destination Operand: %d\n", myOp->typeDestinationOperand);
        printf("Source Operand: %s\n", myOp->sourceOperand);
        printf("Destination Operand: %s\n", myOp->destinationOperand);
        McheckDataOperation = checkDataOperation(myOp);
        if(McheckDataOperation !=-1 ){
         m=getOprtion( myOp);
         printf("m=%d",m);
        }
       }
       
         freeDataOperation(myOp);
    }
 }
    
return 0;    
}