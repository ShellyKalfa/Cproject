#include "firstPassHeader.h"

#define START_L 100
#define MAX_LENGTH_LINE 4095
/*secondPass run the second Pass check if symbol in place that everthing works 
and also write them to files
*/
int secondPass(char *fileNameToWrite){
    int sucssesEntryInSymbol=0, allSymbolIn=0,fileOBscces=0;
     /*error messages */
    char EsymbolNotDefined[] ="Failed your put in entry symbol that you didnt defined";
    char EsymbolNot[] ="Failed  symbol that you didnt defined it so we cant start";
    char EsomthingWRONG[] ="Failed  saveing didnt work try again";

    sucssesEntryInSymbol=checkEntryInSymbol(listOfEntry,mySymbolTabel);
    if(sucssesEntryInSymbol==-1){
      errorMessagesWithText(EsymbolNotDefined,strlen(EsymbolNotDefined),'r');
      return -1; 
    }
    allSymbolIn=checkSymbolLineInICInSymbolTabelOrExtern(myIClist,mySymbolTabel,listOfExtern);
    if(allSymbolIn==-1){
      errorMessagesWithText(EsymbolNot,strlen(EsymbolNot),'r');
      return -1; 
    }
    if(sucssesEntryInSymbol==1&&(allSymbolIn==1||allSymbolIn==0)){

     if(listOfEntry->headEntry  != NULL){
       printEntryToFile(listOfEntry,fileNameToWrite);}
       if(listOfExtern->head != NULL){
       printExternToFile(listOfExtern,myIClist,fileNameToWrite);}
      fileOBscces= printICAndDCToFile(myIClist,myDClist,fileNameToWrite);
      if(fileOBscces==-1){
         errorMessagesWithText(EsomthingWRONG,strlen(EsomthingWRONG),'r');
         return -1; 
      }
      return 1;
    }
    return -1; 
}
/*check Entry In Symbol
return 1 if all go else -1
*/
int checkEntryInSymbol(EntryList *list,SymbolTabel *table){
    Entry *current=NULL;
    SymbolName *SymbolNameForPlace=NULL;
    int lookUpInSymboll=0,place=0;

    if (list == NULL ||table==NULL) {
        return -1; 
    }

    current = list->headEntry;
    while (current != NULL) {
        lookUpInSymboll=ISsearchSymbol(table, current->name);
        if (!lookUpInSymboll) {
            return -1;
        }
        SymbolNameForPlace=searchSymbol(table, current->name);
        place=SymbolNameForPlace->placeInCode;
        current->lineIcCurrent=place;
        current = (current->next);
    }
  return 1;
}
/*
check SymbolLineInIC In SymbolTabel Or Extern
return 1 if found else -1 
*/
int checkSymbolLineInICInSymbolTabelOrExtern(IClist *icList,SymbolTabel *table,ExternList *externList){
    SymbolLineInIC *current;
    SymbolName* symbolNameCurrent=NULL;
    int inSYmbol=0,inExtern=0,putICSymbol=0;
      /*error messages */
    char ENoSymbols[] ="No symbols to check.";
    char ESymbolsNotFound[] ="the symbol you put in is not found ";
     char ESomthingWrong[] ="SOMTHING GO WRONG ";

    if (!icList || !icList->HeadSymbolLinesToFill) {
        errorMessagesWithText(ENoSymbols,strlen(ENoSymbols),'y');
        return 0;
    }

    current = icList->HeadSymbolLinesToFill;
    while (current != NULL) {
               inExtern= ISsearchExtern(externList, current->nameSymbol);
               if(inExtern==1){ 
                   addLineIcToExtern(externList, current->nameSymbol, current->placeInIc);
                   putICSymbol=putInPlaceSymbolLineInIC(icList,current->placeInIc,0,'e');
               }
               if(!inExtern){
                 inSYmbol=ISsearchSymbol(table,current->nameSymbol);
                 symbolNameCurrent =searchSymbol(table,current->nameSymbol);
                 if(inSYmbol==1){
                   putICSymbol=putInPlaceSymbolLineInIC(icList,current->placeInIc,symbolNameCurrent->placeInCode,'r');
                 }
               }
               if(!inExtern&&!inSYmbol){
                   errorMessagesWithTextIN(ESymbolsNotFound,strlen(ESymbolsNotFound),current->nameSymbol,strlen(current->nameSymbol),22,'r');
                     return -1;
               }
               if(inExtern==-1||inSYmbol==-1){
                    errorMessagesWithText(ESomthingWrong,strlen(ESomthingWrong),'r');
                    return -1;
               }
               if(!putICSymbol){
                    errorMessagesWithText(ESomthingWrong,strlen(ESomthingWrong),'r');
                    return -1;
               }
        current = current->next;
    }
    return 1;
}/*
after checking that everthing good puting In Place -SymbolLineInIC
return 1 if all good else -1 
*/
int putInPlaceSymbolLineInIC(IClist *icList,int placeInIC,int PlaceNumber,char E_or_R){
    unsigned short currentSymbolBit=0;
    ICline *currentIC = icList->head;
    int linePlace=0;
    currentSymbolBit=BitsSymbolLineInIC(PlaceNumber, E_or_R);
    while (currentIC != NULL) {

        if(linePlace==placeInIC){
          currentIC->LinesInIC=currentSymbolBit;
          /*sucsses*/
          return 1;
         }
        currentIC = currentIC->next;
        linePlace++;
    }
    return 0;
}
/*print to file Entry */
void printEntryToFile(EntryList *entryList,char* namefile){
     Entry *current = entryList->headEntry;
     FILE *fileWrite;
     int length=0,newLength=0;
     char *dot,*fileName=NULL;
     /**/
     char EfileNoExtensiont[]="No file extension found";
     char EFailedAllocate[] ="Failed to allocate memory";

    dot = strrchr(namefile, '.');
    if (dot == NULL) {
        errorMessagesWithText(EfileNoExtensiont,strlen(EfileNoExtensiont),'r');
        return ;
    }

    length = dot - namefile;
    newLength = length + 4;
    fileName = (char *)malloc((newLength + 1) * sizeof(char));

    if (fileName == NULL) {
        errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'y');
        return ;
    }
    strncpy(fileName, namefile, length);
    fileName[length] = '\0';
    strcat(fileName, ".ent");
     fileWrite = fopen(fileName, "w");
     if (fileWrite == NULL ) {
       if (fileWrite) fclose(fileWrite);
       }
    
    while (current != NULL) {
        fprintf(fileWrite," %d, %s\n",
               current->lineIcCurrent,
               current->name);
        current = current->next;
    }
    fclose(fileWrite);

}
/*print to file Extern */
void printExternToFile(ExternList *externList,IClist *icList,char* namefile){
     SymbolLineInIC *current;
     FILE *fileWrite;
     int length=0,newLength=0,inExtern;
     char *dot,*fileName=NULL;
     /**/
     char EfileNoExtensiont[]="No file extension found";
     char EFailedAllocate[] ="Failed to allocate memory";

    dot = strrchr(namefile, '.');
    if (dot == NULL) {
        errorMessagesWithText(EfileNoExtensiont,strlen(EfileNoExtensiont),'r');
        return ;
    }

    length = dot - namefile;
    newLength = length + 4;
    fileName = (char *)malloc((newLength + 1) * sizeof(char));

    if (fileName == NULL) {
        errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'y');
        return ;
    }
    strncpy(fileName, namefile, length);
    fileName[length] = '\0';
    strcat(fileName, ".ext");
     fileWrite = fopen(fileName, "w");
     if (fileWrite == NULL ) {
       if (fileWrite) fclose(fileWrite);
       }
   
    if (!externList) {
        printf("The list is empty or not initialized.\n");
        return;
    }

    if (!icList || !icList->HeadSymbolLinesToFill) {
        printf("No symbols to traverse.\n");
        return;
    }

    current = icList->HeadSymbolLinesToFill;
    while (current != NULL) {
               inExtern= ISsearchExtern(externList, current->nameSymbol);
               if(inExtern==1){ 
                fprintf(fileWrite," %s,  %d\n",
               current->nameSymbol, (current->placeInIc+START_L));
               }
        current = current->next;
    }
        
        fclose(fileWrite);
}
/*print to file IC And DC To File */
int printICAndDCToFile(IClist *icList, DClist *dclist, char* namefile) {
    ICline *currentICLine;
    DCline *currentDCLine;
    int CurrentLine;
     FILE *fileWrite;
    char EyouPassTHElimtLINE[] = "Failed you PASS THE LIMIT Addresses ";

    /* Initialize variables */
    currentICLine = icList->head;
    currentDCLine = dclist->head;
    CurrentLine = START_L;
      fileWrite = fopen(namefile, "w");
     if (fileWrite == NULL ) {
       if (fileWrite) fclose(fileWrite);
       }
    
    fprintf(fileWrite,"%d ,%d \n",icList->numbersOfLineInIC,dclist->numbersOfLineInDC);

    /* Process IC lines */
    while (currentICLine != NULL) {
        fprintf(fileWrite,"%d  %-11o \n", CurrentLine, currentICLine->LinesInIC);
        currentICLine = currentICLine->next;
        CurrentLine++; 

        if (CurrentLine >= MAX_LENGTH_LINE) {
            errorMessagesWithText(EyouPassTHElimtLINE, strlen(EyouPassTHElimtLINE), 'r');
            fclose(fileWrite);
            return -1;
        }
    }

    /* Process DC lines */
    while (currentDCLine != NULL) {
        fprintf(fileWrite,"%d  %-11o \n", CurrentLine, currentDCLine->LinesInDC);
        currentDCLine = currentDCLine->next;
        CurrentLine++; 

        if (CurrentLine >= MAX_LENGTH_LINE) {
            errorMessagesWithText(EyouPassTHElimtLINE, strlen(EyouPassTHElimtLINE), 'r');
            fclose(fileWrite);
            return -1;
        }
    }
    fclose(fileWrite);
    return 1;
}
