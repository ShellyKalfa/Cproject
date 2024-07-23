#include "header.h"


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