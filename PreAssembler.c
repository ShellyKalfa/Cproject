#include "header.h"

#define MAX_LINE_LENGTH 80
/**
 * Function open file for writting lines in it.
 * It returns 0 if the files succeeded to open and the writing was ok
 * else returns -1.
 */

int procLine( FILE *fileWrite,char *line,int length){
   char *text;
    if (fileWrite == NULL || line == NULL) {
        return -1; 
    }
    text = (char *)malloc((length + 2) * sizeof(char));
    if (text == NULL) {
        perror("Error allocating memory");
        return -1;
    }

    strncpy(text, line, length);
    text[length + 1] = '\0';

  fprintf(fileWrite,"%s",text);

    return 0;

}



/**
 * Function open both files for reading and writting.
 * It returns 1 if the files succeeded to open and the writing was ok
 * else returns 0.
 */
int writeLinesToFile( char *assemblerName,char *textName) {
    int success=0 ,stop=0,i;
    char *input=NULL,c ;
    FILE *fileWrite = fopen(assemblerName, "a+");
    FILE *fileRead = fopen(textName, "r");
    if (fileRead == NULL ||fileWrite == NULL) {
        perror("Failed to open files");
        success=0;
        return success;
    }
    while (!stop)
    {
       while ((c = fgetc(fileRead)) != '\n'&&!stop)
      {
        if (c == EOF)
        {
            stop=1;
            break;
        }
        input = (char *)realloc(input, (i + 2) * sizeof(char));
        input[i] = c;
        i++;
        if(i>MAX_LINE_LENGTH){
            stop=-1;
            break; 
          }
      

      }
       if(i<MAX_LINE_LENGTH){
           stop=procLine(fileWrite,input,i);
           free(input);
        }
    }
    fclose(fileRead);
    fclose(fileWrite);
    printf("done");

    if(stop==-1 ||stop==0)
    {
        success=0;
    }
    else{
        success=1;
    }    
    return success;
    
    
}

/**
 * Function to check whether a file exists or not.
 * It returns 1 if file exists at given path otherwise
 * returns 0.
 */
int isFileExists(char *path)
{
    /* Try to open file */
    FILE *fptr = fopen(path, "r");

    /* If file does not exists  */
    if (fptr == NULL)
        return 0;

    /* File exists hence close file and return true. */
    fclose(fptr);

    return 1;
}

/**
 * Function to check whether a file exists or not and create a full assemble file.
 * It make a file .am after puting macros inside if file succeeded returns 1 else
 * returns 0.
 */
int preAssembler(char *textFile)
{
    int succeeded=0;
     size_t length;
     size_t newLength;
     char *fileName;
     char *dot = strrchr(textFile, '.');
     if (!isFileExists(textFile))
    {
        printf("\nFile does not exists at path '%s'\n", textFile);
         return 0;
    }
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
      if (isFileExists(fileName))
    {
        printf("\nFile does exists at path '%s'\n", fileName);
         return 0;
    }
    succeeded =writeLinesToFile(fileName,textFile);
    return succeeded;
}
