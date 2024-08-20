#include "firstPassHeader.h"

#define MAX_SIZE_DATA 37
#define MAX_SIZE_STRING 70
#define MAX_LINE_LENGTH 80

int data[MAX_SIZE_DATA];
char string[MAX_SIZE_STRING];
EntryList * listOfEntry=NULL;
int entryCount = 0;
ExternList *listOfExtern;
int externCount = 0;

/*data*/
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
/*string*/
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
/* Entry */

EntryList * createEntryList() {
    EntryList *list;

    list = (EntryList *)malloc(sizeof(EntryList));
    if (list == NULL) {
        return NULL;
    }
    list->headEntry = NULL;
    list->tailEntry = NULL;
    return list;
}

int addEntry(EntryList *list, const char *name) {
    Entry *newEntry;

    if (list == NULL || name == NULL) {
        return -1;
    }

    newEntry = (Entry *)malloc(sizeof(Entry)*1);
    if (newEntry == NULL) {
        return -1; 
    }

    newEntry->lineIcCurrent = 0;
    newEntry->nameLangth = strlen(name);
    newEntry->name = (char *)malloc(sizeof(char) *(strlen(name) + 1));
    if (newEntry->name == NULL) {
        free(newEntry);
        return -1; 
    }
    strcpy(newEntry->name, name);
    newEntry->next = NULL;

    if (list->tailEntry == NULL) {
        list->headEntry = newEntry;
        list->tailEntry = newEntry;
    } else {
        list->tailEntry->next = newEntry;
        list->tailEntry = newEntry;
    }

    return 0; 
}

int ISsearchEntry(EntryList *list, const char *name) {
    Entry *current;

    if (list == NULL || name == NULL) {
        return -1; 
    }

    current = list->headEntry;
    while (current != NULL) {
        
        if (strcmp(current->name, name) == 0 && (strlen(current->name) == strlen(name))) {
            return 1;
        }
        current = (current->next);
    }

    return 0; 
}

Entry* searchEntry(EntryList *list, const char *name) {
    Entry *current;

    if (list == NULL || name == NULL) {
        return NULL; 
    }

    current = list->headEntry;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && (strlen(current->name) == strlen(name))) {
            return current;
        }
        current = (current->next);
    }

    return NULL; 
}
void cleanEntryList(EntryList *list) {
    Entry *current;
    Entry *next;

    if (list == NULL) {
        return; 
    }

    current = list->headEntry;
    while (current != NULL) {
        next = current->next;
        free(current->name);
        free(current);
        current = next;
    }

    list->headEntry = NULL;
    list->tailEntry = NULL;
}

void printEntryList(const EntryList *entryList) {
    Entry *current = entryList->headEntry;
    
    while (current != NULL) {
        printf("\nLine IC: %d, Name Length: %d, Name: %s\n",
               current->lineIcCurrent,
               current->nameLangth,
               current->name);
        current = current->next;
    }
}
/*extern*/
ExternList* createExternList() {
    ExternList *list = (ExternList*)malloc(sizeof(ExternList));
    if (!list) {
        return NULL; 
    }

    list->head = NULL;
    list->tail = NULL;
    return list;
}
Extern* createExtern(const char *name, int nameLength, int *lineIc, int lineIcCount) {
    Extern *newExtern = (Extern*)malloc(sizeof(Extern));
    if (!newExtern) {
        return NULL; 
    }

    newExtern->nameLangth = nameLength;
    newExtern->name = (char*)malloc(nameLength + 1); 
    if (!newExtern->name) {
        free(newExtern);
        return NULL;
    }
    strncpy(newExtern->name, name, nameLength);
    newExtern->name[nameLength] = '\0'; 

    newExtern->lineIcCount = lineIcCount;
    newExtern->lineIc = (int*)malloc(lineIcCount * sizeof(int));
    if (!newExtern->lineIc) {
        free(newExtern->name);
        free(newExtern);
        return NULL;
    }
    memcpy(newExtern->lineIc, lineIc, lineIcCount * sizeof(int));

    newExtern->next = NULL;
    return newExtern;
}


Extern* searchExtern(ExternList *list, const char *name) {
    Extern *current ;
    if (!list || !name) {
        return NULL;
    }

    current= list->head;
    while (current != NULL) {
        if (strncmp(current->name, name, current->nameLangth) == 0) {
            return current; 
        }
        current = current->next;
    }
    return NULL; 
}

int ISsearchExtern(ExternList *list, const char *name) {
    Extern *current;
    if (!list || !name) {
        return -1;
    }

     current= list->head;
    while (current != NULL) {
        if (strncmp(current->name, name, current->nameLangth) == 0) {
            return 1; 
        }
        current = current->next;
    }
    return 0; 
}

void cleanExternList(ExternList *list) {
    Extern *current;
    if (!list) {
        return;
    }

     current= list->head;
    while (current != NULL) {
        Extern *next = current->next;
        free(current->name);
        free(current->lineIc);
        free(current);
        current = next;
    }
    list->head = NULL;
    list->tail = NULL;
}
int createAndAddExtern(ExternList *list, const char *name, int nameLength) {
    Extern *newExtern;

    newExtern = (Extern*)malloc(sizeof(Extern));
    if (!newExtern) {
        /* Memory allocation failed for Extern */
        return -1; 
    }

    newExtern->name = (char*)malloc(nameLength + 1);
    if (!newExtern->name) {
         /* Clean up allocated memory if name allocation fails */
        free(newExtern);
        return -1;
    }
    strncpy(newExtern->name, name, nameLength);
    /* Ensure the name is null-terminated */
    newExtern->name[nameLength] = '\0'; 

    newExtern->lineIc = NULL;
    newExtern->lineIcCount = 0;

    newExtern->nameLangth = nameLength;
    newExtern->next = NULL;

    if (list->head == NULL) {
        list->head = newExtern;
        list->tail = newExtern;
    } else {
        list->tail->next = newExtern;
        list->tail = newExtern;
    }
/* Successfully created and added the Extern */
    return 0; 
}



int addLineIcToExtern(ExternList *list, const char *name, int lineIcValue) {
    Extern *foundExtern;
    int *newLineIc;

    foundExtern = searchExtern(list, name);
    if (!foundExtern) {
        /* Extern not found */
        return -1; 
    }

    newLineIc = (int*)realloc(foundExtern->lineIc, (foundExtern->lineIcCount + 1) * sizeof(int));
    if (!newLineIc) {
        /* Memory allocation failed */
        return -1; 
    }

    foundExtern->lineIc = newLineIc;
    foundExtern->lineIc[foundExtern->lineIcCount] = lineIcValue;
    foundExtern->lineIcCount++;
/* Successfully added lineIc value */
    return 0; 
}
void printExternList(const ExternList *list) {
    Extern *current;
    int i;

    if (!list) {
        printf("The list is empty or not initialized.\n");
        return;
    }

    current = list->head;
    while (current != NULL) {
        printf("Name: %s, Length: %d, Line IC Count: %d, Line ICs: ",
               current->name, current->nameLangth, current->lineIcCount);

        for (i = 0; i < current->lineIcCount; i++) {
            printf("%d", current->lineIc[i]);
            if (i < current->lineIcCount - 1) {
                printf(", ");
            }
        }
        printf("\n");

        current = current->next;
    }
}