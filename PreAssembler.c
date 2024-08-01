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
    if (fileWrite == NULL || line == NULL) {
        return -1;
    }
   text = (char *)malloc((length + 2) * sizeof(char));
   copyLine= (char *)malloc((length + 2) * sizeof(char));
    if (text == NULL||copyLine== NULL) {
        perror("Error allocating memory");
        return -1;
    }
    
    strncpy(text, line, length);
    text[length] = '\0';
    strncpy(copyLine, line, length);
    copyLine[length] = '\0';
    whatToDo=checkLineForMacr(line);
    if(!whatToDo)
    { 
        fprintf(fileWrite, "%s\n", text);
    }
    if(whatToDo==-1){
        errorPage=1;
    }
    if(whatToDo==2){
       getmacrText= showLinesMacro(line);
        while (getmacrText != NULL) 
        {
            content = getmacrText->content;
                fprintf(fileWrite, "%s\n", content);
            getmacrText = getmacrText->next;
        }
    }
       
   

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
    enum colorMessages myColor;

    FILE *fileWrite = fopen(assemblerName, "a+");
    FILE *fileRead = fopen(textName, "r");

    if (fileRead == NULL || fileWrite == NULL) {
        perror("Failed to open files");
        if (fileRead) fclose(fileRead);
        if (fileWrite) fclose(fileWrite);
        return 0;
    }
    reboot();

    while (!stop) {
        input = (char *)malloc((MAX_LINE_LENGTH + 1) * sizeof(char));
        if (input == NULL) {
            perror("Error allocating memory");
            break;
        }
        numberLine++;
        i = 0;
        while (i < MAX_LINE_LENGTH && (c = fgetc(fileRead)) != '\n' && c != EOF) {
            input[i++] = c;
        }
        input[i] = '\0';
        if(i > MAX_LINE_LENGTH){
            myColor=RED;
            errorMessages (myColor);
            printf("error in line i%d: this line has exceeded the limit",i);
            myColor=WHITE;
            errorMessages (myColor);
            break;
        } 
        if (c == EOF) {
            stop = 1;
            if (i == 0)
             break; 
        }

        getProcLine=procLine(fileWrite, input, i,numberLine);
        if(getProcLine==-1){
            fileIsOk=0;
        }
        free(input);
    }
    tableFree();

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
int preAssembler(char *textFile) {
    int succeeded;
    size_t length ,newLength;
    char *dot,*fileName ;
    /*color to messges */
    enum colorMessages myColor ;

    if (!isFileExists(textFile)) {
        myColor=RED;
        errorMessages (myColor);
        printf("\nFile does not exist at path '%s'\n", textFile);
        myColor=WHITE;
        errorMessages (myColor);
        return 0;
    }
    dot = strrchr(textFile, '.');
    if (dot == NULL) {
        myColor=RED;
        errorMessages (myColor);
        fprintf(stderr, "No file extension found\n");
        myColor=WHITE;
        errorMessages (myColor);
        return -1;
    }

   length = dot - textFile;
    newLength = length + 3;
    fileName = (char *)malloc((newLength + 1) * sizeof(char));

    if (fileName == NULL) {
        myColor=RED;
        errorMessages (myColor);
        perror("Failed to allocate memory\n");
        myColor=WHITE;
        errorMessages (myColor);
        return -1;
    }

    strncpy(fileName, textFile, length);
    fileName[length] = '\0';
    strcat(fileName, ".am");

    if (isFileExists(fileName)) {
         myColor=RED;
        errorMessages (myColor);
        printf("\nFile already exists at path '%s'\n", fileName);
        myColor=WHITE;
        errorMessages (myColor);
        free(fileName);
        return 0;
    }

     succeeded = writeLinesToFile(fileName, textFile);
    free(fileName);

    return succeeded;
}
