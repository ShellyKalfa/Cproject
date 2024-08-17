#include "symbol.h"

#define MAX_SIZE_DATA 37
#define MAX_SIZE_STRING 70
#define MAX_LINE_LENGTH 80

int data[MAX_SIZE_DATA];
char string[MAX_SIZE_STRING];
Entry * listOfEntry=NULL;
int entryCount = 0;
Extern *listOfExtern;
int externCount = 0;


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


/* Entry */
Entry *searchEntry(const char *name) {
    int i;
    for ( i = 0; i < entryCount; i++) {
        if (strcmp(listOfEntry[i].name, name) == 0) {
            return &listOfEntry[i];
        }
    }
    return NULL; 
}
int addEntry(const char *name, int lineIcCurrent) {
    Entry *entry = searchEntry(name); 
    if(entry!=NULL){
       perror("Failed you are already have this entry");
       return -1;
    }
    listOfEntry = realloc(listOfEntry, (entryCount + 1) * sizeof(Entry));
    if (listOfEntry == NULL) {
        perror("Failed to allocate memory");
        return -1;
    }
    
    listOfEntry[entryCount].nameLangth = strlen(name);
    listOfEntry[entryCount].lineIcCurrent = lineIcCurrent;
    listOfEntry[entryCount].name = malloc((strlen(name) + 1) * sizeof(char));
    
    if (listOfEntry[entryCount].name == NULL) {
        perror("Failed to allocate memory");
        return -1;
    }
    
    strcpy(listOfEntry[entryCount].name, name);
    entryCount++;
    return 1;
}
void cleanEntries() {
    int i;
    for (i = 0; i < entryCount; i++) {
        free(listOfEntry[i].name);
    }
    free(listOfEntry);
    listOfEntry = NULL;
    entryCount = 0;
}

void printEntries() {
    int i;
    for ( i= 0; i < entryCount; i++) {
        printf("Name: %s, Length: %d, Line: %d\n", 
               listOfEntry[i].name, 
               listOfEntry[i].nameLangth, 
               listOfEntry[i].lineIcCurrent);
    }
}
int printEntriesToFile(FILE *file) {
    int i ;
    if (file == NULL) {
        perror("File error");
        return -1;
    }

    for ( i = 0; i < entryCount; i++) {
        fprintf(file, "%s %d\n", 
                listOfEntry[i].name, 
                listOfEntry[i].lineIcCurrent);
    }
    return 1;
}
/*
int addExternEntry(const char *name, int lineIcValue) {
    
    Extern externTemp = searchExtern(name);

    if (externTemp != NULL) {
            perror("Failed to allocate memory");
            return -1;
    } else {
        listOfExtern = realloc(listOfExtern, (externCount + 1) * sizeof(Extern));
        if (listOfExtern == NULL) {
            perror("Failed to allocate memory");
            return -1;
        }
        
        listOfExtern[externCount].nameLangth = strlen(name);
        listOfExtern[externCount].name = malloc((strlen(name) + 1) * sizeof(char));
        if (listOfExtern[externCount].name == NULL) {
            perror("Failed to allocate memory");
            return -1;
        }
        strcpy(listOfExtern[externCount].name, name);

        listOfExtern[externCount].lineIcCount = 1;
        listOfExtern[externCount].lineIc = malloc(sizeof(int));
        if (listOfExtern[externCount].lineIc == NULL) {
            perror("Failed to allocate memory");
            return -1;
        }
        listOfExtern[externCount].lineIc[0] = lineIcValue;

        externCount++;
    }

    return 1;
}
int cleanExternEntries() {
    int i;
    for (i = 0; i < externCount; i++) {
        free(listOfExtern[i].name);
        free(listOfExtern[i].lineIc);
    }
    free(listOfExtern);
    listOfExtern = NULL;
    externCount = 0;

    return 0;
}
Extern *searchExtern(const char *name) {
    int i;
    for (i = 0; i < externCount; i++) {
        if (strcmp(listOfExtern[i].name, name) == 0) {
            return &listOfExtern[i];
        }
    }
    return NULL; 
}
int addLineIcToExtern(Extern *entry, int lineIcValue) {
    if (entry == NULL) {
        return -1;
    }

    entry->lineIc = realloc(entry->lineIc, (entry->lineIcCount + 1) * sizeof(int));
    if (entry->lineIc == NULL) {
        perror("Failed to allocate memory");
        return -1;
    }

    entry->lineIc[entry->lineIcCount] = lineIcValue;
    entry->lineIcCount++;

    return 1;
}
void printExternEntriesToFile(FILE *file) {
    int i,j;
    if (file == NULL) {
        perror("File error");
        return -1;
    }

    for (  i= 0; i < externCount; i++) {
        for ( j = 0; j < listOfExtern[i].lineIcCount; j++) {
            fprintf(file, "%s %d\n", 
                    listOfExtern[i].name, 
                    listOfExtern[i].lineIc[j]);
        }
    }
    return 1;
}*/
