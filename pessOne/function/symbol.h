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
    RED,    
    YELLOW,
    WHITE
}; 

/*Symbol*/
char *thereIsSymbol(char *line,int IC);
int checkSymbol(char *nameSymbol);
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

#endif 