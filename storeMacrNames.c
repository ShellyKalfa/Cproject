#include "header.h"

typedef struct macroName
{
    char *name;
    char *linesInMacro;
    struct macroName *next;   
}macroName;
typedef struct listMacro
{
    struct macroName *head;
    struct macroName *tail;
} listMacro;

int searchNameOfMacr(listMacro *list, char *nameMacr)
{
    macroName *temp = list->head;
    while (temp != NULL)
    {
        if (strcmp(temp->name, nameMacr) == 0)
        {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}
void addNameOfMacr(listMacro *list, char *nameMacr, char *linesInMacro)
{
    macroName *newNode = (macroName *)malloc(sizeof(macroName));
    newNode->name = (char *)malloc(sizeof(char) * strlen(nameMacr));
    strcpy(newNode->name, nameMacr);
    newNode->linesInMacro = (char *)malloc(sizeof(char) * strlen(linesInMacro));
    strcpy(newNode->linesInMacro, linesInMacro);
    newNode->next = NULL;
    if (list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        list->tail->next = newNode;
        list->tail = newNode;
    }
}
void freeListMacro(){
    macroName *temp = list->head;
    macroName *temp2;
    while (temp != NULL)
    {
        temp2=( macroName *)malloc(sizeof( macroName));
        temp2 = temp;
        temp = temp->next;
        free(temp2->name);
        free(temp2->linesInMacro);
        free(temp2);
    }
}
