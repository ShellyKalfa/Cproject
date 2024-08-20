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
typedef struct line {
    char *content;        
    struct line *next;     
} line;

typedef struct macroName {
    char *name;
    line *linesInMacro;   
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
extern line *linesInMacro;
extern line * readMe;


/*enum color Messages */
enum colorMessages {
    GREEN,
    RED,    
    YELLOW,
    WHITE
};


int preAssembler(char *textFile);
int isFileExists(char *path);
int writeLinesToFile(char *assemblerName, char *textName);
/*error*/
void errorMessages(enum colorMessages message);
void errorMessagesWithText(char * message,int lenght,char color);
void errorMessagesWithTextExstra(char * message,int length,char * messageExstra,int lengthExstra,char color);
void errorMessagesWithTextIN(char * message,int length,char * messageIn,int lengthIn,int whereIn,char color);
void errorMessagesInLine(int numberOfLine,char color,int problem);
/*macros*/
int checkLineForMacr(char *line);
int cleanBlankAndNoteLine(char *clearLine);
int findDefinitionMacro(char *line );
int checkNameOfMcro(char *nameMacr);
int findEndMacro(char *checkLine );
int findMacrByName(char *nameMacr);
line * showLinesMacro(char *line);
void initialize();
void tableFree();

/*storage*/
int searchNameOfMacr(HashTable *table, char *nameMacr);
void addNameOfMacr(HashTable *table, char *nameMacr, line *linesInMacro);
void deleteNameOfMacr(HashTable *table, char *nameMacr);
void freeHashTable(HashTable *table);
line* searchNameOfMacrReturnLine(HashTable *table, char *nameMacr);
HashTable* createHashTable(void);
/*linesInStorage*/
line* createLine(const char *content);
void appendLine(line **head, const char *content);
void freeLines(line *head);
void clearLinesInMacro(line **head);
/*Operation*/
int lookForOpcode(char *input);

#endif 
