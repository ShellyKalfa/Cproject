#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int preAssembler(const char *nameFile)
{
     size_t length;
     size_t newLength;
     char *fileName;
    const char *dot = strrchr(nameFile, '.');
    if (dot == NULL) {
        fprintf(stderr, "No file extension found\n");
        return -1;
    }
     length = dot - nameFile; 
     newLength = length + 3;  
     fileName = (char *)malloc((newLength + 1) * sizeof(char));
    
    if (fileName == NULL) {
        perror("Failed to allocate memory");
        return -1;
    }
    strncpy(fileName, nameFile, length);
    fileName[length] = '\0'; 

    strcat(fileName, ".am");
    printf("New File Name: %s\n", fileName);

    free(fileName);

    return 0;
}

int main() {

    const char *nameFile = "file.as";
    preAssembler(nameFile);

    return 0;
}
