#include "firstPassHeader.h"

/*DC*/
DClist* createDClist() {
    DClist *list = (DClist *)malloc(sizeof(DClist));
    if (list == NULL) return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->numbersOfLineInDC = 0;

    return list;
}

DCline* createDCline(short line) {
    DCline *node = (DCline *)malloc(sizeof(DCline));
    if (node == NULL) return NULL;

    node->LinesInDC = line;
    node->next = NULL;

    return node;
}

int addLineToDClist(DClist *list, short line) {
    DCline *newNode;
    if (list == NULL) return -1;

    newNode = createDCline(line);
    if (newNode == NULL) return -1;

    if (list->numbersOfLineInDC == 0) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }

    list->numbersOfLineInDC++;
    return 0;
}

void cleanDClist(DClist *list) {
    DCline *current,nextNode;
    if (list == NULL) return;

    current = list->head;
    nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    list->head = NULL;
    list->tail = NULL;
    list->numbersOfLineInDC = 0;
}
/*IC*/

ICline* createICline(short line) {
    ICline *node = (ICline *)malloc(sizeof(ICline));
    if (node == NULL)
    { return NULL;}

    node->LinesInIC = line;
    node->next = NULL;

    return node;
}

IClist* createIClist() {
    IClist *list = (IClist *)malloc(sizeof(IClist));
    if (list == NULL) return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->numbersOfLineInIC = 0;
    list->HeadSymbolLinesToFill = NULL;
    list->TailSymbolLinesToFill = NULL;

    return list;
}

SymbolLineInIC* createSymbolLineInIC(const char *name, int placeInIc) {
    SymbolLineInIC *node = (SymbolLineInIC *)malloc(sizeof(SymbolLineInIC));
    if (node == NULL) return NULL;

    node->nameSymbol = strdup(name);
    if (node->nameSymbol == NULL) {
        free(node);
        return NULL;
    }

    node->lengthName = strlen(name);
    node->placeInIc = placeInIc;
    node->next = NULL;

    return node;
}

int addLineToIClist(IClist *list, short line) {
    ICline *newNode;
    if (list == NULL) return -1;

    newNode = createICline(line);
    if (newNode == NULL) return -1;

    if (list->numbersOfLineInIC == 0) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }

    list->numbersOfLineInIC++;
    return 0;
}

int addSymbolToHeadSymbolLinesToFill(IClist *list, const char *name, int placeInIc) {
    SymbolLineInIC *newSymbol;
    if (list == NULL) return -1;

    newSymbol = createSymbolLineInIC(name, placeInIc);
    if (newSymbol == NULL) return -1;

    if (list->HeadSymbolLinesToFill == NULL) {
        list->HeadSymbolLinesToFill = newSymbol;
        list->TailSymbolLinesToFill = newSymbol;
    } else {
        list->TailSymbolLinesToFill->next = newSymbol;
        list->TailSymbolLinesToFill = newSymbol;
    }

    return 0;
}
void cleanIClineList(ICline *head) {
    ICline *current,*nextNode;
    current = head;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
}
void cleanSymbolLineInICList(SymbolLineInIC *head) {
    SymbolLineInIC *current = head,*nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current->nameSymbol);
        free(current);
        current = nextNode;
    }
}
void cleanIClist(IClist *list) {
    if (list == NULL) return;

    cleanIClineList(list->head);

    cleanSymbolLineInICList(list->HeadSymbolLinesToFill);

    list->head = NULL;
    list->tail = NULL;
    list->numbersOfLineInIC = 0;
    list->HeadSymbolLinesToFill = NULL;
    list->TailSymbolLinesToFill = NULL;

    free(list);
}