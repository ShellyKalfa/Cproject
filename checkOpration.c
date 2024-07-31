#include "header.h"
int lookForOpcode(char *input)
{
    int returnOperation = -1;
    int flag = 0;
   
    if (strstr(input, "mov") != NULL)
    {
        flag += 1;
        returnOperation= 0;
    }
    if (strstr(input, "cmp") != NULL)
    {
        flag += 1;
        returnOperation= 1;
    }
    if (strstr(input, "add") != NULL)
    {
        flag += 1;
        returnOperation= 2;
    }
    if (strstr(input, "sub") != NULL)
    {
        flag += 1;
        returnOperation= 3;
    }
    if (strstr(input, "lea") != NULL)
    {
        flag += 1;
        returnOperation= 4;
    }
    if (strstr(input, "clr") != NULL)
    {
        flag += 1;
        returnOperation= 5;
    }
    if (strstr(input, "not") != NULL)
    {
        flag += 1;
        returnOperation= 6;
    }
    if (strstr(input, "inc") != NULL)
    {
        flag += 1;
        returnOperation= 7;
    }
    if (strstr(input, "dec") != NULL)
    {
        flag += 1;
        returnOperation= 8;
    }
    if (strstr(input, "jmp") != NULL)
    {
        flag += 1;
        returnOperation= 9;
    }
    if (strstr(input, "bne") != NULL)
    {
        flag += 1;
        returnOperation= 10;
    }
    if (strstr(input, "red") != NULL)
    {
        flag += 1;
        returnOperation= 11;
    }if (strstr(input, "prn") != NULL)
    {
        flag += 1;
        returnOperation= 12;
    }
    if (strstr(input, "jsr") != NULL)
    {
        flag += 1;
        returnOperation= 13;
    }
     if (strstr(input, "rts") != NULL)
    {
        flag += 1;
        returnOperation= 14;
    }
    if (strstr(input, "stop") != NULL)
    {
        flag += 1;
        returnOperation= 15;
    }
    if ( flag > 1)
    {
        printf(" ther are to many oprations");
        returnOperation= -1;
    }
    return returnOperation;
}