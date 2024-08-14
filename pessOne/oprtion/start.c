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