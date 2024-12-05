#include "header.h"

int lookForOpcode(char *input)
{
    int returnOperation = -1;
    int flag = 0;
   
    if (strstr(input, "mov") != NULL&&(strlen(input)==strlen("mov")))
    {
        flag += 1;
        returnOperation= 0;
    }
    if (strstr(input, "cmp") != NULL&&(strlen(input)==strlen("cmp")))
    {
        flag += 1;
        returnOperation= 1;
    }
    if (strstr(input, "add") != NULL&&(strlen(input)==strlen("add")))
    {
        flag += 1;
        returnOperation= 2;
    }
    if (strstr(input, "sub") != NULL&&(strlen(input)==strlen("sub")))
    {
        flag += 1;
        returnOperation= 3;
    }
    if (strstr(input, "lea") != NULL&&(strlen(input)==strlen("lea")))
    {
        flag += 1;
        returnOperation= 4;
    }
    if (strstr(input, "clr") != NULL&&(strlen(input)==strlen("clr")))
    {
        flag += 1;
        returnOperation= 5;
    }
    if (strstr(input, "not") != NULL&&(strlen(input)==strlen("not")))
    {
        flag += 1;
        returnOperation= 6;
    }
    if (strstr(input, "inc") != NULL&&(strlen(input)==strlen("inc")))
    {
        flag += 1;
        returnOperation= 7;
    }
    if (strstr(input, "dec") != NULL&&(strlen(input)==strlen("dec")))
    {
        flag += 1;
        returnOperation= 8;
    }
    if (strstr(input, "jmp") != NULL&&(strlen(input)==strlen("jmp")))
    {
        flag += 1;
        returnOperation= 9;
    }
    if (strstr(input, "bne") != NULL&&(strlen(input)==strlen("bne")))
    {
        flag += 1;
        returnOperation= 10;
    }
    if (strstr(input, "red") != NULL&&(strlen(input)==strlen("red")))
    {
        flag += 1;
        returnOperation= 11;
    }if (strstr(input, "prn") != NULL&&(strlen(input)==strlen("prn")))
    {
        flag += 1;
        returnOperation= 12;
    }
    if (strstr(input, "jsr") != NULL&&(strlen(input)==strlen("jsr")))
    {
        flag += 1;
        returnOperation= 13;
    }
     if (strstr(input, "rts") != NULL&&(strlen(input)==strlen("rts")))
    {
        flag += 1;
        returnOperation= 14;
    }
    if (strstr(input, "stop") != NULL&&(strlen(input)==strlen("stop")))
    {
        flag += 1;
        returnOperation= 15;
    }
    if (strstr(input, "data") != NULL&&(strlen(input)==strlen("data")))
    {
        flag += 1;
        returnOperation= 16;
    }
    if (strstr(input, "string") != NULL&&(strlen(input)==strlen("string")))
    {
        flag += 1;
        returnOperation= 17;
    }
     if (strstr(input, "extern") != NULL&&(strlen(input)==strlen("extern")))
    {
        flag += 1;
        returnOperation= 18;
    }
     if (strstr(input, "entry") != NULL&&(strlen(input)==strlen("entry")))
    {
        flag += 1;
        returnOperation= 19;
    }
    if (strstr(input, "macr") != NULL &&(strlen(input)==strlen("macr")))
    {
        flag += 1;
        returnOperation= 20;
    }
    if (strstr(input, "endmacr") != NULL&&(strlen(input)==strlen("endmacr")))
    {
        flag += 1;
        returnOperation= 21;
    }

    if ( flag > 1)
    {
        returnOperation= -1;
    }
    
    return returnOperation;
}