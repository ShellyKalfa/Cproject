#include "firstPassHeader.h"

/*create tabel for all symbols(or list)*/
SymbolTabel* createSymbolTabel() {
    SymbolTabel *table = (SymbolTabel *)malloc(sizeof(SymbolTabel));
    if (table == NULL) {
        /*error*/
        return NULL; 
    }
    table->symbols=NULL;
    table->size=0;
    return table;
}

void cleanSymbolTabel(SymbolTabel *table) {
    int sizeTabel=0,i;
    sizeTabel= table->size;
    if (table != NULL) {
        if (table->symbols != NULL) {
            for ( i = 0; i < sizeTabel; i++) {
                free(table->symbols[i]->nameSymbol);
            }
            free(table->symbols);
        }
        free(table);
    }
}

int searchSymbolTabel(SymbolTabel *table, const char *name) {
    int i,sizeTabel=0;
    sizeTabel= table->size;
    if (table == NULL || table->symbols == NULL) {
        /*error*/
        return -1; 
    }

    for ( i = 0; i < sizeTabel; i++) {
      if (strcmp(table->symbols[i].nameSymbol, name) == 0 && strlen(table->symbols[i].nameSymbol) == strlen(name) ) {
            return i; 
        }
    }

    return -1;
}

SymbolName* searchSymbolTabel(SymbolTabel *table, const char *name) {
    int i;
    if (table == NULL || table->symbols == NULL) {
        return NULL; 
    }
    for ( i = 0; i < table->size; i++) {
        if (strcmp(table->symbols[i].nameSymbol, name) == 0) {
            return &table->symbols[i]; 
        }
    }

    return NULL; 
}

int addSymbol(SymbolTabel *table, const char *name, char DCorIC, int placeInCode) {
    int sizeTabel = table->size;
    SymbolName *newSymbols ;
    newSymbols = (SymbolName *)realloc(table->symbols, sizeof(SymbolName) * (sizeTabel + 1));
    if (newSymbols == NULL) {
        return -1; 
    }

    table->symbols = newSymbols;

    table->symbols[sizeTabel].nameSymbol = (char *)malloc(strlen(name) + 1);
    if (table->symbols[sizeTabel].nameSymbol == NULL) {
        return -1; 
    }

    strcpy(table->symbols[sizeTabel].nameSymbol, name);

    table->symbols[sizeTabel].lengthName = strlen(name);
    table->symbols[sizeTabel].DCorIC = DCorIC;
    table->symbols[sizeTabel].placeInCode = placeInCode;

    table->size++; 

    return sizeTabel;
}