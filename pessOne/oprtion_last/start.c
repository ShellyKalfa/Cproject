#include "opration.h"

#define MAX_LINE_LENGTH 80



int main(int argc, char const *argv[])
{
    char line[MAX_LINE_LENGTH+1];
    char *continueLine=NULL;
    int m=-1;
     int directive=-1;
    /*
    int IC=100;
    int lineNmber=5;
    */
    /*error messages*/


    /*symbol*/
    if(directive==-1){
       dataOperation* myOp = createDataOperation();
       printf("\nEnter a line:\n ");
       if (fgets(line, sizeof(line), stdin) != NULL) {
           m=checkForOpration(line,myOp);
        } else {
           printf("Error reading input.\n");
        }

        if(m !=-1){
        printf("Opcode: %d\n", myOp->opcode);
        printf("Type Source Operand: %d\n", myOp->typeSourceOperand);
        printf("Type Destination Operand: %d\n", myOp->typeDestinationOperand);
        printf("Source Operand: %s\n", myOp->sourceOperand);
        printf("Destination Operand: %s\n", myOp->destinationOperand);
       }
       
         freeDataOperation(myOp);
    }
    /*
    if(continueLine==NULL){
      errorMessagesInLine(lineNmber,'r',0);
      return -1;
    }*/
    

printf("\n m=%d ",m);
    /* code */
    return 0;
    
}