int saveCurrentMacr(char *nameSymbol,int ISsave){
  int i ,length=0,inTabel=1;
  char *tempNameMacr=NULL,*saveMacrName=NULL;
  char EalreadyInTabel[] ="symbol already in the tabel cant be save ";
  char EFailedAllocate[] ="Failed to allocate memory";
  
   for (i = 0; i < strlen(nameSymbol); i++) {
        if (!isspace(nameSymbol[i])) {
            length++;
            tempNameSymbol = (char *)realloc(saveMacrName, sizeof(char) * (length + 1));
            if (tempNameSymbol == NULL) {
                
                errorMessagesWithText(EFailedAllocate, strlen(EFailedAllocate), 'r');
                free(saveMacrName); 
                saveMacrName = NULL;
                return -1;
            }
            saveMacrName = tempNameSymbol;
            saveMacrName[length - 1] = nameSymbol[i];  
        }
    }
  if (saveMacrName == NULL ) {
        errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'r');
        free(CurrentLabel);
        return -1;
    }
  saveMacrName[length]='\0';
  free(saveMacrName);
}
