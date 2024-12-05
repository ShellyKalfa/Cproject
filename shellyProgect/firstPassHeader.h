#ifndef COUNTER_H
#define COUNTER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>

/*structures*/

typedef struct SymbolName{
    char * nameSymbol;
    int lengthName;
    char DCorIC;
    int placeInCode;
    struct SymbolName *next;
}SymbolName;

typedef struct{
        SymbolName *HeadSymbols;
        SymbolName *TailSymbols;
        int size;
}SymbolTabel;

typedef struct Entry {
    int lineIcCurrent;
    int nameLangth;
    char *name;
    struct Entry *next;
} Entry;

typedef struct {
   Entry * headEntry;
   Entry * tailEntry;
} EntryList;

typedef struct Extern {
    int nameLangth;
    char *name;
    int lineIcCount;
    int * lineIc;
    struct Extern *next;
} Extern;

typedef struct {
    Extern * head;
    Extern * tail;
} ExternList;

typedef struct DCline {
    unsigned short LinesInDC;
    struct DCline * next; 
} DCline;

typedef struct {
  DCline * head;
  DCline * tail;
  int numbersOfLineInDC;
} DClist;

typedef struct ICline{
  unsigned short LinesInIC;
   struct ICline *next; 
} ICline;

typedef struct SymbolLineInIC{
  char * nameSymbol;
  int lengthName;
  int placeInIc;
  struct SymbolLineInIC *next;
} SymbolLineInIC;

typedef struct {
  ICline * head;
  ICline * tail;
  int numbersOfLineInIC;
  SymbolLineInIC *HeadSymbolLinesToFill;
  SymbolLineInIC *TailSymbolLinesToFill;
} IClist;

/*Define the data Operation*/
typedef struct {
    int opcode;
    int typeSourceOperand;
    int typeDestinationOperand;
    char *sourceOperand;
    char *destinationOperand;
} dataOperation;

/*global*/
extern int data[37];
extern char string[70];
extern EntryList * listOfEntry;
extern ExternList *listOfExtern;
/*symbol global*/
extern char * CurrentLabel;
extern SymbolTabel * mySymbolTabel;
/*IC DC global*/
extern DClist * myDClist;
extern IClist * myIClist;
/*functions*/

/*error*/
void errorMessagesWithText(char * message,int lenght,char color);
void errorMessagesWithTextExstra(char * message,int length,char * messageExstra,int lengthExstra,char color);
void errorMessagesWithTextIN(char * message,int length,char * messageIn,int lengthIn,int whereIn,char color);
void errorMessagesInLine(int numberOfLine,char color,int problem);

/* dataSymbol */
SymbolTabel* createSymbolTabel();
SymbolName* searchSymbolTabel(SymbolTabel *table, const char *name);
SymbolName* searchSymbol(SymbolTabel *table, const char *nameSymbol);
int ISsearchSymbol(SymbolTabel *table, const char *nameSymbol);
int addSymbol(SymbolTabel *table, const char *nameSymbol, int lengthName, char DCorIC, int placeInCode);
void cleanSymbolTabel(SymbolTabel *table);
void printSymbolTabel(SymbolTabel *table) ;

/* dataDCorIC */
/*dc*/
DClist* createDClist() ;
DCline* createDCline(unsigned short line); 
int addLineToDClist(DClist *list, unsigned short line) ;
void cleanDClist(DClist *list);
void printDClist(DClist *list);
/*ic*/
ICline* createICline(unsigned short line);
IClist* createIClist();
SymbolLineInIC* createSymbolLineInIC(const char *name, int placeInIc);
int addLineToIClist(IClist *list, unsigned short line);
int addSymbolToHeadSymbolLinesToFill(IClist *list, const char *name);
void cleanIClist(IClist *list);
void cleanSymbolLineInICList(SymbolLineInIC *head);
void cleanIClist(IClist *list);
void printIClist(IClist *list);
/*firstPass*/
int handelLine(char * line);
/**/
/*Symbol*/
char *thereIsSymbol(char *line);
int checkSymbol(char *nameSymbol,int saveSymbol);
int saveSymbolCurrentLabel(char *nameSymbol);
/*Opcode*/
int lookForOpcode(char *input);
int checkDataOperation(dataOperation * myOp);
/*Opcode*/
int lookForOpcode(char *input);
int checkDataOperation(dataOperation * myOp);
/*Directive*/
int checkDirective(char *line);
int whichDirective(int functionNumber,char * line);
int dataHasFound(char * input);
int getInteger(char *input ,int lengthInput);
int stringHasFound(char * input);
int addToListEntryOrExtern( char * nameEntry,int EntryOrExtern );
 int saveEntryOrExtern(char *nameSymbol,int EntryOrExtern );
/*dataDirectives*/
void initializeArrayData();
void fillArrayData(int * newdata,int length);

void initializeArrayString();
void fillArrayString(char * newString,int length);
int printArrayStringToFile(char * fileName,int length ) ;
void print15BitBinary(int asciiCode);

EntryList * createEntryList();
int addEntry(EntryList *list, const char *name) ;
Entry* searchEntry(EntryList *list, const char *name);
int ISsearchEntry(EntryList *list, const char *name);
void cleanEntryList(EntryList *list);
void printEntryList(const EntryList *entryList);

ExternList* createExternList();
Extern* createExtern(const char *name, int nameLength, int *lineIc, int lineIcCount);
Extern* searchExtern(ExternList *list, const char *name);
int ISsearchExtern(ExternList *list, const char *name);
int createAndAddExtern(ExternList *list, const char *name, int nameLength);
int addLineIcToExtern(ExternList *list, const char *name, int lineIcValue);
void cleanExternList(ExternList *list);
void printExternList(const ExternList *list) ;
/*Opration*/
int checkForOpration(char * line, dataOperation * newOpcode );
int checkEmptyLine(char * copyLine);
int getOpration(char * copyLine,dataOperation * newOpcode,char whichOpration);
int checkOpration(char * token );
int getInteger(char *input ,int lengthInput);
int splitOprations(char * copyLine,dataOperation * newOpcode );
/*data Opcode*/
dataOperation* createDataOperation();
void setOpcode(dataOperation* op, int opcode);
void setTypeSourceOperand(dataOperation* op, int typeSource);
void setTypeDestinationOperand(dataOperation* op, int typeDest);
void setSourceOperand(dataOperation* op, const char* srcOperand);
void setDestinationOperand(dataOperation* op, const char* destOperand);
void freeDataOperation(dataOperation* op);
/*dataTObinary*/
int getOprtion(dataOperation * myOp);
int getOprtionNumber(int type ,char *numberOp);
unsigned short BitsfirstLine(int opcode, int Source, int Destination);
unsigned short BitsRegister( int SourceR, int DestinationR);
unsigned short BitsgetNumber(int num);
unsigned short BitsNumberSymbol(int num,char E_or_R);
unsigned short BitsSymbolLineInIC(int place,char E_or_R);

int saveSymbolForSymbolLines(IClist *list,char *nameSymbol);
int putLineInDC(DClist * listDC,int directiveNumber,int length);
int printString(DClist * listDC,int length);
int printData(DClist * listDC,int length);
/*filefirstPass*/
int firstPass(char *textFile);
int isFileExistsOB(char *path) ;
int writeLinesToFileOB(char *assemblerName, char *textName);
/*secondPass*/
int secondPass(char *fileNameToWrite);
int checkEntryInSymbol(EntryList *list,SymbolTabel *table);
int checkSymbolLineInICInSymbolTabelOrExtern(IClist *icList,SymbolTabel *table,ExternList *externList);
int putInPlaceSymbolLineInIC(IClist *icList,int placeInIC,int PlaceNumber,char E_or_R);
void printEntryToFile(EntryList *list,char* namefile);
void printExternToFile(ExternList *externList,IClist *icList,char* namefile);
int printICAndDCToFile(IClist *icList, DClist *dclist, char* namefile);

#endif 
