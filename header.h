#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>

/*enum functions {mov,cmp,add,sub,lea,clr,not,inc,dec,jmp,bne,red,prn,jsr,rts,stop};*/


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

#endif 
