#include "firstPassHeader.h"

#define MAX_LINE_LENGTH 80

#define START_L 100

int main(int argc, char const *argv[])
{
  int fileOK=0;
  char fileAm[]="ps.am";


    firstPass(fileAm);
 
  

    return 0;
    
}



/*
 EntryList *myList;
    Entry *foundEntry;
    int result;

    myList = createEntryList();
    if (myList == NULL) {
        fprintf(stderr, "Failed to create entry list.\n");
        return EXIT_FAILURE;
    }

    result = addEntry(myList, 100, "FirstEntry");
    if (result != 0) {
        fprintf(stderr, "Failed to add 'FirstEntry' to the list.\n");
        cleanEntryList(myList);
        free(myList);
        return EXIT_FAILURE;
    }

    result = addEntry(myList, 200, "SecondEntry");
    if (result != 0) {
        fprintf(stderr, "Failed to add 'SecondEntry' to the list.\n");
        cleanEntryList(myList);
        free(myList);
        return EXIT_FAILURE;
    }

    foundEntry = searchEntry(myList, "FirstEntry");
    if (foundEntry != NULL) {
        printf("Found entry: %s, lineIcCurrent: %d\n", foundEntry->name, foundEntry->lineIcCurrent);
    } else {
        printf("Entry 'FirstEntry' not found.\n");
    }

    cleanEntryList(myList);
    free(myList);
    
     while (1)
    {
    symbol
    printf("\nEnter a line:\n ");
    if (fgets(line, sizeof(line), stdin) != NULL) {
      fileOK=handelLine(line);
    } else {
        printf("Error reading input.\n");
    } 
    printf("fileOK %d",fileOK);
   }
    
    
    
    */
