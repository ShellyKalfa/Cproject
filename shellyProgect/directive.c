#include "firstPassHeader.h"

extern int MinusOneTest;

/*
function that check for Directive:
found :return the opcode
not found:0
not right:-1
right and we fount which one: 16,17...
*/
int checkDirective(char *line){
    char *tempLine,*findpoint,*token,*nameSymbol;
    int lengthName=0,DirectiveNumber=0;
    /*error messages*/
    char EFailedAllocate[] ="Failed to allocate memory";
    char EnotDirective[] ="this not a directive";
    char ENullSymbol[] ="null directive or you dont have enough spaces";
    char ENullLine[] ="Null Line";
    char EplaceOfPoint[] ="your point is not in the right place";
    tempLine = (char*)malloc(sizeof(char) * (strlen(line)+1));

     if (tempLine == NULL ) {
         errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'r');
         DirectiveNumber=-1;
        return DirectiveNumber;
    }

    strcpy(tempLine, line);
    token=strtok(tempLine," ");
    if(token==NULL){
         free(tempLine);
         errorMessagesWithText(ENullLine,strlen(ENullLine),'y');
         DirectiveNumber=-1;
        return DirectiveNumber;
    }
    findpoint=strchr(token, '.');
     if(findpoint==NULL){
         findpoint=strchr(line, '.');
         free(tempLine);
         if(findpoint==NULL){
            return DirectiveNumber;
           }
         else{
            errorMessagesWithText(EplaceOfPoint,strlen(EplaceOfPoint),'r');
            DirectiveNumber=-1;
            return DirectiveNumber;
          }
     }
     if(*(token+strlen(token))=='\n'){
        lengthName=strlen(token)-1;
     }else{
    lengthName=strlen(token);
    }
    if(lengthName<8 && lengthName>0){
      nameSymbol = (char*)malloc(sizeof(char) * (lengthName));
      if (nameSymbol == NULL ) {
         errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'r');
         free(tempLine); 
         DirectiveNumber=-1;
         return DirectiveNumber;
      }
      strncpy(nameSymbol,(token+1),lengthName);
    }else
    {
         errorMessagesWithText(EnotDirective,strlen(EnotDirective),'r'); 
         free(tempLine);
          DirectiveNumber=-1;
         return DirectiveNumber;
    }
        if(*(nameSymbol+strlen(nameSymbol)-1)=='\n'){ 
          errorMessagesWithText(ENullSymbol,strlen(ENullSymbol),'r');
          free(nameSymbol);
          free(tempLine);
          DirectiveNumber=-1;
          return DirectiveNumber; 
        }
    DirectiveNumber=lookForOpcode(nameSymbol);
    if(DirectiveNumber>20 || DirectiveNumber<15){
         errorMessagesWithText(EnotDirective,strlen(EnotDirective),'r'); 
         free(nameSymbol);
         free(tempLine);
         DirectiveNumber=-1;
         return DirectiveNumber;
    }
    free(nameSymbol);
    free(tempLine);
 return DirectiveNumber;
}
/*
function that check which Directive:
and retun the opcode else -1
*/
int whichDirective(int functionNumber,char * line ){
    char *token, *tempLine;
    int success=0,functionSuccess=0;
    int * listNumbers=NULL;
    /*error message*/
    char EplaceOfPoint[] ="your point is not in the right place";
    char EFailedAllocate[] ="Failed to allocate memory";

    tempLine = (char*)malloc(sizeof(char) * (strlen(line)+1));

     if (tempLine == NULL ) {
         errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'r');
         success=-1;
        return success;
    }
    strcpy(tempLine, line);
    switch (functionNumber)
    {
    case 16:
        /* data */
        token=strstr(tempLine, "data");
        token= token +strlen("data");
        functionSuccess=dataHasFound(token);
        break;
    case 17:
        /* string */
        token=strstr(tempLine, "string");
        token=token +strlen("string");
        functionSuccess=stringHasFound(token);
        break;
    case 18:
        /* extern */
        token=strstr(tempLine, "extern");
        token=token +strlen("extern");
        functionSuccess=addToListEntryOrExtern(token,1);
        break;
    case 19:
        /* entry */
        token=strstr(tempLine, "entry");
        token=token +strlen("entry");
        functionSuccess=addToListEntryOrExtern(token,0);
        break;
    
    default:
         /* error: shoudent be here*/
         errorMessagesWithText(EplaceOfPoint,strlen(EplaceOfPoint),'r');
         free(listNumbers);
         free(tempLine);
         return 0;
        break;
    }
    free(listNumbers);
    free(tempLine);
    if(functionSuccess==-1){
      return functionSuccess;
    }
    return functionSuccess;
}
/*function ger line and make it to a list of chars 
retun 1 if succsses else -1
*/
int  stringHasFound(char * input){
    int i,foundQuotation=0;
    int countLetters = 0,success=-1;
    char *listLetters = NULL,* tempListLetters=NULL;
    /*error messages */
    char EFailedAllocate[] ="Failed to allocate memory";
    char EstringNotCorrect[] ="your string is not correct";
    char EstringNull[] ="your string is null";
    for (i=0;i<strlen(input);i++){
      if(!foundQuotation){
          if(!isspace(input[i])){
            if(input[i]!='"'){
                errorMessagesWithText(EstringNotCorrect,strlen(EstringNotCorrect),'r');
                if(tempListLetters != NULL){
                    free(tempListLetters);
                }
                if(listLetters != NULL && tempListLetters != listLetters){
                    free(listLetters); 
                }
                return success;
            }
            else {
                foundQuotation=1;
            }
          }
      }else
      {
          if(!isalpha(input[i])){
               if(input[i]!='"'){
                errorMessagesWithText(EstringNotCorrect,strlen(EstringNotCorrect),'r');
                if(tempListLetters != NULL){
                    free(tempListLetters);
                }
                if(listLetters != NULL && tempListLetters != listLetters){
                    free(listLetters); 
                }
                return success;
               }
               else {
                foundQuotation=0;
               }
            }
            if(foundQuotation){
                countLetters++;
                tempListLetters= (char*)realloc(listLetters, sizeof(char) * countLetters);
                if(tempListLetters == NULL){
                      errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'y');
                       free(listLetters); 
                       return success;
                }
                 listLetters = tempListLetters;
                listLetters[countLetters - 1] = input[i];
            }
        }
    }
  
    /*store list somere else */

   if(listLetters != NULL){
       for (i = 0; i < countLetters; i++){
         string[i]=listLetters[i];
       }
   }
   if(listLetters == NULL){ 
       errorMessagesWithText(EstringNull,strlen(EstringNull),'r');
                if(tempListLetters != NULL){
                    free(tempListLetters);
                }
                if(listLetters != NULL && tempListLetters != listLetters){
                    free(listLetters); 
                }
                return success;
   }else{
         success=countLetters;
   }

   if(success&&listLetters != NULL){
      fillArrayString(listLetters,countLetters);
      
   }
   if(tempListLetters != NULL){
       free(tempListLetters);
    }
    if(listLetters != NULL && tempListLetters != listLetters){
      free(listLetters); 
    }

    return success;

 }

/* dataHasFound get the list of numbers in data 
and put them in list and store them
if everthing is good:count of numbers 
else return :-1
*/
int  dataHasFound(char * input){
    char *findcomma;
    int i,number=0,stop=0,length=0;
    int countNumbers = 0;
    int *listNumbers = NULL,* tempListNumbers=NULL;
    /*error messages */
    char EFailedAllocate[] ="Failed to allocate memory";
    while(number!=-1&&!stop&& strlen(input)>length){
         findcomma=strchr((input+length+1), ',');
         if(findcomma == NULL){
            number= getInteger(input+length+1,strlen(input) -length);
            stop=1;
         }else{
         number= getInteger(input+length+1 , (findcomma-input-length));
         length=findcomma-input;
         }
         if(number!= -1 || MinusOneTest){
             countNumbers++;
             tempListNumbers= (int*)realloc(listNumbers, sizeof(int) * countNumbers);
             if(tempListNumbers == NULL){
                      errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'y');
                       free(listNumbers); 
                       return -1;
             }
             listNumbers = tempListNumbers;
             listNumbers[countNumbers - 1] = number;
             number=MinusOneTest;
         }
    }
 
if(countNumbers>0){
 for (i = 0; i < countNumbers; i++){
    data[i]=listNumbers[i];
 }
 }
  /*store somere else*/
    if(tempListNumbers != NULL){
       free(tempListNumbers);
    }
    if(listNumbers != NULL && tempListNumbers != listNumbers){
      free(listNumbers); 
    }
    if(stop&& number!=-1 ){
        return countNumbers;
    }
return -1;
}

/* getInteger get  number 
and check if there ok 
if everthing is good  :the number (...,-1,0,1,....)
else return :-1
*warning: if is -1 and everthing ok send -1 and put it global 
*/
int getInteger(char *input ,int lengthInput){
      char *temp;
      int number=-1,countSpaces=0,numberFlage=0, flag=0,flageMines=0;
      size_t i;
      
      /*erorr messge*/
       char EnotNumber[] ="not a number";
       char EnullNumber[] ="Null number, you forgot to put number ";
       char EFailedAllocate[] ="Failed to allocate memory";
       char EforgotComma[] ="you forgot comma";
       char ETooManyHyphen[] ="Hyphen is not good";
       char EzeroWithHyphen[] ="Hyphen is not go with zero,check your math";
       char EnumberoutOfRange[] ="Error: Number out of range for 15-bit 2's complement representation.\n";
       MinusOneTest=0;

       if(!lengthInput){
            errorMessagesWithText(EnullNumber,strlen(EnullNumber),'r');
            return number;
       }
      temp=(char*)malloc(sizeof(char) * (lengthInput+1));
      if(temp==NULL){
          errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'r');
          free(temp);
          return number;
      }
      temp[lengthInput+1]='\0';
      for (i = 0; i < lengthInput-1; i++)
      {
         if(isdigit(input[i]) || isspace(input[i]) ||input[i]=='-' ){
            temp[i]=input[i];
            if(isspace(input[i])){
                countSpaces++;
            }
             if(input[i]=='-'){
                flageMines++;
                if(flageMines>1){
                   free(temp);
                  errorMessagesWithText(ETooManyHyphen,strlen(ETooManyHyphen),'r');
                  return-1;
                }
                if((i) == lengthInput){
                  free(temp);
                  errorMessagesWithText(ETooManyHyphen,strlen(ETooManyHyphen),'r');
                  return-1;
              
                }
                 if(!isdigit(input[i+1])){
                  free(temp);
                  errorMessagesWithText(ETooManyHyphen,strlen(ETooManyHyphen),'r');
                  return-1;
                }
                 if(input[i+1]=='0'){
                  free(temp);
                  errorMessagesWithText(EzeroWithHyphen,strlen(EzeroWithHyphen),'r');
                  return-1;
                }
            }
            if(isdigit(input[i])){
                if(!flag)
                {
                     numberFlage=countSpaces;
                     flag=1;
                }
                if(numberFlage!=countSpaces){
                  free(temp);
                  errorMessagesWithText(EforgotComma,strlen(EforgotComma),'r');
                  return-1;
                }
            }
          }else{
           free(temp);
           errorMessagesWithText(EnotNumber,strlen(EnotNumber),'r');
           return-1;
          }
      }
      if(countSpaces==lengthInput-1&&(lengthInput-1)!=0){
          errorMessagesWithText(EnullNumber,strlen(EnullNumber),'r');
          free(temp);
          return number;
      }
    number= atoi(temp);
    if (number==-1){
        MinusOneTest=1;
    }
   if (number > 2047 || number < -2048) {
         errorMessagesWithText(EnumberoutOfRange,strlen(EnumberoutOfRange),'r');
         number= -1;
     }
    free(temp);
    return number;
 }
 /*function get line and adding the List to Entry Or Extern
 *return 1 succeses else -1
  */
 int addToListEntryOrExtern( char * nameEntry,int EntryOrExtern ){
   int okEntry=-1,sucssesEntry=0;
   char *checkNameEntry=NULL,*token=NULL;
    /*erorr messge*/
   char ENoSpaces[] ="you dont have space";
   char EFailedAllocate[] ="Failed to allocate memory";
   char ECanBeSymbol[] ="Failed that label cant be symbol";
   char EemptyEntery[] ="Failed empty entery";
   if(!isspace(*nameEntry)){
      errorMessagesWithText(ENoSpaces,strlen(ENoSpaces),'r');
     return -1;
   }
   token=strtok(nameEntry," ");
   if(token == NULL||*token=='\n'){
     errorMessagesWithText(EemptyEntery,strlen(EemptyEntery),'r');
     return -1;
   }
   checkNameEntry=(char*)malloc(sizeof(char) * (strlen(token)+1));
      if (checkNameEntry == NULL ) {
         errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'r');
         return -1;
      }
   strncpy(checkNameEntry, token,strlen(token));
   checkNameEntry[strlen(token)]='\0';
   
   okEntry= checkSymbol(checkNameEntry,0);
   sucssesEntry=saveEntryOrExtern(checkNameEntry,EntryOrExtern);
   if(sucssesEntry==-1){
     return -1;
   }

   free(checkNameEntry);
   if(okEntry==-1){
     errorMessagesWithText(ECanBeSymbol,strlen(ECanBeSymbol),'r');
     return -1;
   }
   return 1;

 }
 /*save Entry Or Extern in there global list*/
 int saveEntryOrExtern(char *nameSymbol,int EntryOrExtern ){
  int i ,length=0,inTabel=1, okStoreg=0;
  char *tempName=NULL,*saveName=NULL ;
  char EalreadyInTabelExtern[] ="Extern already in the tabel  ";
  char EalreadyInTabelEntery[] ="Entery already in the tabel ";
  char EFailedAllocate[] ="Failed to allocate memory";
  char EEntery[]="Entery";
  char EExtern[]="Extern";
  char ESymbol[]="Symbol";
   for (i = 0; i < strlen(nameSymbol); i++) {
        if (!isspace(nameSymbol[i])) {
            length++;
            
            tempName = (char *)realloc(saveName, sizeof(char) * (length + 1));
            if (tempName == NULL) {
                
                errorMessagesWithText(EFailedAllocate, strlen(EFailedAllocate), 'r');
                free(saveName); 
                saveName = NULL;
                return -1;
            }
            saveName = tempName;
            saveName[length - 1] = nameSymbol[i];  
        }
    }
  if (saveName == NULL ) {
        errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'r');
        free(tempName);
        return -1;
    }
  saveName[length]='\0';
 
 
   /*entry =0 ,extern =1*/
   if(EntryOrExtern==0){
     inTabel=ISsearchEntry(listOfEntry, saveName);
     if(inTabel){
        errorMessagesWithTextExstra(EalreadyInTabelEntery,strlen(EalreadyInTabelEntery),EEntery,strlen(EEntery),'r');
        free(saveName);
        return -1;
      }
      inTabel=ISsearchExtern(listOfExtern, saveName);
      if(inTabel){
        errorMessagesWithTextExstra(EalreadyInTabelEntery,strlen(EalreadyInTabelEntery),EExtern,strlen(EExtern),'r');
        free(saveName);
        return -1;
      }
      okStoreg= addEntry(listOfEntry, saveName);
      if(okStoreg==-1){
        errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'r');
        free(saveName);
        return -1;
      }
   }
   else
   {
     inTabel=ISsearchEntry(listOfEntry, saveName);
     if(inTabel){
        errorMessagesWithTextExstra(EalreadyInTabelExtern,strlen(EalreadyInTabelExtern),EEntery,strlen(EEntery),'r');
        free(saveName);
        return -1;
      }
      inTabel=ISsearchExtern(listOfExtern, saveName);
      if(inTabel){
        errorMessagesWithTextExstra(EalreadyInTabelExtern,strlen(EalreadyInTabelExtern),EExtern,strlen(EExtern),'r');
        free(saveName);
        return -1;
      }
      inTabel=ISsearchSymbol(mySymbolTabel,saveName);
      if(inTabel){
        errorMessagesWithTextExstra(EalreadyInTabelExtern,strlen(EalreadyInTabelExtern),ESymbol,strlen(ESymbol),'r');
        free(saveName);
        return -1;
      }
     
      okStoreg=  createAndAddExtern(listOfExtern, saveName, length);
      if(okStoreg==-1){
        errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'r');
        free(saveName);
        return -1;
      }
   }
   
return 1;
 }

 