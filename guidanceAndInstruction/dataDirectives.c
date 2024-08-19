#include "firstPassHeader.h"

#define MAX_SIZE_DATA 37
#define MAX_SIZE_STRING 70
#define MAX_LINE_LENGTH 80

int data[MAX_SIZE_DATA];
char string[MAX_SIZE_STRING];
Entry * listOfEntry=NULL;
int entryCount = 0;
Extern *listOfExtern;
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

int addEntry(EntryList *list, int lineIcCurrent, const char *name) {
    Entry *newEntry;

    if (list == NULL || name == NULL) {
        return -1;
    }

    newEntry = (Entry *)malloc(sizeof(Entry)*1);
    if (newEntry == NULL) {
        return -1; 
    }

    newEntry->lineIcCurrent = lineIcCurrent;
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


Entry* searchEntry(EntryList *list, const char *name) {
    Entry *current;

    if (list == NULL || name == NULL) {
        return NULL; 
    }

    current = list->headEntry;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
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



