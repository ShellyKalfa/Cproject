#include <stdio.h>
#include <stdlib.h> 

int getOprtionNumber(int type ,char *numberOp){
    int placeNumberStart=0,realNumber=0;
     if(type==-1){
     return 0;
    }
    switch (type)
    {
    case 0:
        placeNumberStart=1;
        break;
    case 2:
        placeNumberStart=2;
        break; 
    case 3:
        placeNumberStart=1;
        break;          
    default:
        break;
    }
    realNumber=atoi((numberOp+placeNumberStart));
 return realNumber;
}


int main() {
    int SourceR=0,DestinationR=0;
    int Source = -1;        
    int Destination = 3;  
    char CSourceR[]="#34";
    char CDestinationR[]="r4";
    SourceR=getOprtionNumber(Source,CSourceR);
    printf("CSourceR %d",SourceR);
    DestinationR=getOprtionNumber(Destination,CDestinationR);
    printf("DestinationR %d",DestinationR);
    return 0;
}
