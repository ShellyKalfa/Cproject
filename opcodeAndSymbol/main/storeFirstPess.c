#include "symbol.h"

#define MAX_SIZE_DATA 37
#define MAX_SIZE_STRING 70

int data[MAX_SIZE_DATA];
char string[MAX_SIZE_STRING];


void initializeArrayData() {
    int i;
    for ( i= 0; i < MAX_SIZE_DATA; i++) {
        data[i] = 0;
    }
}
void fillArrayData(int * newdata,int length) {
    int i;
    for (i = 0; i < length; i++) {
        data[i] = newdata[i];  
    }
}
void initializeArrayString() {
    int i;
    for ( i= 0; i < MAX_SIZE_STRING; i++) {
        string[i] = '\0';
    }
}
void fillArrayString(char * newString,int length) {
    int i = 0;
    initializeArrayString();
    for (i = 0; i < length; i++) {
        string[i] = newString[i];  
    }
}
/*return the numbers of line it toke*/
int printArrayStringToFile(char * fileName,int length ) {
  int asciiCodeLetter=0;
  int i;
    /* FILE *fileWrite = fopen(fileName, "a+");*/
     printf("\n");
    for (i = 0; i <length ; i++) {
        asciiCodeLetter=(int) string[i];
        print15BitBinary(asciiCodeLetter);
       /* printf("%d",print15BitBinary(asciiCodeLetter) );
         printf("\n");*/
    }
    print15BitBinary(0);
      /*printf("%d",print15BitBinary(0) );
       printf("\n");*/
   return i;
}
void print15BitBinary(int asciiCode) {
    int i;
    for (i = 14; i >= 0; i--) {
        printf("%d", (asciiCode >> i) & 1);
    }
    printf("\n");
}


