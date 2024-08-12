#include "header.h"

/*we found macro we need to put the next line in macro table*/
int foundMacro=0;
/*there are any macro? should we check for macro */
int thereAreMacros=0;
/*keep all the lines for the macro*/
char* storeLine=  NULL;
/*keep the name for the macro*/
char* currentMacrName=  NULL;
/*if there is a problem keep */
int problems=0;
/*list of lines*/
line *linesInMacro = NULL;
/*lines to read*/
line * readMe=NULL;

HashTable *currentTable;





/*
*function get line check where it suppose to go :
*thereAreMacros- if there are macro check for macro name
*if there are not  macro name:
*if there is macro , or already in macro
*return:-1 erorr: this line is not good 
*0 normal: this line doesnot have macro
*1 line in macro: dont write in the file
*2 found macro : write what in the line 
*/
int checkLineForMacr(char *copyLine){
  int isClean=0,foundName=0,checkForMcro=0,foundEndMacr=0,newSize=0 ;
  /*Line duplication*/
  char * cleanLine=NULL,*findNameLine=NULL,*checkLine=NULL;
  /*error messages*/
  char EFailedAllocate[] ="Failed to allocate memory";
  char ESemicolonNotRight[] ="Your Semicolon is not in the right place";
  char EUsingNameMacro[] ="You are using the name of macro incorrectly";
  cleanLine = (char*)malloc(sizeof(char) * (strlen(copyLine) + 1));
  if(cleanLine ==NULL){
        errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'y');
        return -1;
  }
  strcpy(cleanLine, copyLine);
  isClean=cleanBlankAndNoteLine(cleanLine);
  free(cleanLine);
  if(isClean){
    if(isClean==-1){
      errorMessagesWithText(ESemicolonNotRight,strlen(ESemicolonNotRight),'r');
    }
        return isClean;
  }
  
  if(thereAreMacros){
    findNameLine = (char*)malloc(sizeof(char) * (strlen(copyLine) + 1));
    if(findNameLine ==NULL){
        errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'y');
        return -1;
    }
    strcpy(findNameLine, copyLine);
    /*founName:we found =1 didnt=0 not legel=-1*/ 
     foundName=findMacrByName(findNameLine);
     printf("foundName %d",foundName);
     free(findNameLine);
     findNameLine=NULL;
     printf("check for macro name");
     if(foundName==1){
       /*  showLinesMacro(line);*/
        return 2;
      }
     if(foundName==-1){
        errorMessagesWithText(EUsingNameMacro,strlen(EUsingNameMacro),'r');
        return -1;
     }
  }

  checkLine = (char*)malloc(sizeof(char) * (strlen(copyLine) + 1));
  if(checkLine ==NULL){
        errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'y');
        return -1;
  }
  strcpy(checkLine, copyLine);
  if(!foundMacro &&!foundName){
      checkForMcro=findDefinitionMacro(checkLine);
      if(checkForMcro == -1){
       foundMacro=1;
       problems=1;
       free(checkLine);
       return -1;
      }
     foundMacro=checkForMcro;
  }
  else{
      foundEndMacr=findEndMacro(checkLine);
      printf("foundEndMacr = %d",foundEndMacr);
       if(foundEndMacr==-1){
          free(checkLine);
          foundMacro=0;
          return -1;
       }
       foundMacro = foundEndMacr;
       if(!foundEndMacr){
         free(checkLine);
         return 1;
       }
       if(foundMacro==1){
        newSize = strlen(checkLine) + 1;
        storeLine = (char *)malloc(newSize);
        if(storeLine==NULL){
           errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'y');
           free(checkLine);
           return -1;
        }
        strcpy(storeLine, checkLine);
        appendLine(&linesInMacro, storeLine);
        free(storeLine);
    }
  }
  if(checkForMcro==-1||foundEndMacr==-1){
    if(checkForMcro==-1){
      problems=1;
    }
    if(foundEndMacr==-1){
        foundMacro=0;
    }
    free(checkLine);
    return -1;
  } 
  
free(checkLine);
return foundMacro;
}
/*
*function to clean from blank Line and note lines
*return 0 line is not blnk or note
*return 1 if its blank or notes 
*return -1 if there any ; just like that
*/
int cleanBlankAndNoteLine(char *clearLine){ 
  int blankOrNote=0;
  char *token,*point;
  if(clearLine== NULL){
    return blankOrNote=1;
  }
  if(*clearLine=='\n'){
    return blankOrNote=1;
  }
   if(*clearLine==';'){
    return blankOrNote=1;
  }
  point=strchr(clearLine, ';');
  token=strtok(clearLine," ");
   if(*token=='\n'){
    return blankOrNote=1;
  }
   if(*token==';'){
    return blankOrNote=1;
  }
  if(point!=NULL &&token!=point){
    return blankOrNote=-1;
  }
return blankOrNote;
}

/**
 * Function get Line check for macro,or defition
 * return: 1: if we found macro, 0: if there arent,
 *  -1:if  we found macro but he is wrong and we need to stop
 */
int findDefinitionMacro(char *checkLine ){
  int i, length=0 , nameMacrOk=0;
  char *pos;
  char word[]="macr";
  /*error messages*/
  char EBCleanMacr[] ="Before macr there should not be any thing ";

  pos = strstr(checkLine, word);
  if(pos==NULL){ 
     return 0;
  }
  if(pos != checkLine){
    if(!isspace(*(pos-1))){
      return 0;
    }
    else{
       if(!isspace(*(pos+strlen(word)))){
         return 0;
       }
       else
       {
          length=pos-checkLine;
          for(i=0;i<length;i++){
          if(!isspace(*(checkLine+i))){
               errorMessagesWithText(EBCleanMacr,strlen(EBCleanMacr),'r');
               return -1;
             }
           }
        }
      }
    }
    if(!isspace(*(pos+strlen(word)))){
         return 0;
    }
     
  
  nameMacrOk= checkNameOfMcro(pos+strlen(word));
  
return nameMacrOk;

}

/**
 * Function get the rest of Line check for macro name
 * return: 1: if the name is alright  and it in the table, 
 *  -1:if we found name but is wrong and we need to stop
 */
int checkNameOfMcro(char *posMacr){
 int i,length,result=0,isOpcode=0,alreadyInTable=0;
 char * token,*nameMacr=NULL ,*pos;
 char notInTheSE[]=",.:+}{\\|?!@#$%^&*()-='\"";
 /*error messages*/
  char EmacroNameNull[] ="your macro name is null";
  char EFailedAllocate[] ="Failed to allocate memory";
  char EtextAfterName[] ="you put  text after you macro name";
  char EmacrSaveWord[] ="Your macr name is a saved word ";
  char EmacrAlreadySave[] ="Your macr name is already in the table";
  char EmacrLetterFirst[] ="macr name must have letter first";
  char EmacrNoPunctuation[] ="macr name doesnt containing punctuation";

   token=strtok(posMacr," ");
    if(token == NULL || *token == ' ' || *token == '\n'|| *token == '\0'){
       errorMessagesWithText(EmacroNameNull,strlen(EmacroNameNull),'r');
      return -1;
    }
    nameMacr = (char*)malloc(sizeof(char) * (strlen(token) + 1));
    if(nameMacr ==NULL){
        errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'y');
        return -1;
    }
    result=isspace(*(token+strlen(token)-1));
    if(result){
      length=strlen(token)-1;
      nameMacr=(char*)malloc(sizeof(char)*(strlen(token) ));
    }else{
    length=strlen(token);
    nameMacr=(char*)malloc(sizeof(char)*(strlen(token) + 1));
    }
    strncpy(nameMacr,token,length);
    token=strtok(NULL," ");
    if(token != NULL && *token != ' ' && *token != '\n'&& *token != '\0'){
       errorMessagesWithText(EtextAfterName,strlen(EtextAfterName),'r');
       free(nameMacr);
      return -1;
    }
   /*check for letter first */
   if(!isalpha(nameMacr[0])){
       errorMessagesWithText(EmacrLetterFirst,strlen(EmacrLetterFirst),'r');
       free(nameMacr);
       return -1;
   }
    /*check for punctuation */
    for(i=0;i<strlen(notInTheSE);i++){
      pos=strchr(nameMacr, notInTheSE[i]);
      if(pos!= NULL){
         errorMessagesWithText(EmacrNoPunctuation,strlen(EmacrNoPunctuation),'r');
        free(nameMacr);
        return -1;
      }
    }
  isOpcode=lookForOpcode(nameMacr);
  printf("isOpcode %d",isOpcode);
  if(isOpcode!= -1){
     errorMessagesWithText(EmacrSaveWord,strlen(EmacrSaveWord),'r');
     free(nameMacr);
     return -1;
  }
  alreadyInTable=searchNameOfMacr(currentTable, nameMacr);
  if(alreadyInTable ){
     errorMessagesWithText(EmacrAlreadySave,strlen(EmacrAlreadySave),'r');
      free(nameMacr);
       return -1;
    }

   if(isOpcode==-1&&!alreadyInTable){
       printf("*in*");
       if(currentMacrName!=NULL){
           free(currentMacrName);
           currentMacrName=NULL;
        }
        currentMacrName=(char*)malloc(sizeof(char)*(strlen(nameMacr)));
        strcpy(currentMacrName,nameMacr);
        free(nameMacr);
        return 1;
    }
  free(nameMacr);
  return 0;
}

/**
 * Function get Line check for EndMacro
 * return: 0: if we found EndMacro, 1: if there arent,
 *  -1:if  we found EndMacro but he is wrong and we need to stop
 */
int findEndMacro(char *checkLine ){
   int i;
  char *pos=NULL;
  char word[]="endmacr";
  /*error messages*/
  char EBACleanMacr[] ="Before endmacr or After there should not be any thing ";
  pos = strstr(checkLine, word);
  if(pos==NULL){
    return 1;
  }
  for ( i = 0; i < strlen(checkLine); i++)
  {
   if(pos==(checkLine+i)){
     i+=strlen(word);
   }
   if(!isspace(*(checkLine+i))){
      errorMessagesWithText(EBACleanMacr,strlen(EBACleanMacr),'r');
      return -1;
   }
  }
  
  if(!problems&&foundMacro!=-1){
    /*store macro*/
      if(currentMacrName!=NULL&&storeLine!=NULL){
          addNameOfMacr(currentTable, currentMacrName, linesInMacro);
          printf("end");
          thereAreMacros++;
          linesInMacro=NULL;
      }
  }
 return 0;
}
/*
*function tring to find macr 
*return:0- didnt find any macro
*1: found macro
*-1 : have a problem with macro
*/
int findMacrByName(char *findNameLine){
   char *token,*macrName,*point,*isItLabel;
   int foundInList,result=0,lenght=0;
     /*error messages*/
   char EFailed[] ="Failed: something not right ";
   char EFailedAllocate[] ="Failed to allocate memory";
   char EmacrLabel[] ="you confused macr with label";
   token=strtok(findNameLine," ");
   if(token == NULL){
      errorMessagesWithText(EFailed,strlen(EFailed),'r');
      return 0;
    }
    result=isspace(*(token+strlen(token)-1));
    if(result){
      lenght=strlen(token)-1;
      macrName=(char*)malloc(sizeof(char)*(strlen(token) ));
    }else{
    lenght=strlen(token);
    macrName=(char*)malloc(sizeof(char)*(strlen(token) + 1));
    }
    if(macrName==NULL){
      errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'y');
      return -1 ;
    }
    strncpy(macrName,token,lenght);
    point=strchr(macrName, ':');
    if(point!=NULL){
      isItLabel=(char*)malloc(sizeof(char)*(strlen(macrName)-1));
      if(isItLabel==NULL){
         errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'y');
         return -1 ;
      }
      strncpy(isItLabel,macrName,lenght-1);
      foundInList= searchNameOfMacr(currentTable, isItLabel);
      free(isItLabel);
      if(foundInList){
      errorMessagesWithText(EmacrLabel,strlen(EmacrLabel),'y');
      free(macrName);
      return -1;
      }
  }
  token=strtok(NULL," ");
  if(token == NULL || *(token) == ' ' || *(token) == '\n'|| *(token)== '\0'){
      foundInList= searchNameOfMacr(currentTable, macrName);
      if(foundInList){
        free(macrName); 
          return 1;
      }
  }

free(macrName);
return 0;
}
/**/
line * showLinesMacro(char *line){
  int i, lenght=0,result;
  char *token, *macrName;
  token=strtok(line," ");
   if(token == NULL){
      printf("macro name is null problem");
      return NULL;
    }
    result=isspace(*(token+strlen(token)-1));
    if(result){
      lenght=strlen(token)-1;
      printf("lenght=%d",lenght);
      macrName=(char*)malloc(sizeof(char)*(strlen(token)));
    }else{
    lenght=strlen(token);
     printf("lenght=%d",lenght);
     macrName=(char*)malloc(sizeof(char)*(strlen(token)+1));
    }
   
   strncpy(macrName,token,lenght);
   macrName[lenght]='\0';
   readMe=NULL;
   for ( i = 0; i < strlen(macrName); i++)
   {
     printf("c=%c ",*(macrName+i));
   }
   readMe = searchNameOfMacrReturnLine(currentTable,macrName);
   free(macrName);
   return readMe;
}

/*
*function that start the table
*/
void initialize(){
   currentTable = createHashTable();
}
/*
*function that free the table 
*/
void tableFree(){
  freeHashTable(currentTable);
  currentTable=NULL;
}