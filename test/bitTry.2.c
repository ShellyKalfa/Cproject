#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>

typedef struct ICline {
  unsigned  short LinesInIC;
  struct ICline  * next;
} ICline;

typedef struct SymbolLineInIC{
  char  *nameSymbol;
  int lengthName;
  int placeInIc;
  struct SymbolLineInIC *next;
} SymbolLineInIC;

typedef struct {
  ICline *head;
  ICline *tail;
  int numbersOfLineInIC;
  SymbolLineInIC *HeadSymbolLinesToFill;
  SymbolLineInIC *TailSymbolLinesToFill;
} IClist;

SymbolLineInIC* createSymbolLineInIC(const char *name, int placeInIc) {
    SymbolLineInIC *node = (SymbolLineInIC *)malloc(sizeof(SymbolLineInIC));
    if (node == NULL) return NULL;

    node->nameSymbol = (char *)malloc(sizeof(char)*(strlen(name)+1));
    if (node->nameSymbol == NULL) {
        free(node);
        return NULL;
    }
    strcpy(node->nameSymbol, name);

    node->lengthName = strlen(name);
    node->placeInIc = placeInIc;
    node->next = NULL;

    return node;
}

int addSymbolToHeadSymbolLinesToFill(IClist *list, const char *name) {
    SymbolLineInIC *newSymbol;
    int placeInIc;
    if (list == NULL) return -1;
    placeInIc=list->numbersOfLineInIC;
    newSymbol = createSymbolLineInIC(name, placeInIc);
    if (newSymbol == NULL) return -1;

    if (list->HeadSymbolLinesToFill == NULL) {
        list->HeadSymbolLinesToFill = newSymbol;
        list->TailSymbolLinesToFill = newSymbol;
    } else {
        list->TailSymbolLinesToFill->next = newSymbol;
        list->TailSymbolLinesToFill = newSymbol;
    }

    return 0;
}

SymbolLineInIC *BitsSymbolInIC(char * symbolName,int whichOprtion){
    SymbolLineInIC *newSymbol;
    /*if (list == NULL) return -1;*/

    newSymbol = createSymbolLineInIC(symbolName, whichOprtion);
    if (newSymbol == NULL) return -1;

     return newSymbol;

}
void printSymbol(SymbolLineInIC *BitsSymbolInIC){
    /*char  *nameSymbol;
  int lengthName;
  int placeInIc;*/

    printf("nameSymbol= %c",*(BitsSymbolInIC->nameSymbol));
    printf("nameSymbol= %d",BitsSymbolInIC->lengthName);
    printf("nameSymbol= %d",BitsSymbolInIC->placeInIc);


}



int main() {
   /* int SourceR=0,DestinationR=0;*/
    int Ic=100;       
     
    char CSourceR[]="bla";
   /* int Destination = 3; 
    char CDestinationR[]="lala";*/
    SymbolLineInIC *tempSymbol;
     /**/
    tempSymbol=createSymbolLineInIC(CSourceR,1+Ic);
    printSymbol(tempSymbol);
   

  

    return 0;
}
