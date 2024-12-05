#include "firstPassHeader.h"

/*my Symbol Tabel (real list) it global -saveing the data for ic*/
SymbolTabel * mySymbolTabel =NULL;

/* Create a table for all symbols (or list) */
SymbolTabel* createSymbolTabel() {
    SymbolTabel *table;
    
    table = (SymbolTabel *)malloc(sizeof(SymbolTabel));
    if (table == NULL) {
        return NULL; 
    }
    table->HeadSymbols = NULL;
    table->TailSymbols = NULL;
    table->size = 0;
    
    return table;
}
/*clean Symbol Tabel*/
void cleanSymbolTabel(SymbolTabel *table) {
    SymbolName *currentSymbol, *nextSymbol;
    if (table != NULL) {
        currentSymbol = table->HeadSymbols;
        while (currentSymbol != NULL) {
            nextSymbol = currentSymbol->next;
            free(currentSymbol->nameSymbol);
            free(currentSymbol);
            currentSymbol = nextSymbol;
        }
        free(table);
    }
}
/*search Symbol 
*reurn the SymbolName if fount else null
*/
SymbolName* searchSymbol(SymbolTabel *table, const char *nameSymbol) {
    SymbolName *current;
    
    if (table == NULL || nameSymbol == NULL) {
        return NULL; 
    }
    
    current = table->HeadSymbols;
    while (current != NULL) {
        if (strcmp(current->nameSymbol, nameSymbol) == 0) {
            return current;
        }
        current = current->next;
    }
    
    return NULL;
}
/*search Symbol 
*reurn the 1 if fount else 0
*/
int ISsearchSymbol(SymbolTabel *table, const char *nameSymbol) {
    SymbolName *current;
    
    if (table == NULL || nameSymbol == NULL) {
        return -1; 
    }
    
    current = table->HeadSymbols;
    while (current != NULL) {
        if (strcmp(current->nameSymbol, nameSymbol) == 0) {
            return 1;
        }
        current = current->next;
    }
    
    return 0;
}
/*function  add Symbol
*reurn the 1 if successes else 0
*/
int addSymbol(SymbolTabel *table, const char *nameSymbol, int lengthName, char DCorIC, int placeInCode) {
    SymbolName *newSymbol;
    
    if (table == NULL || nameSymbol == NULL) {
        return -1; 
    }
    
    newSymbol = (SymbolName *)malloc(sizeof(SymbolName));
    if (newSymbol == NULL) {
        return -1; 
    }
    
    newSymbol->nameSymbol = (char *)malloc(lengthName + 1);
    if (newSymbol->nameSymbol == NULL) {
        free(newSymbol);
        return -1; 
    }
    strcpy(newSymbol->nameSymbol, nameSymbol);
    
    newSymbol->lengthName = lengthName;
    newSymbol->DCorIC = DCorIC;
    newSymbol->placeInCode = placeInCode;
    newSymbol->next = NULL;
    
    if (table->TailSymbols == NULL) { 
        table->HeadSymbols = newSymbol;
        table->TailSymbols = newSymbol;
    } else {
        table->TailSymbols->next = newSymbol;
        table->TailSymbols = newSymbol;
    }
    
    table->size++;
    
    return 0; 
}
/*
*print Symbol Tabel to the trminal so you can learn from it
*/
void printSymbolTabel(SymbolTabel *table) {
    SymbolName *currentSymbol = table->HeadSymbols;

    printf("Symbol Table (Size: %d):\n", table->size);
    printf("-----------------------------------------\n");
    printf("| %-10s | %-8s | %-5s | %-10s |\n", "Name", "Length", "Type", "Place");
    printf("-----------------------------------------\n");

    while (currentSymbol != NULL) {
        printf("| %-10s | %-8d | %-5c | %-10d |\n", 
                currentSymbol->nameSymbol, 
                currentSymbol->lengthName, 
                currentSymbol->DCorIC, 
                currentSymbol->placeInCode);
        
        currentSymbol = currentSymbol->next;
    }

    printf("-----------------------------------------\n");
}
