#ifndef COUNTER_H
#define COUNTER_H

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

int searchNameOfMacr(HashTable *table, char *nameMacr);
void addNameOfMacr(HashTable *table, char *nameMacr, char *linesInMacro);
void deleteNameOfMacr(HashTable *table, char *nameMacr);
void freeHashTable(HashTable *table);
char* searchNameOfMacrReturnLine(HashTable *table, char *nameMacr) ;
HashTable* createHashTable(void);





#endif 
