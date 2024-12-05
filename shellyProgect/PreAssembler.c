#include "header.h"

#define MAX_LINE_LENGTH 80

int errorPage=0;
 line *getmacrText=NULL;
/**
 * Function to process and write a line to the file.
 * It returns 0 if the writing was successful, else returns -1.
 */
int procLine(FILE *fileWrite, char *line, int length,int numberLine) {
    char *text,*copyLine,*content;
    int whatToDo=0;
     /*error messages*/
    char EFailed[] ="Failed: something not right ";
    char EFailedAllocate[] ="Failed to allocate memory";
    if (fileWrite == NULL || line == NULL) {
        errorMessagesWithText(EFailed,strlen(EFailed),'y');
        return -1;
    }
    text = (char *)malloc((length+1) * sizeof(char));
    copyLine= (char *)malloc((length+2) * sizeof(char));
    if (text == NULL||copyLine== NULL) {
        errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'y');
        return -1;
    }
    
    strncpy(text, line, length);
    text[length] = '\0';
    strncpy(copyLine, line, length);
    copyLine[length] = '\n';
    copyLine[length+1] = '\0';
    whatToDo=checkLineForMacr(copyLine);
    if(!whatToDo)
    { 
        fprintf(fileWrite, "%s\n", text);
    }
    if(whatToDo == -1){
        errorPage=1;
         free(copyLine);
         free(text);
         return -1;
    }
    if(whatToDo==2){
       getmacrText= showLinesMacro(copyLine);
        while (getmacrText != NULL) 
        {
            content = getmacrText->content;
                fprintf(fileWrite, "%s", content);
            getmacrText = getmacrText->next;
        }
    }
     if(getmacrText!=NULL){
        clearLinesInMacro(&getmacrText);
     }
    free(copyLine);
    free(text);
    return 0;
}

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
     /*error messages*/
    char EFailedOpen[] ="Failed to open files";
    char EFailedAllocate[] ="Failed to allocate memory";
    char EfileEmpty[] ="Your file is empty";
    char Msuccess[] ="success pre assmbler";
    char MFailed[] ="Your file Failed in macro";

    FILE *fileWrite = fopen(assemblerName, "a+");
    FILE *fileRead = fopen(textName, "r");

    if (fileRead == NULL || fileWrite == NULL) {
        errorMessagesWithText(EFailedOpen,strlen(EFailedOpen),'r');
        if (fileRead) fclose(fileRead);
        if (fileWrite) fclose(fileWrite);
        return 0;
    }

    initialize();
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
               fclose(fileRead);
               fclose(fileWrite);
               free(input);
               input=NULL;
               return -1;
            }
        }
        input[i] = '\0';
        
        if (c == EOF) {
         stop = 1;
          if (i == 0){
             if(numberLine == 1){
                  errorMessagesWithText(EfileEmpty,strlen(EfileEmpty),'r');
                  fclose(fileRead);
                  fclose(fileWrite);
                  free(input);
                  input=NULL;
                  return -1 ;
             }
             break;
          }
        }
        if(i != 0){
          getProcLine=procLine(fileWrite, input, i,numberLine);
        }else
        {
            getProcLine=0;
        }
        
        if(getProcLine == -1){
            fileIsOk=0;
           errorMessagesInLine(numberLine,'r',0);
        } 
        if(input != NULL){
        free(input);
        input=NULL;
        }
    }
    tableFree();

    fclose(fileRead);
    fclose(fileWrite);

    if (stop == 1&&fileIsOk!=-1) {
        success = 1;
        errorMessagesWithText(Msuccess,strlen(Msuccess),'g');
    }
    if(!fileIsOk){
      errorMessagesWithText(MFailed,strlen(MFailed),'r');
      success = -1;
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
int preAssembler(char *textFile) {
    int succeeded;
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
    strcat(fileName, ".am");

    if (isFileExists(fileName)) {
        errorMessagesWithText(EalreadyExists,strlen(EalreadyExists),'y');
        free(fileName);
        return 0;
    }
     succeeded = writeLinesToFile(fileName, textFile);
   
    if(errorPage){
        printf("!not good!");
        succeeded=-1;
    }
     free(fileName);
    return succeeded;
}
