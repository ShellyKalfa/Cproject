#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>

/*enum color Messages */
enum colorMessages {
    GREEN,
    RED,    
    YELLOW,
    WHITE
}; 
typedef struct {
    int lineIcCurrent;
    int nameLangth;
    char *name;
} Entry;
typedef struct {
    int nameLangth;
    char *name;
    int lineIcCount;
    int * lineIc;
} Extern;

/*global*/
extern int data[37];
extern char string[70];
extern Entry * listOfEntry;
extern int entryCount;
/*symbol*/
extern char *CurrentLabel;

/*Symbol*/
char *thereIsSymbol(char *line,int IC);
int checkSymbol(char *nameSymbol,int saveSymbol);
/*error*/
void errorMessages(enum colorMessages message);
void errorMessagesWithText(char * message,int lenght,char color);
void errorMessagesWithTextExstra(char * message,int length,char * messageExstra,int lengthExstra,char color);
void errorMessagesWithTextIN(char * message,int length,char * messageIn,int lengthIn,int whereIn,char color);
void errorMessagesInLine(int numberOfLine,char color,int problem);
/*Opcode*/
int lookForOpcode(char *input);
/*Directive*/
int checkDirective(char *line);
int whichDirective(int functionNumber,char * line);
int dataHasFound(char * input);
int getInteger(char *input ,int lengthInput);
int  stringHasFound(char * input);
int addToListEntry( char * nameEntry);
/*store data and string */
void initializeArrayData();
void fillArrayData(int * newdata,int length);

void initializeArrayString();
void fillArrayString(char * newString,int length);
int printArrayStringToFile(char * fileName,int length ) ;
void print15BitBinary(int asciiCode);

Entry *searchEntry(const char *name);
int addEntry(const char *name, int lineIcCurrent);
void cleanEntries();
void printEntries();
int printEntriesToFile(FILE *file);

#endif 