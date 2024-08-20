#include "firstPassHeader.h"

/**/
DClist * myDClist=NULL;
/**/
IClist * myIClist=NULL;

/*DC*/
DClist * createDClist() {
    DClist *list = (DClist *)malloc(sizeof(DClist));
    if (list == NULL) return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->numbersOfLineInDC = 0;

    return list;
}

DCline* createDCline(unsigned short line) {
    DCline *node = (DCline *)malloc(sizeof(DCline));
    if (node == NULL) return NULL;

    node->LinesInDC = line;
    node->next = NULL;

    return node;
}


int addLineToDClist(DClist *list, unsigned short line) {
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
    DCline *current,*nextNode;
    if (list == NULL) return;

    current = list->head;

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

ICline* createICline(unsigned short line) {
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

SymbolLineInIC * createSymbolLineInIC(const char *name, int placeInIc) {
    SymbolLineInIC *node = (SymbolLineInIC *)malloc(sizeof(SymbolLineInIC));
    if (node == NULL) return NULL;

    node->nameSymbol = (char*)malloc(sizeof(char) * (strlen(name)));
    if (node->nameSymbol == NULL) {
        free(node);
        return NULL;
    }
    strcpy(node->nameSymbol, name);

    node->lengthName = strlen(name);
    node->placeInIc = placeInIc;
    node->next = NULL;

    return node;
}

int addLineToIClist(IClist *list, unsigned short line) {
    ICline * newNode;
    if (list == NULL) return -1;

    newNode = (ICline *)malloc(sizeof(ICline));
    if (newNode == NULL) return -1;

    newNode->LinesInIC = line;
    newNode->next = NULL;

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

int addSymbolToHeadSymbolLinesToFill(IClist *list, const char *name) {
    SymbolLineInIC *newSymbol;
     int placeInIc;
    if (list == NULL) return -1;
    
    placeInIc=list->numbersOfLineInIC;

    newSymbol = createSymbolLineInIC(name, placeInIc);
    if (newSymbol == NULL) return -1;

    if (list->HeadSymbolLinesToFill == NULL) {
        list->HeadSymbolLinesToFill = newSymbol;
        list->TailSymbolLinesToFill = newSymbol;
    } else {
        list->TailSymbolLinesToFill->next = newSymbol;
        list->TailSymbolLinesToFill = newSymbol;
    }

    return 1;
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
    ICline *currentICLine = list->head;
    ICline *nextICLine;
    SymbolLineInIC *currentSymbolLine = list->HeadSymbolLinesToFill;
    SymbolLineInIC *nextSymbolLine;

    while (currentICLine != NULL) {
        nextICLine = currentICLine->next;
        free(currentICLine);
        currentICLine = nextICLine;
    }

    while (currentSymbolLine != NULL) {
        nextSymbolLine = currentSymbolLine->next;
        free(currentSymbolLine->nameSymbol); 
        free(currentSymbolLine);
        currentSymbolLine = nextSymbolLine;
    }

    list->head = NULL;
    list->tail = NULL;
    list->numbersOfLineInIC = 0;
    list->HeadSymbolLinesToFill = NULL;
    list->TailSymbolLinesToFill = NULL;
}
void printDClist(DClist *list) {
    DCline *currentLine = list->head;

    printf("\nDC List (Number of Lines: %d):\n", list->numbersOfLineInDC);
    printf("--------------------------\n");
    printf("| %-5s |\n", "Line");
    printf("--------------------------\n");

    while (currentLine != NULL) {
        printf("| %-5hu |\n", currentLine->LinesInDC);
        currentLine = currentLine->next;
    }

    printf("--------------------------\n");
}

void printIClist(IClist *list) {
    ICline *currentICLine = list->head;
    SymbolLineInIC *currentSymbolLine = list->HeadSymbolLinesToFill;

    printf("\nIC List (Number of Lines: %d):\n", list->numbersOfLineInIC);
    printf("------------------------------\n");
    printf("| %-8s |\n", "Line");
    printf("------------------------------\n");

   
    while (currentICLine != NULL) {
        printf("|%-11o |\n", currentICLine->LinesInIC);
        currentICLine = currentICLine->next;
    }

    printf("------------------------------\n");

    printf("Symbol Lines to Fill:\n");
    printf("---------------------------------------------------------\n");
    printf("| %-10s | %-8s | %-10s |\n", "Name", "Length", "Place in IC");
    printf("---------------------------------------------------------\n");

    
    while (currentSymbolLine != NULL) {
        printf("| %-10s | %-8d | %-10d |\n",
               currentSymbolLine->nameSymbol,
               currentSymbolLine->lengthName,
               currentSymbolLine->placeInIc);
        currentSymbolLine = currentSymbolLine->next;
    }

    printf("---------------------------------------------------------\n");
}