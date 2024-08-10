#include "symbol.h"

#define MAX_LINE_LENGTH 80



int main(int argc, char const *argv[])
{
    char line[MAX_LINE_LENGTH+1];
    char *continueLine=NULL;
    int m=-1,i;  
    int IC=100;
    int lineNmber=5;
    int isCheckDirective=0;
    
    /*error messages*/


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
          m=whichDirective(isCheckDirective,continueLine);
      }
   

printf("\n m=%d ",m);
    /* code */
    return 0;
    
}