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


line * showLinesMacro(char *line){
  int i,lenght=0,result;
  char *token, *macrName,*readMe = NULL;
  token=strtok(line," ");
   if(token == NULL){
      printf("macro name is null problem");
      return NULL;
    }
    result=isspace(*(token+strlen(token)-1));
    if(result){
      lenght=strlen(token)-1;
      macrName=(char*)malloc(sizeof(char)*(strlen(token) ));
    }else{
    lenght=strlen(token);
    macrName=(char*)malloc(sizeof(char)*(strlen(token) + 1));
    }
   strncpy(macrName,token,lenght);
   readMe= searchNameOfMacrReturnLine(currentTable,macrName);
   free(macrName);
   return readMe;
}

/*
*function to clean storeLine and  currentMacrName
*/
void clearGlobals() {
    if (storeLine != NULL) {
        free(storeLine);
        storeLine = NULL;  
    }
    if (currentMacrName != NULL) {
        free(currentMacrName);
        currentMacrName = NULL;  
    }
}
/*
*function to clean from blank Line and note lines
*return 0 line is not blnk or note
* return1 if its blank or notes 
*/
int cleanBlankAndNoteLine(char *line){ 
  int blankOrNote=0;
  char *token;
  if(line== NULL){
    return blankOrNote=1;
  }
  if(*line=='\n'){
    return blankOrNote=1;
  }
   if(*line==';'){
    return blankOrNote=1;
  }
  token=strtok(line," ");
   if(*token=='\n'){
    return blankOrNote=1;
  }
   if(*token==';'){
    return blankOrNote=1;
  }
return blankOrNote;
}

/*
*function tring to find macr 
*return:0- didnt find any macro
*1: found macro
*-1 : have a problem with macro
*/
int findMacrByName(char *nameMacr){
   char *token,*macrName,*point,*isItLabel;
   int foundInList,result=0,tokenLength=0,lenght=0;
  token=strtok(nameMacr," ");
  if(token == NULL){
     printf("macro name is null problem");
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
    printf("error in realloc");
    return 0;
  }
  strncpy(macrName,token,lenght);
  point=strchr(macrName, ':');
  if(point!=NULL){
      isItLabel=(char*)malloc(sizeof(char)*(strlen(macrName)));
      strncpy(isItLabel,macrName,lenght-1);
     foundInList= searchNameOfMacr(currentTable, isItLabel);
      free(isItLabel);
      if(foundInList){
      printf("\nyou confused macr with label\n");
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

/**
 * Function get the rest of Line check for macro name
 * return: 1: if the name is alright  and it in the table, 
 *  -1:if we found name but is wrong and we need to stop
 */
int checkNameOfMcro(char *nameMacr){
    char *token,*pos,*point;
    char *macrName;
    char notInTheSE[]=",._:";
    int i,isOpcode=-1,nameOk=-1,result=0,lenght=0,alreadyInTable=0;;
    token=strtok(nameMacr," ");
    if(token == NULL || *token == ' ' || *token == '\n'|| *token == '\0'){
      printf("macro name is null problem");
      return -1;
    }
    result=isspace(*(token+strlen(token)-1));
    if(result){
      lenght=strlen(token)-1;
      macrName=(char*)malloc(sizeof(char)*(strlen(token) ));
    }else{
    lenght=strlen(token);
    macrName=(char*)malloc(sizeof(char)*(strlen(token) + 1));
    }
    if (macrName == NULL) {
            printf("Failed to allocate memory");
            return -1;
        }
    strncpy(macrName,token,lenght);
    token=strtok(NULL," ");
     if(token != NULL && *token != ' ' && *token != '\n'&& *token != '\0'){
      printf("token= %c ",*token);
      printf("macro to many arguments");
      free(macrName);
      return -1;
    }
    /*check for punctuation */
    isOpcode=lookSaveWords(macrName);
    alreadyInTable=searchNameOfMacr(currentTable, macrName);
    if(isOpcode !=-1){
      printf(" this name is a save word");
      free(macrName);
       return -1;
    }
      if(alreadyInTable ){
      printf(" this name is a already in the table ");
      free(macrName);
       return -1;
    }
    for(i=0;i<strlen(notInTheSE);i++){
      pos=strchr(macrName, notInTheSE[i]);
      if(pos== macrName){
        printf("no punctuationin the beginning");
        free(macrName);
        return -1;
      }
      if(pos== (macrName+strlen(macrName))){
        printf("no punctuationin the ending");
        free(macrName);
        return -1;
      }
    } 
    if(isOpcode==-1&&!alreadyInTable){
        currentMacrName=(char*)malloc(sizeof(char)*(strlen(macrName)));
        strcpy(currentMacrName,macrName);
        free(macrName);
        return 1;
    }

    free(macrName);
    return -1;
}

/**
 * Function get Line check for macro,or defition
 * return: 1: if we found macro, 0: if there arent,
 *  -1:if  we found macro but he is wrong and we need to stop
 */
int findDefinitionMacro(char *line ){
    char *token,*pos,*point;
    char word[]="macr";
    int macroName=0,i=0;
     /* Find first occurrence of word in str */
        pos = strstr(line, word);
        if (pos != NULL)
        {
           foundMacro=1;
           token=strtok(line," ");
           point=pos+strlen(word);
           if((pos+strlen(word))!=NULL){
           if(*point!=' '&&*point!='\0'&&*point!='\t'&& *point!='\n'){
               foundMacro=0;
           }
           
           }
           if((pos-1)!=NULL&&line!=pos)
              if(pos[-1]!=' '&&pos[-1]!='\0'&&pos[-1]!='\t'){
               foundMacro=0;
              }
            if(token !=pos&&foundMacro){  
             foundMacro=-1;
               return -1;
            } 
             
             if(point!=NULL && *point!='\n'&& foundMacro==1 ){
               macroName= checkNameOfMcro(point+1);
             }else
             {
               if(foundMacro==1){
               printf("macro name is null ");
               return -1;
               }
             }
             
        }
      if(macroName!=1&& foundMacro==1){
        printf("the name is not good");
        return -1;
        /*move found macro*/
      }
return foundMacro;
}
/**
 * Function get Line check for EndMacro
 * return: 0: if we found EndMacro, 1: if there arent,
 *  -1:if  we found EndMacro but he is wrong and we need to stop
 */
int findEndMacro(char *line ){
 char *token,*pos,*point;
    char word[]="endmacr";
    int isEndOK=0;
     /* Find first occurrence of word in str */
        pos = strstr(line, word);
         foundMacro=1;
        if (pos != NULL)
        {
           token=strtok(line," ");
           point=pos+strlen(word);
           if((pos+strlen(word))!=NULL){
               if(*point!=' '&&*point!='\0'&&*point!='\t'&& *point!='\n'){
                 isEndOK=1;
              }
           }
           
           if((pos-1)!=NULL&&line!=pos)
              if(pos[-1]!=' '&&pos[-1]!='\0'&&pos[-1]!='\t'){
               isEndOK=1;
              }
            if(token !=pos&&foundMacro){
               foundMacro=-1;
               return -1;
            } 
             if((point == NULL || *(point+1) == ' ' || *(point+1) == '\n'|| *(point+1)== '\0')&& isEndOK!=1 ){
                 foundMacro=0;
                  token=strtok(NULL," ");
                  
                  if(token !=NULL&&( *token != ' ' && *token != '\n'&& *token != '\0')){
                     foundMacro=-1;
                      printf(" end token= %c ",*token);
                     printf("to many argouments");
                  }
                  if(!problems&&foundMacro!=-1){
                    /*store macro*/
                    if(currentMacrName!=NULL&&storeLine!=NULL){
                    addNameOfMacr(currentTable, currentMacrName, linesInMacro);
                    printf("end");
                    thereAreMacros++;
                    linesInMacro=NULL;
                    }
                    else{
                      clearGlobals();
                    }
                  }else{
                   clearGlobals();
                  }
                  free(storeLine);
                  problems=0;
             }else{
                    if(!isEndOK&& point !=NULL &&( *(point+1) != ' ' && *(point+1) != '\n'&& *(point+1) != '\0')){
                      foundMacro=-1;
                      printf("to many argouments");
                    }
             }
        }
         
return foundMacro;
}
int lookSaveWords(char *input)
{
    int returnOperation = -1;
    int flag = 0;
   
    if (strstr(input, "mov") != NULL&&(strlen(input)==strlen("cmp")))
    {
        flag += 1;
        returnOperation= 0;
    }
    if (strstr(input, "cmp") != NULL&&(strlen(input)==strlen("cmp")))
    {
        flag += 1;
        returnOperation= 1;
    }
    if (strstr(input, "add") != NULL&&(strlen(input)==strlen("add")))
    {
        flag += 1;
        returnOperation= 2;
    }
    if (strstr(input, "sub") != NULL &&(strlen(input)==strlen("sub")))
    {
        flag += 1;
        returnOperation= 3;
    }
    if (strstr(input, "lea") != NULL&&(strlen(input)==strlen("lea")))
    {
        flag += 1;
        returnOperation= 4;
    }
    if (strstr(input, "clr") != NULL&&(strlen(input)==strlen("clr")))
    {
        flag += 1;
        returnOperation= 5;
    }
    if (strstr(input, "not") != NULL&&(strlen(input)==strlen("not")))
    {
        flag += 1;
        returnOperation= 6;
    }
    if (strstr(input, "inc") != NULL&&(strlen(input)==strlen("inc")))
    {
        flag += 1;
        returnOperation= 7;
    }
    if (strstr(input, "dec") != NULL&&(strlen(input)==strlen("dec")))
    {
        flag += 1;
        returnOperation= 8;
    }
    if (strstr(input, "jmp") != NULL&&(strlen(input)==strlen("jmp")))
    {
        flag += 1;
        returnOperation= 9;
    }
    if (strstr(input, "bne") != NULL&&(strlen(input)==strlen("bne")))
    {
        flag += 1;
        returnOperation= 10;
    }
    if (strstr(input, "red") != NULL&&(strlen(input)==strlen("red")))
    {
        flag += 1;
        returnOperation= 11;
    }
    if (strstr(input, "prn") != NULL&&(strlen(input)==strlen("prn")))
    {
        flag += 1;
        returnOperation= 12;
    }
    if (strstr(input, "jsr") != NULL&&(strlen(input)==strlen("jsr")))
    {
        flag += 1;
        returnOperation= 13;
    }
     if (strstr(input, "rts") != NULL&&(strlen(input)==strlen("rts")))
    {
        flag += 1;
        returnOperation= 14;
    }
    if (strstr(input, "stop") != NULL&&(strlen(input)==strlen("stop")))
    {
        flag += 1;
        returnOperation= 15;
    }
    if (strstr(input, "string") != NULL&&(strlen(input)==strlen("string")))
    {
        flag += 1;
        returnOperation= 16;
    }
    if (strstr(input, "data") != NULL&&(strlen(input)==strlen("data")))
    {
        flag += 1;
        returnOperation= 17;
    }
    if (strstr(input, "entry") != NULL &&(strlen(input)==strlen("entry")))
    {
        flag += 1;
        returnOperation= 18;
    }
    if (strstr(input, "extern") != NULL&&(strlen(input)==strlen("extern")))
    {
        flag += 1;
        returnOperation= 19;
    }
    if (strstr(input, "macr") != NULL&&(strlen(input)==strlen("macr")))
    {
        flag += 1;
        returnOperation= 20;
    }
    if ( flag > 1)
    {
        returnOperation= -1;
    }
    return returnOperation;
}
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
int checkLineForMacr(char *line){
  int founName=0,foundMacr=0,foundEndMacr=0,i,newSize=0;
  char *temp=line;
  char *tempC=line;
  char *clearLine=line;
    temp = (char*)malloc(sizeof(char) * (strlen(line) + 1));
    clearLine = (char*)malloc(sizeof(char) * (strlen(line) + 1));
    tempC = (char*)malloc(sizeof(char) * (strlen(line) + 1));
    if (temp == NULL||clearLine ==NULL||tempC==NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }
    strcpy(temp, line);
    strcpy(clearLine, line);
    strcpy(tempC, line);
    /* blank lines or note*/
    if(cleanBlankAndNoteLine(clearLine))
      {
        /* freeTempLine(temp,clearLine,tempC);*/
        return 1;
      }
      /**/
    if(thereAreMacros&&!foundMacro){
    /*founName:we found =1 didnt=0 not legel=-1*/
     founName=findMacrByName(line);
     }

  if(founName==1){
    showLinesMacro(line);
     /* freeTempLine(temp,clearLine,tempC);*/
    return 2;
  }
   if(founName==-1){
      /* freeTempLine(temp,clearLine,tempC);*/
      return -1;
  }
     if(!foundMacro &&!founName){
      foundMacr=findDefinitionMacro(temp);
     
      }else{
      foundEndMacr=findEndMacro(temp);
       if(!foundEndMacr){
         /* freeTempLine(temp,clearLine,tempC);*/
        return 1;
       }
  
     if(foundMacro==1){
       newSize = strlen(tempC) + 1;
       storeLine = (char *)malloc(newSize);
       if(storeLine==NULL){
          printf("malloc didnt work");
           /* freeTempLine(temp,clearLine,tempC);*/
         return -1;
       }
       strcpy(storeLine, tempC);
      appendLine(&linesInMacro, storeLine);
     storeLine[strlen(storeLine)]='\n';
    }
  }
  
  if(foundMacr==-1||foundEndMacr==-1){
    if(foundMacr==-1){
      problems=1;
      foundMacro=1;
    }
    if(foundEndMacr==-1){
        foundMacro=0;
    }
    /* freeTempLine(temp,clearLine,tempC);*/
    return -1;
  } 
  
    /*freeTempLine(temp,clearLine,tempC);*/
     
        
  return foundMacro;
}
void reboot(){
   currentTable = createHashTable();
}
void tableFree(){
  freeHashTable(currentTable);
  clearGlobals();
  if(readMe!=NULL){
    clearLinesInMacro(&readMe);
    readMe=NULL;
  }
  currentTable=NULL;
}
void freeTempLine(char *first,char *second,char *tree){

if(first!=NULL){
printf("f ");
free(first);
first=NULL;
}
if(second!=NULL ){
printf("s ");
free(second);
second = NULL;
}
if(tree!=NULL){
printf("t ");
free(tree);
tree = NULL;
}
}
