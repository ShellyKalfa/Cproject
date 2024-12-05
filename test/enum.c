#include <stdio.h>

enum week {Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};

int main()
{

    enum week today;
    today = 1;
    printf("Day %d",today+1);
    return 0;
}
