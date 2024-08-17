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

typedef struct{
    char * nameSymbol;
    int lengthName;
    char DCorIC;
    int placeInCode;
    SymbolName *next
}SymbolName;

typedef struct{
        SymbolName *HeadSymbols;
        SymbolName *TailSymbols;
        int size;
}SymbolTabel;

typedef struct {
    int lineIcCurrent;
    int nameLangth;
    char *name;
    Entry *next;
} Entry;

typedef struct {
   Entry *headEntry;
   Entry *tailEntry;
} EntryList;

typedef struct {
    int nameLangth;
    char *name;
    int lineIcCount;
    int * lineIc;
    Extern *next;
} Extern;

typedef struct {
    Extern * head;
    Extern * tail;
} ExternList;

typedef struct {
  short LinesInDC;
  DCline  * next;
} DCline;

typedef struct {
  DCline *head;
  DCline *tail;
  int numbersOfLineInDC;
} DClist;

typedef struct {
  short LinesInIC;
  ICline  * next;
} ICline;

typedef struct {
  char  *nameSymbol;
  int lengthName;
  int placeInIc;
  SymbolLineInIC *next;
} SymbolLineInIC;

typedef struct {
  ICline *head;
  ICline *tail;
  int numbersOfLineInIC;
  SymbolLineInIC *HeadSymbolLinesToFill;
  SymbolLineInIC *TailSymbolLinesToFill;
} IClist;

/*functions*/
/* dataSymbol */
SymbolTabel* createSymbolTabel();
void cleanSymbolTabel(SymbolTabel *table);
int searchSymbolTabel(SymbolTabel *table, const char *name);
SymbolName* searchSymbolTabel(SymbolTabel *table, const char *name);
int addSymbol(SymbolTabel *table, const char *name, char DCorIC, int placeInCode);
/* dataDCorIC */
/*dc*/
DClist* createDClist() ;
DCline* createDCline(short line);
int addLineToDClist(DClist *list, short line);
void cleanDClist(DClist *list);
/*ic*/
ICline* createICline(short line);
IClist* createIClist();
SymbolLineInIC* createSymbolLineInIC(const char *name, int placeInIc);
int addLineToIClist(IClist *list, short line);
int addSymbolToHeadSymbolLinesToFill(IClist *list, const char *name, int placeInIc);
void cleanIClineList(ICline *head);
void cleanSymbolLineInICList(SymbolLineInIC *head);
void cleanIClist(IClist *list);
/**/
#endif 
