#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 80

/**
 * Function to process and write a line to the file.
 * It returns 0 if the writing was successful, else returns -1.
 */
int procLine(FILE *fileWrite, char *line, int length) {
    char *text ;
    if (fileWrite == NULL || line == NULL) {
        return -1;
    }
   text = (char *)malloc((length + 2) * sizeof(char));
    if (text == NULL) {
        perror("Error allocating memory");
        return -1;
    }
    strncpy(text, line, length);
    text[length] = '\0';

    fprintf(fileWrite, "%s\n", text);

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
    char *input = NULL;
    char c;

    FILE *fileWrite = fopen(assemblerName, "a+");
    FILE *fileRead = fopen(textName, "r");

    if (fileRead == NULL || fileWrite == NULL) {
        perror("Failed to open files");
        if (fileRead) fclose(fileRead);
        if (fileWrite) fclose(fileWrite);
        return 0;
    }

    while (!stop) {
        input = (char *)malloc((MAX_LINE_LENGTH + 1) * sizeof(char));
        if (input == NULL) {
            perror("Error allocating memory");
            break;
        }

        i = 0;
        while (i < MAX_LINE_LENGTH && (c = fgetc(fileRead)) != '\n' && c != EOF) {
            input[i++] = c;
        }
        input[i] = '\0'; 

        if (c == EOF) {
            stop = 1;
            if (i == 0) break; 
        }

        if (procLine(fileWrite, input, i) == -1) {
            stop = -1;
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
int preAssembler(char *textFile) {
    int succeeded;
    size_t length ,newLength;
    char *dot,*fileName ;
    
    if (!isFileExists(textFile)) {
        printf("\nFile does not exist at path '%s'\n", textFile);
        return 0;
    }
    dot = strrchr(textFile, '.');
    if (dot == NULL) {
        fprintf(stderr, "No file extension found\n");
        return -1;
    }

   length = dot - textFile;
    newLength = length + 3;
    fileName = (char *)malloc((newLength + 1) * sizeof(char));

    if (fileName == NULL) {
        perror("Failed to allocate memory\n");
        return -1;
    }

    strncpy(fileName, textFile, length);
    fileName[length] = '\0';
    strcat(fileName, ".am");

    if (isFileExists(fileName)) {
        printf("\nFile already exists at path '%s'\n", fileName);
        free(fileName);
        return 0;
    }

     succeeded = writeLinesToFile(fileName, textFile);
    free(fileName);

    return succeeded;
}
