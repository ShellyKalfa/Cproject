#include "header.h"

/*we found macro we need to put the next line in macro table*/
int foundMacro=0;
/*there are any macro? should we check for macro */
int thereAreMacros=0;
/*keep all the lines for the macro*/
char* storeLine;
/*keep the name for the macro*/
char* currentMacrName;
/*if there is a problem keep */
int problems=0;

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
*
*
*/

int findMacrByName(char *nameMacr){
  char *token,*macrName,*point;
 
  printf("the nameMacr %p , c= %c\n",nameMacr,*nameMacr);
  token=strtok(nameMacr," ");
  printf("the nameMacr %p , c= %c\n",token,*token);
  if(token == NULL){
     printf("macro name is null problem");
      return 0;
  }
  macrName=(char*)malloc(sizeof(char)*(strlen(token) + 1));
  if(macrName==NULL){
    printf("error in realloc");
    return 0;
  }
  strcpy(macrName,token);
  point=strchr(macrName, ":");
  if(point!=NULL){
    /* and in check in list*/
      printf("\nyou confused macr with label\n");
      return -1;
  }
  
  token=strtok(NULL," ");
  if(token == NULL || *(token) == ' ' || *(token) == '\n'|| *(token)== '\0'){
      printf("\ncheck macro\n");
    printf("check + %c ",*macrName);
    /*check in list*/
  }
free(macrName);
return 2;
}


/**
 * Function get the rest of Line check for macro name
 * return: 1: if the name is alright  and it in the table, 
 *  -1:if we found name but is wrong and we need to stop
 */
int checkNameOfMcro(char *nameMacr){
    char *token,*pos,*point;
    char *macrName;
    char notInTheSE[]=",._:;";
    int i,isOpcode=-1,nameOk=-1;
    token=strtok(nameMacr," ");
    printf("the nameMacr %p , c= %c\n",nameMacr,*nameMacr);
    
    if(token == NULL || *token == ' ' || *token == '\n'|| *token == '\0'){
      printf("macro name is null problem");
      return -1;
    }
    macrName=(char*)malloc(sizeof(char)*(strlen(token) + 1));
    strcpy(macrName,token);
    token=strtok(NULL," ");
     if(token != NULL && *token != ' ' && *token != '\n'&& *token != '\0'){
      printf("macro to many arguments");
      free(macrName);
      return -1;
    }
   /*for me */
    for (i = 0; i < strlen(macrName); i++)
   {
    printf("%c", *(macrName+i));
   }
    /*check for punctuation */
    isOpcode=lookSaveWords(macrName);
    printf("opcode: %d",isOpcode);
    if(isOpcode !=-1){
      printf(" this name is a save word");
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
    if(isOpcode==-1){
      currentMacrName=(char*)malloc(sizeof(char)*(strlen(macrName)));
        strcpy(currentMacrName,macrName);
        /* everthig is good */
        /*delete lines and put new name */
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
    int macroName=0;
     /* Find first occurrence of word in str */
        pos = strstr(line, word);
         printf("in definition : %p",pos);
        if (pos != NULL)
        {
           foundMacro=1;
           token=strtok(line," ");
          
           printf("\ntoken=%p,token[0]=%c pos=%p,pos[0]=%c\n ",token,token[0],pos,pos[0]);
           point=pos+strlen(word);
           if((pos+strlen(word))!=NULL){
           if(*point!=' '&&*point!='\0'&&*point!='\t'&& *point!='\n'){
               printf("pos[1]=%c ",*point);
               foundMacro=0;
           }
           
           }
           if((pos-1)!=NULL&&line!=pos)
              if(pos[-1]!=' '&&pos[-1]!='\0'&&pos[-1]!='\t'){
                  printf("pos[-1]=%c ",pos[-1]);
               foundMacro=0;
              }
            if(token !=pos&&foundMacro){  
             foundMacro=-1;
               return -1;
            } 
             if(point!=NULL && *point!='\n'&& foundMacro==1 ){
                 printf("check");
               printf(" \n point %p",point+1);
               macroName= checkNameOfMcro(point+1);
             }else
             {
               printf("macro name is null ");
               return -1;
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
         printf("in end ");
        if (pos != NULL)
        {
        
           token=strtok(line," ");
          
           printf("\ntoken=%p,token[0]=%c pos=%p,pos[0]=%c\n ",token,token[0],pos,pos[0]);
           point=pos+strlen(word);;
           if((pos+strlen(word))!=NULL){
           if(*point!=' '&&*point!='\0'&&*point!='\t'&& *point!='\n'){
               printf("pos[1]=%c ",*point);
               isEndOK=1;
           }
           
           }
           
           if((pos-1)!=NULL&&line!=pos)
              if(pos[-1]!=' '&&pos[-1]!='\0'&&pos[-1]!='\t'){
                  printf("pos[-1]=%c ",pos[-1]);
               isEndOK=1;
              }
            if(token !=pos&&foundMacro){
               printf("check@");  
               foundMacro=-1;
               return -1;
            } 
            printf("isEnd= %d",isEndOK);
             if((point == NULL || *(point+1) == ' ' || *(point+1) == '\n'|| *(point+1)== '\0')&& isEndOK!=1 ){
                 printf("check good");
                 foundMacro=0;
                  token=strtok(NULL," ");
                  
                  if(token !=NULL&&( *token != ' ' && *token != '\n'&& *token != '\0')){
                    printf("%c",*token);
                     foundMacro=-1;
                     printf("to many argouments");
                  }
                  if(!problems&&foundMacro!=-1){
                    /*store macro*/
                    printf("\nstore macro\n");
                    thereAreMacros++;
                  }else{
                   clearGlobals();
                  }
                
                  /*store macro*/
                  free(storeLine);
                  problems=0;
             }else{

             }
        }
         
return foundMacro;
}
int lookSaveWords(char *input)
{
    int returnOperation = -1;
    int flag = 0;
   
    if (strstr(input, "mov") != NULL)
    {
        flag += 1;
        returnOperation= 0;
    }
    if (strstr(input, "cmp") != NULL)
    {
        flag += 1;
        returnOperation= 1;
    }
    if (strstr(input, "add") != NULL)
    {
        flag += 1;
        returnOperation= 2;
    }
    if (strstr(input, "sub") != NULL)
    {
        flag += 1;
        returnOperation= 3;
    }
    if (strstr(input, "lea") != NULL)
    {
        flag += 1;
        returnOperation= 4;
    }
    if (strstr(input, "clr") != NULL)
    {
        flag += 1;
        returnOperation= 5;
    }
    if (strstr(input, "not") != NULL)
    {
        flag += 1;
        returnOperation= 6;
    }
    if (strstr(input, "inc") != NULL)
    {
        flag += 1;
        returnOperation= 7;
    }
    if (strstr(input, "dec") != NULL)
    {
        flag += 1;
        returnOperation= 8;
    }
    if (strstr(input, "jmp") != NULL)
    {
        flag += 1;
        returnOperation= 9;
    }
    if (strstr(input, "bne") != NULL)
    {
        flag += 1;
        returnOperation= 10;
    }
    if (strstr(input, "red") != NULL)
    {
        flag += 1;
        returnOperation= 11;
    }if (strstr(input, "prn") != NULL)
    {
        flag += 1;
        returnOperation= 12;
    }
    if (strstr(input, "jsr") != NULL)
    {
        flag += 1;
        returnOperation= 13;
    }
     if (strstr(input, "rts") != NULL)
    {
        flag += 1;
        returnOperation= 14;
    }
    if (strstr(input, "stop") != NULL)
    {
        flag += 1;
        returnOperation= 15;
    }
    if (strstr(input, "string") != NULL)
    {
        flag += 1;
        returnOperation= 16;
    }
    if (strstr(input, "data") != NULL)
    {
        flag += 1;
        returnOperation= 17;
    }
    if (strstr(input, "entry") != NULL)
    {
        flag += 1;
        returnOperation= 18;
    }
    if (strstr(input, "extern") != NULL)
    {
        flag += 1;
        returnOperation= 19;
    }
    if (strstr(input, "macr") != NULL)
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
  int founName=0,foundMacr=0,foundEndMacr=0,i;
  char *temp=line;
  char *tempC=line;
    temp = (char*)malloc(sizeof(char) * (strlen(line) + 1));
    if (temp == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }
    strcat(temp, line);
    if(thereAreMacros&&!foundMacro){
    /*founName:we found =1 didnt=0 not legel=-1*/
     founName=findMacrByName(line);
     }
     if(!foundMacro &&!founName){
      foundMacr=findDefinitionMacro(temp);
      }else{
      foundEndMacr=findEndMacro(temp);
  
     if(foundMacro==1){
      if (storeLine == NULL)
     storeLine = (char*)realloc(storeLine, sizeof(char) * (strlen(tempC)+1));
     else
     storeLine = (char*)realloc(storeLine, sizeof(char) * (strlen(storeLine)+ strlen(tempC)+1));
     
     if (storeLine == NULL) {
        
        printf("Memory allocation failed\n");
        return -1;
    }
    strcat(storeLine, tempC);
    /*for me*/
   for (i = 0; i < strlen(storeLine); i++)
   {
    printf("%c", *(storeLine+i));
   }
  }
  }
 
  if(founName==1){
    return 2;
  }
   if(founName=-1){
    return -1;
  }
  if(foundMacr==-1||foundEndMacr==-1){
    printf("problem -1");
    if(foundMacr==-1){
      problems=1;
      foundMacro=1;
    }
    if(foundEndMacr==-1){
        foundMacro=0;
    }
    clearGlobals();
    return -1;
  } 
  
  return foundMacro;

}





  /* delete when no use */
int main(int argc, char const *argv[])
{
    char line[256];
    int m=0;  
/*while (m=2)
{*/
 

while (m<2)
{
  

    printf("\nEnter a line:\n ");
    if (fgets(line, sizeof(line), stdin) != NULL) {
      m=checkLineForMacr(line);
      /*m= findDefinitionMacro(line);*/
    } else {
        printf("Error reading input.\n");
    }
    printf("m= %d",m);
    /* code */
}
    return 0;
    
}
