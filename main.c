#include "header.h"


int main(int argc, char *argv[]) {
    int i;
     size_t length,newLength;
     char *fileName;
printf("arg = %d",argc);
    for(i=1;i<argc;i++){
        length=strlen(argv[i]);
        newLength = length + 3;  
       fileName = (char *)malloc((newLength + 1) * sizeof(char));
     
        
    if (fileName == NULL) {
        perror("Failed to allocate memory");
        return -1;
    }
    strncpy(fileName, argv[i], length);
    fileName[length] = '\0'; 

    strcat(fileName, ".as");
    preAssembler(fileName);
    }
    printf("done");
    return 0;
}