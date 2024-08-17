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

EntryList *createEntryList() {
    EntryList *list = malloc(sizeof(EntryList));
    if (list == NULL) {
        perror("Failed to allocate memory");
        return NULL;
    }
    list->headEntry = NULL;
    list->tailEntry = NULL;

    return list;
}

Entry *createEntry(const char *name, int lineIcCurrent) {
    Entry *newEntry = malloc(sizeof(Entry));
    if (newEntry == NULL) {
        perror("Failed to allocate memory");
        return NULL;
    }
    
    newEntry->nameLangth = strlen(name);
    newEntry->name = malloc((newEntry->nameLangth + 1) * sizeof(char));
    if (newEntry->name == NULL) {
        perror("Failed to allocate memory");
        free(newEntry);
        return NULL;
    }
    strcpy(newEntry->name, name);
    newEntry->lineIcCurrent = lineIcCurrent;
    newEntry->next = NULL;

    return newEntry;
}
int addEntryToList(EntryList *list, Entry *newEntry) {
    if (list == NULL || newEntry == NULL) {
        return -1;
    }

    if (list->headEntry == NULL) {
        list->headEntry = newEntry;
        list->tailEntry = newEntry;
    } else {
        list->tailEntry->next = newEntry;
        list->tailEntry = newEntry;
    }

    return 0;
}

Entry *searchEntry(EntryList *list, const char *name) {
    Entry *current;
    if (list == NULL) {
        return NULL;
    }

    current = list->headEntry;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL; 
}
void cleanEntryList(EntryList *list) {
    if (list == NULL) {
        return;
    }

    Entry *current = list->headEntry;
    Entry *nextEntry;

    while (current != NULL) {
        nextEntry = current->next;
        free(current->name);
        free(current);
        current = nextEntry;
    }

    free(list);
}
