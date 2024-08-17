#include "opration.h"

#define MAX_LINE_LENGTH 80



int main(int argc, char const *argv[])
{
    char line[MAX_LINE_LENGTH+1];
    char *continueLine=NULL;
    int m=-1, mi=-1;
     int directive=-1;
    /*
    int IC=100;
    int lineNmber=5;
    */
    /*error messages*/


    /*symbol*/
    if(directive==-1){
       dataOperation* myOp = createDataOperation();
       memset(line, '\0', sizeof(MAX_LINE_LENGTH+1));
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
       }else
       {
         return -1;
       }
       
        mi= checkDataOperation(myOp);
        printf("mi =%d",mi);
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