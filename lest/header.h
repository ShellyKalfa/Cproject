#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>

/*global varibles*/


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

#endif 
