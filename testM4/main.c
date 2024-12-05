#include <stdio.h>
#include "counter.h"  

int main() {
    char c;
    
    printf("Initial value of counter: %d\n", counter);
   while ((c = fgetc(stdin)) != 'a')
   {
        increment_counter();
   }
   
   
   
    printf("Updated value of counter: %d\n", counter);
    
    return 0;
}
