#include "firstPassHeader.h"

/*the current label for use */
char *CurrentLabel=NULL;


/*
*function check if there is puctuation
*there is: -1
 *no : 0
 * */
int therePunctuation(char *nameSymbol){
    int i;
    char *pos;
    char Punctuation[]=":;></\\+=!@#$^&*()_-}{][,~`|'?\" %.";
     for(i=0;i<strlen(Punctuation);i++){
       pos=strchr(nameSymbol, Punctuation[i]);
       if(pos!= NULL){
          return -1;
        }
     }
     return 0;
}
/*
function gets the name of symbol and save it 
sucsses :0
not sucsses:-1
*/
int saveSymbolCurrentLabel(char *nameSymbol){
  int i ,length=0,inTabel=1;
  char *tempNameSymbol=NULL;
  char EalreadyInTabel[] ="symbol already in the tabel cant be save ";
  char EFailedAllocate[] ="Failed to allocate memory";
   for (i = 0; i < strlen(nameSymbol); i++) {
        if (!isspace(nameSymbol[i])) {
            length++;
            
            tempNameSymbol = (char *)realloc(CurrentLabel, sizeof(char) * (length + 1));
            if (tempNameSymbol == NULL) {
                
                errorMessagesWithText(EFailedAllocate, strlen(EFailedAllocate), 'r');
                free(CurrentLabel); 
                CurrentLabel = NULL;
                return -1;
            }
            CurrentLabel = tempNameSymbol;
            CurrentLabel[length - 1] = nameSymbol[i];  
        }
    }
  printf("lenght %d",length);
  if (CurrentLabel == NULL ) {
        errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'r');
        free(CurrentLabel);
        return -1;
    }
  CurrentLabel[length+1]='\0';
  /*check in table already*/
  inTabel= ISsearchSymbol(mySymbolTabel, CurrentLabel);
     if(inTabel == 1){
        errorMessagesWithText(EalreadyInTabel,strlen(EalreadyInTabel),'r');
        free(tempNameSymbol);
        if(tempNameSymbol!=CurrentLabel){
        free(CurrentLabel);
        }
        CurrentLabel=NULL;
        return -1;
     }
     

     if(tempNameSymbol!=CurrentLabel){
        free(CurrentLabel);
        }
    printf("\n store \n");
    return 0;

}

/*
check the name of symbol if it correct 
retun :1
if wrong:-1
*/
int checkSymbol(char *nameSymbol,int saveSymbol){
    int thereispunctuation=0, isItOpration=-1 ,save=-1;
    /*error messages*/
    char EstartWithLetter[] ="symbol should start with letter ";
    char Epunctuation[] ="symbol should not have punctuation";
    char Eopration[] ="symbol should not have the same name as opration";
    

     thereispunctuation=therePunctuation(nameSymbol);
     if(thereispunctuation==-1){
           errorMessagesWithText(Epunctuation,strlen(Epunctuation),'r');
          return -1;
     }
      if (isalpha(*nameSymbol)) {
        printf("%c is a letter.\n", *nameSymbol);
    } else {
        printf("%c is not a letter.\n", *nameSymbol);
        errorMessagesWithText(EstartWithLetter,strlen(EstartWithLetter),'r');
        return -1;
    }
     /*check if it add ,macr and more (Opration)*/
    isItOpration=lookForOpcode(nameSymbol);
    if(isItOpration!=-1){
        errorMessagesWithText(Eopration,strlen(Eopration),'r');
        return -1;
    }
    if(saveSymbol){
     save= saveSymbolCurrentLabel(nameSymbol);
     if(save==-1){
       return -1;
     }
    }

    return 1;
}

/*
function that check if there :(colon) 
if there is it check the name of the symbol 
if everthing is good return: where to star
else:NULL
*/
char *thereIsSymbol(char *line){
    char *tempLine,*findColon,*token,*returnSymbol = NULL,*nameSymbol;
    int lengthName=0,okSymbol=0;
    /*error messages*/
    char EFailedAllocate[] ="Failed to allocate memory";
    char EsymbolNameNumber[] ="symbol should be 0-31 characters";
    char ENullSymbol[] ="null symbol";
    char EplaceOfColon[] ="your colon is not in the right place";
    tempLine = (char*)malloc(sizeof(char) * (strlen(line)+1));

     if (tempLine == NULL ) {
         errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'r');
        return returnSymbol;
    }
    strcpy(tempLine, line);
    printf(" copy ");
    token=strtok(tempLine," ");
    printf("%c \n",*token);
    findColon=strchr(token, ':');
     
     printf("p=%p \n",findColon);
     if(findColon==NULL){
         printf("null \n");
        findColon=strchr(line, ':');
        if(findColon==NULL){
        free(tempLine);
        return line;
        }
        else{
          free(tempLine);
          errorMessagesWithText(EplaceOfColon,strlen(EplaceOfColon),'r');
          return NULL;
        }
     }
    lengthName=findColon-token;
    printf("lengthName=%d",lengthName);
    if(lengthName<32 && lengthName>0){
      nameSymbol = (char*)malloc(sizeof(char) * (lengthName));
      if (nameSymbol == NULL ) {
         errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'r');
         free(tempLine);
        return NULL;
      }
      strncpy(nameSymbol,token,lengthName);
    }else
    {
         errorMessagesWithText(EsymbolNameNumber,strlen(EsymbolNameNumber),'r'); 
         free(tempLine);
         return returnSymbol; 
    }
    
    
    okSymbol=checkSymbol(nameSymbol,1);
    if(okSymbol==1){
        if(*(findColon+1)=='\0'){
        returnSymbol=line+(findColon-tempLine)+2;
        }else{  
        returnSymbol=line+(findColon-tempLine)+1;
          if(*(returnSymbol+1)==' '||*returnSymbol=='\n'){
             errorMessagesWithText(ENullSymbol,strlen(ENullSymbol),'r'); 
             returnSymbol=NULL;
          }
        }
    }else{
        returnSymbol=NULL;
    }
    free(nameSymbol);
    free(tempLine);
    printf("returnSymbol=%p ",returnSymbol);
    return returnSymbol;
}