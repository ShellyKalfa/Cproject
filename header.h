#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>


/*enum functions {mov,cmp,add,sub,lea,clr,not,inc,dec,jmp,bne,red,prn,jsr,rts,stop};*/

int preAssembler(char *textFile);
int isFileExists(char *path);
int writeLinesToFile( char *assemblerName,char *textName);