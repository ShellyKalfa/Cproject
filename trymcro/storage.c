#include "storage.h"

/*Hash Function*/
unsigned int hash(char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash << 5) + *str++;
    }
    return hash % TABLE_SIZE;
}
/*Initialize the Hash Table*/
HashTable* createHashTable() {
    int i;
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    table->table = (macroName **)malloc(TABLE_SIZE * sizeof(macroName *));
    for ( i= 0; i < TABLE_SIZE; i++) {
        table->table[i] = NULL;
    }
    return table;
}
/*Insert Function*/
void addNameOfMacr(HashTable *table, char *nameMacr, char *linesInMacro) {
    unsigned int index = hash(nameMacr);
    macroName *newNode = (macroName *)malloc(sizeof(macroName));
    newNode->name = (char *)malloc(strlen(nameMacr) + 1);
    strcpy(newNode->name, nameMacr);
    newNode->linesInMacro = (char *)malloc(strlen(linesInMacro) + 1);
    strcpy(newNode->linesInMacro, linesInMacro);
    newNode->next = table->table[index];
    table->table[index] = newNode;
}
/*Search Function*/
int searchNameOfMacr(HashTable *table, char *nameMacr) {
    unsigned int index = hash(nameMacr);
    macroName *temp = table->table[index];
    while (temp != NULL) {
        if (strcmp(temp->name, nameMacr) == 0) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}
/*search Name Of Macr and Return Line*/
char* searchNameOfMacrReturnLine(HashTable *table, char *nameMacr) {
    unsigned int index = hash(nameMacr);
    macroName *temp = table->table[index];
    while (temp != NULL) {
        if (strcmp(temp->name, nameMacr) == 0) {
            return temp->linesInMacro;
        }
        temp = temp->next;
    }
    return NULL;  
}
/*Delete Function*/
void deleteNameOfMacr(HashTable *table, char *nameMacr) {
    unsigned int index = hash(nameMacr);
    macroName *temp = table->table[index];
    macroName *prev = NULL;

    while (temp != NULL && strcmp(temp->name, nameMacr) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return; 

    if (prev == NULL) {
        table->table[index] = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp->name);
    free(temp->linesInMacro);
    free(temp);
}
/*Free Function*/
void freeHashTable(HashTable *table) {
    macroName *next,*temp;
    int i;
    for ( i = 0; i < TABLE_SIZE; i++) {
        temp = table->table[i];
        while (temp != NULL) {
            next = temp->next;
            free(temp->name);
            free(temp->linesInMacro);
            free(temp);
            temp = next;
        }
    }
    free(table->table);
    free(table);
}
/**/
