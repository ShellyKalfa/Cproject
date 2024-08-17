#include "symbol.h"

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
    int lengthName=0,DirectiveNumber=0,i;
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
    printf(" copy ");
    token=strtok(tempLine," ");
    printf("%c \n",*token);
    if(token==NULL){
         free(tempLine);
         errorMessagesWithText(ENullLine,strlen(ENullLine),'y');
         DirectiveNumber=-1;
        return DirectiveNumber;
    }
    findpoint=strchr(token, '.');
     
     printf("p=%p \n",findpoint);
     /**/
     if(findpoint==NULL){
         printf("null \n");
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
    printf("lengthName=%d \n",lengthName);
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
    printf("\n");
   
    for (i = 0; i < strlen(nameSymbol); i++)
        {
          printf("%c", *(nameSymbol+i));
        }
        if(*(nameSymbol+strlen(nameSymbol)-1)=='\n'){ 
          errorMessagesWithText(ENullSymbol,strlen(ENullSymbol),'r');
          free(nameSymbol);
          free(tempLine);
          DirectiveNumber=-1;
          return DirectiveNumber; 
        }
    DirectiveNumber=lookForOpcode(nameSymbol);
    printf("DirectiveNumber=%d",DirectiveNumber);
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

*/
int whichDirective(int functionNumber,char * line ){
    char *token, *tempLine;
    int success=0,i, functionSuccess=0;
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
    printf(" copy ");
       printf("\n");
    printf("new line ");
    for (i = 0; i < strlen(tempLine); i++)
        {
          printf("%c", *(tempLine+i));
        }
    printf("\n");

    switch (functionNumber)
    {
    case 16:
        /* data */
        token=strstr(tempLine, "data");
        token= token +strlen("data");
        functionSuccess=dataHasFound(token);
        printf("\ndata is %d \n",functionSuccess);
        break;
    case 17:
        /* string */
        token=strstr(tempLine, "string");
        token=token +strlen("string");
        functionSuccess=stringHasFound(token);
        printf("\nstring is %d \n",functionSuccess);
        break;
    case 18:
        /* extern */
        token=strstr(tempLine, "extern");
        token=token +strlen("extern");
        printf("extern\n");
        break;
    case 19:
        /* entry */
        token=strstr(tempLine, "entry");
        token=token +strlen("entry");
        printf("entry\n");
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
    return 0;
}

int  stringHasFound(char * input){
    int i,foundQuotation=0;
    int countLetters = 0,success=-1;
    char *listLetters = NULL,* tempListLetters=NULL;
    /*error messages */
    char EFailedAllocate[] ="Failed to allocate memory";
    char EstringNotCorrect[] ="your string is not correct";
    char EstringNull[] ="your string is null";
    printf("\n");
    printf("new line ");
    for (i = 0; i < strlen(input); i++)
        {
          printf("%c", *(input+i));
        }
    printf("\n");
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
         printf("%c ", listLetters[i]);
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
         success=1;
   }

   if(success&&listLetters != NULL){
      fillArrayString(listLetters,countLetters);
      printArrayStringToFile(EstringNull,countLetters);
   }
   if(tempListLetters != NULL){
       free(tempListLetters);
    }
    if(listLetters != NULL && tempListLetters != listLetters){
      free(listLetters); 
    }

    return 1;

 }

/* dataHasFound get the list of numbers in data 
and put them in list and store them
if everthing is good  :1
else return :-1
*/
int  dataHasFound(char * input){
    char *findcomma;
    int i,number,stop=0,length=0;
    int countNumbers = 0;
    int *listNumbers = NULL,* tempListNumbers=NULL;
    /*error messages */
    char EFailedAllocate[] ="Failed to allocate memory";
    printf("\n");
    printf("new line ");
    for (i = 0; i < strlen(input); i++)
        {
          printf("%c", *(input+i));
        }
    printf("\n");
    while(number!=-1&&!stop&& strlen(input)>length){
         findcomma=strchr((input+length+1), ',');
         printf("\n you in findcomma c=%c  length =%d findcomma=%p",*(input+length+1),length,findcomma);
         
         if(findcomma == NULL){
            printf("null comma");
            number= getInteger(input+length+1,strlen(input) -length);
            printf("di=%d",number);
            stop=1;
         }else{
         number= getInteger(input+length+1 , (findcomma-input-length));
         printf("di=%d",number);
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
 
 printf("\n");

 for (i = 0; i < countNumbers; i++){
   printf("%d ", listNumbers[i]);
 }
  /*store somere else*/
    if(tempListNumbers != NULL){
       free(tempListNumbers);
    }
    if(listNumbers != NULL && tempListNumbers != listNumbers){
      free(listNumbers); 
    }
    if(stop&& number!=-1 ){
        return 1;
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
       printf("\n you in c=%c , length =%d",*input,lengthInput);
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
      printf("\n");
      for (i = 0; i < lengthInput-1; i++)
      {
           printf("%c",input[i]);
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
                  printf("did not good");
                  return-1;
                }
                if((i+1) == lengthInput-1 ){
                  free(temp);
                  errorMessagesWithText(ETooManyHyphen,strlen(ETooManyHyphen),'r');
                  printf("did not good");
                  return-1;
              
                }
                 if(!isdigit(input[i+1])){
                  free(temp);
                  errorMessagesWithText(ETooManyHyphen,strlen(ETooManyHyphen),'r');
                  printf("did not good");
                  return-1;
                }
                 if(input[i+1]=='0'){
                  free(temp);
                  errorMessagesWithText(EzeroWithHyphen,strlen(EzeroWithHyphen),'r');
                  printf("did not good");
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
                  printf("did not good");
                  return-1;
                }
            }
          }else{
           free(temp);
           errorMessagesWithText(EnotNumber,strlen(EnotNumber),'r');
           printf("did not good");
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
   if (number > 16383 || number < -16384) {
         errorMessagesWithText(EnumberoutOfRange,strlen(EnumberoutOfRange),'r');
         number= -1;
     }
    free(temp);
    return number;
 }

 