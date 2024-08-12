#include "header.h"


int main(int argc, char *argv[]) {
     int i;
     size_t length,newLength;
     char *fileName;
      /*error messages*/
     char EFailedAllocate[] ="Failed to allocate memory";
     char EMissingFilenames[] ="Missing filenames";

     printf("arg = %d \n",argc);
     if(argc == 1){
        errorMessagesWithText(EMissingFilenames,strlen(EMissingFilenames),'r');
        return -1;
     }

     for(i=1;i<argc;i++){
        length=strlen(argv[i]);
        newLength = length + 3;  
        fileName = (char *)malloc((newLength + 1) * sizeof(char));
        if (fileName == NULL) {
            errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'y');
            return -1;
        }
        strncpy(fileName, argv[i], length);
        fileName[length] = '\0'; 
        strcat(fileName, ".as");
        preAssembler(fileName);
        free(fileName);
        fileName=NULL;
    }
    printf("done");
    return 0;
}