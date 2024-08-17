#include "symbol.h"


void red () {
  printf("\033[1;31m");
}

void yellow () {
  printf("\033[1;33m");
}

void white () {
  printf("\033[0m");
}
/*
 * Function to give color to your error
 */
void errorMessages(enum colorMessages message) {
    switch (message) {
        case RED:
            red();
            break;
        case YELLOW:
            yellow();
            break;
        case WHITE:
            white();
            break;
        default:
            white();
            break;
    }
}
void errorMessagesWithText(char * message,int length,char color){
  int i=0;
  if(color =='r'){
     red();
  }
  if(color =='y'){
    yellow();
  }
  printf("\n");
 for (i=0;i<length;i++){
 printf("%c",*(message+i));
 }
 printf("\n");
 white();
}
void errorMessagesWithTextExstra(char * message,int length,char * messageExstra,int lengthExstra,char color){
  int i=0,j=0;
  if(color =='r'){
     red();
  }
  if(color =='y'){
    yellow();
  }
    printf("\n");
 for (i=0;i<length;i++){
 printf("%c",*(message+i));
 }
 printf(" ");
 for (j=0;j<length;j++){
 printf("%c",*(messageExstra+j));
 }
  printf("\n");
 white();
}
void errorMessagesWithTextIN(char * message,int length,char * messageIn,int lengthIn,int whereIn,char color){
  int i=0;
  if(color =='r'){
     red();
  }
  if(color =='y'){
    yellow();
  }
  printf("\n");
 for (i=0;i<whereIn;i++){
 printf("%c",*(message+i));
 }
 printf(" ");
  for (i=0;i<lengthIn;i++){
 printf("%c",*(messageIn+i));
 }
 printf(" ");
  for (i=whereIn;i<length;i++){
 printf("%c",*(message+i));
 }
 printf("\n");
 white();
}

void errorMessagesInLine(int numberOfLine,char color,int problem){
  if(color =='r'){
     red();
  }
  if(color =='y'){
    yellow();
  }
  printf("\n");
  switch (problem)
  {
  case 1:
      printf("error in line i= %d: this line has exceeded the limit ",numberOfLine);
    break;
  
  default:
   printf("error in line i= %d",numberOfLine);
    break;
  }
  printf("\n");
 white();
}