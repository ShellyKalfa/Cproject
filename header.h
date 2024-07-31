#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>

#define TABLE_SIZE 2048  

typedef struct macroName {
    char *name;
    char *linesInMacro;
    struct macroName *next;
} macroName;

typedef struct {
    macroName *head;
    macroName *tail;
} listMacro;

typedef struct {
    macroName **table;
} HashTable;

extern listMacro currentList;


/*global varibles*/
/*macro*/
extern int foundMacro;
extern int thereAreMacros;
extern char* storeLine;
extern char* currentMacrName;
extern int problems;

/*enum color Messages */
enum colorMessages {
    RED,    
    YELLOW,
    WHITE
};


int preAssembler(char *textFile);
int isFileExists(char *path);
int writeLinesToFile(char *assemblerName, char *textName);
void errorMessages(enum colorMessages message);
/*macros*/
void reboot();
char * showLinesMacro(char *line);
void clearGlobals();
int cleanBlankAndNoteLine(char *line);
int findMacrByName(char *nameMacr);
int checkNameOfMcro(char *nameMacr);
int findDefinitionMacro(char *line );
int findEndMacro(char *line );
int lookSaveWords(char *input);
int checkLineForMacr(char *line);
void tableFree();
/*storage*/
int searchNameOfMacr(HashTable *table, char *nameMacr);
void addNameOfMacr(HashTable *table, char *nameMacr, char *linesInMacro);
void deleteNameOfMacr(HashTable *table, char *nameMacr);
void freeHashTable(HashTable *table);
char* searchNameOfMacrReturnLine(HashTable *table, char *nameMacr) ;
HashTable* createHashTable(void);

#endif 
