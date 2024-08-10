
#include "symbol.h"

#define MAX_LINE_LENGTH 80
#define TOTAL_IC 4096

/**
 * Function to open both files for reading and writing.
 * It returns 1 if the files succeeded to open and the writing was ok, else returns 0.
 */
int writeLinesToFile(char *assemblerName, char *textName) {
    int success = 0;
    int stop = 0;
    int i = 0;
    int getProcLine=0;
    int fileIsOk=1;
    int numberLine=0;
    char *input = NULL;
    char c;
    /*error*/
    char EFailedOpen[] ="Failed to open files";
    char EFailedAllocate[] ="Failed to allocate memory";
    enum colorMessages myColor;

    FILE *fileWrite = fopen(assemblerName, "a+");
    FILE *fileRead = fopen(textName, "r");

    if (fileRead == NULL || fileWrite == NULL) {
        errorMessagesWithText(EFailedOpen,strlen(EFailedOpen),'r');
        if (fileRead) fclose(fileRead);
        if (fileWrite) fclose(fileWrite);
        return 0;
    }

    while (!stop) {
        input = (char *)malloc((MAX_LINE_LENGTH + 1) * sizeof(char));
        if (input == NULL) {
         errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'r');
         free(input);
         return -1;
        }
        numberLine++;
        i = 0;
        while ( (c = fgetc(fileRead)) != '\n' && c != EOF) {
            if(i < MAX_LINE_LENGTH){
            input[i++] = c;
            }
            else{
             errorMessagesInLine(numberLine,'r',1);
             free(input);
             fclose(fileRead);
             fclose(fileWrite);
            return -1;
            }
        } 
        if (c == EOF) {
            stop = 1;
            if (i == 0)
             break; 
        }
        getProcLine=-1;
        if(getProcLine==-1){
            fileIsOk=-1;
             errorMessagesInLine(numberLine,'r',0);
        }
        free(input);
    }

    fclose(fileRead);
    fclose(fileWrite);

    if (stop == 1) {
        success = 1;

    printf("done\n");
    }

    return success;
}

/**
 * Function to check whether a file exists or not.
 * It returns 1 if the file exists at the given path, otherwise returns 0.
 */
int isFileExists(char *path) {
    FILE *fptr = fopen(path, "r");

    if (fptr == NULL) {
        return 0;
    }

    fclose(fptr);
    return 1;
}

/**
 * Function to check whether a file exists or not and create a full assembled file.
 * It makes a file with .am extension after putting macros inside. If the file succeeded, returns 1, else returns 0.
 */
int firstPass(char *textFile) {
    int succeeded=0;
    size_t length ,newLength;
    char *dot,*fileName ;
    /*error messages*/
    char EfileDoesntexist[]="File does not exist at path";
    char EfileNoExtensiont[]="No file extension found";
    char EalreadyExists[] ="File already exists at path";
    char EFailedAllocate[] ="Failed to allocate memory";

    if (!isFileExists(textFile)) {
        errorMessagesWithTextExstra(EfileDoesntexist,strlen(EfileDoesntexist),textFile,strlen(textFile),'y');
        return 0;
    }

    dot = strrchr(textFile, '.');
    if (dot == NULL) {
      errorMessagesWithText(EfileNoExtensiont,strlen(EfileNoExtensiont),'r');
        return -1;
    }

    length = dot - textFile;
    newLength = length + 3;
    fileName = (char *)malloc((newLength + 1) * sizeof(char));

    if (fileName == NULL) {
        errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'y');
        free(fileName);
        return -1;
    }

    strncpy(fileName, textFile, length);
    fileName[length] = '\0';
    strcat(fileName, ".ob");

    if (isFileExists(fileName)) {
        errorMessagesWithText(EalreadyExists,strlen(EalreadyExists),'y');
        free(fileName);
        return 0;
    }
    
    succeeded = writeLinesToFile(fileName, textFile);
    free(fileName);
    /*
    if(errorPage){
        printf("!not good!");
        succeeded=-1;
    }
    */
    return succeeded;
}