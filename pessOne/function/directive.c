#include "symbol.h"

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
    lengthName=strlen(token)-1;
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
    int success=0,i;
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
        dataHasFound(token);
        printf("data\n");
        break;
    case 17:
        /* string */
        token=strstr(tempLine, "string");
        token=token +strlen("string");
        printf("string\n");
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

int  dataHasFound(char * input){
    char *temp,*token=NULL,*findcomma;
    int i,number,stop=0,length=0;
    int countNumbers = 0;
    int *listNumbers = NULL,* tempListNumbers=NULL;
    /*error messages */
    char EFailedAllocate[] ="Failed to allocate memory";
    char EemptyDirective[] ="empty directive ";  
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
         if(number!= -1){
             countNumbers++;
             tempListNumbers= (int*)realloc(listNumbers, sizeof(int) * countNumbers);
             if(temp == NULL){
                      errorMessagesWithText(EFailedAllocate,strlen(EFailedAllocate),'y');
                       free(listNumbers); 
                       free(tempListNumbers); 
                       return -1;
             }
             listNumbers = tempListNumbers;
             listNumbers[countNumbers - 1] = number;
         }
    }
 printf("all good");
 printf("\n");
 for (i = 0; i < countNumbers; i++){
   printf("%d", listNumbers[i]);
 }
 
return 1;
}
 int getInteger(char *input ,int lengthInput){
      char *temp;
      int number=-1,countSpaces=0,numberFlage=0, flag=0;
      size_t i;
      /*erorr messge*/
       char EnotNumber[] ="not a number";
       char EnullNumber[] ="Null number, you forgot to put number ";
       char EFailedAllocate[] ="Failed to allocate memory";
       char EforgotComma[] ="you forgot comma";
       printf("\n you in c=%c , length =%d",*input,lengthInput);
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
         if(isdigit(input[i]) || isspace(input[i]) ){
            temp[i]=input[i];
            if(isspace(input[i])){
                countSpaces++;
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
      if(countSpaces==lengthInput-1){
          errorMessagesWithText(EnullNumber,strlen(EnullNumber),'r');
          free(temp);
          return number;
      }
    number= atoi(temp);
    free(temp);
    return number;
 }
 /*
 
             printf("number %d",number);
            countNumbers++;
            listNumbers = (int*)realloc(listNumbers,sizeof(int) * (countNumbers));
          *(listNumbers+countNumbers-1)=number;*/