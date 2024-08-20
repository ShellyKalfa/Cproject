#include "header.h"
#include "firstPassHeader.h"

int main(int argc, char *argv[]) {
     int i,succssesPre=-1,successeSecound=-1;
     size_t length,newLength;
     char *fileName;
      /*error messages*/
     char EFailedAllocate[] ="Failed to allocate memory";
     char EMissingFilenames[] ="Missing filenames";
     char EMissingsecond[] ="problem in the second pass";
     char Msuccessfile[] ="file Sucsses";
     char Mfaildfile[] ="file Failed";

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
        succssesPre=preAssembler(fileName);
        if(succssesPre!=-1&&succssesPre)
       { successeSecound=firstPass(fileName);}
       if(successeSecound==-1){
           errorMessagesWithText(EMissingsecond,strlen(EMissingsecond),'r');
       }
       if(succssesPre==-1){
         return-1;
       }
       if(succssesPre==1&&successeSecound==1){
                errorMessagesWithTextExstra(Msuccessfile,strlen(Msuccessfile),fileName,strlen(fileName),'g');
       }else{
                errorMessagesWithTextExstra(Mfaildfile,strlen(Mfaildfile),fileName,strlen(fileName),'r');
       }
        printf("----------------------------done file:%s-------------------------\n",fileName);
        free(fileName);
        fileName=NULL;
    }
    printf("done");
    return 0;
}