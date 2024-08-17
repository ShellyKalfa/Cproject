#include "firstPassHeader.h"


int main(int argc, char const *argv[])
{
    char line[256];
    int m=0;  
    currentTable = createHashTable();
   while (m<2)
   {
    printf("\nEnter a line:\n ");
    if (fgets(line, sizeof(line), stdin) != NULL) {
      m=checkLineForMacr(line);
      /*m= findDefinitionMacro(line);*/
    } else {
        printf("Error reading input.\n");
    }
    printf("m= %d",m);
    /* code */
  }
  
    return 0;
    
}
