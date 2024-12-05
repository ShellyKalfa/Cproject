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
/*Define the data Operation*/
typedef struct {
    int opcode;
    int typeSourceOperand;
    int typeDestinationOperand;
    char *sourceOperand;
    char *destinationOperand;
} dataOperation;

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
/*error*/
void errorMessages(enum colorMessages message);
void errorMessagesWithText(char * message,int lenght,char color);
void errorMessagesWithTextExstra(char * message,int length,char * messageExstra,int lengthExstra,char color);
void errorMessagesWithTextIN(char * message,int length,char * messageIn,int lengthIn,int whereIn,char color);
void errorMessagesInLine(int numberOfLine,char color,int problem);
/*check Opration*/
int lookForOpcode(char *input);
int checkDataOperation(dataOperation * myOp);
/*symbol*/
int checkSymbol(char *nameSymbol,int saveSymbol);


#endif 