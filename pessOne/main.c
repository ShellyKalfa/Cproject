#include "symbol.h"

#define MAX_NAMES 100
#define MAX_NAME_LENGTH 50

int main() {
    char names[MAX_NAMES][MAX_NAME_LENGTH];
    int n = 1,i;  
    strncpy(names[0], "t.am", MAX_NAME_LENGTH - 1);
    names[0][MAX_NAME_LENGTH - 1] = '\0';
    strncpy(names[1], "t.am", MAX_NAME_LENGTH - 1);
    names[1][MAX_NAME_LENGTH - 1] = '\0'; 

    printf("List of names:\n");
    for ( i = 0; i < n; i++) {
        printf("%s\n", names[i]);
        firstPass(names[i]);
    }

    return 0;
}