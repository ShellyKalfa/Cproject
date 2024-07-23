#include "header.h"
#include <stdio.h>
extern enum colorMessages;

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
 *Function give color to you error
*/
void errorMessges (enum colorMessages messge) {
 
 switch (messge)
 {
 case red:
     red ();
     break;
 case yellow:
     yellow ();
     break;
 case white:
     white ();
     break;
 default:
      white();
     break;
 }
}