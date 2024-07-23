#include "header.h"

/*we found macro we need to put the next line in macro table*/
int foundMacro=0;
/*there are any macro? should we check for macro */
int thereAreMacros=0;


int checkNameOfMcro(char *nameMacr){
    return 0;
}











/**
 * Function get Line check for macro,or defition
 * return: 1: if we found macro, 0: if there arent,
 *  -1:if  we found macro but he is wrong and we need to stop
 */
int findDefinitionMacro(char *line ){
    char *token,*pos,*point;
    char word[]="macr";
     /* Find first occurrence of word in str */
        pos = strstr(line, word);

        if (pos != NULL)
        {
            foundMacro=1;
            /* First index of word in str is 
               Memory address of pos - memory
               address of str. 
            *col = (pos - str);
            */
           token=strtok(line," ");
          
           printf("\ntoken=%p,token[0]=%c pos=%p,pos[0]=%c\n ",token,token[0],pos,pos[0]);
           point=pos+strlen(word);
           if((pos+strlen(word))!=NULL){
           if(*point!=' '&&*point!='\0'&&*point!='\t'&& *point!='\n'){
               printf("pos[1]=%c ",*point);
               foundMacro=0;
           }
           
           }
           if((pos-1)!=NULL)
              if(pos[-1]!=' '&&pos[-1]!='\0'&&pos[-1]!='\t'){
                printf("pos[-1]=%c ",pos[-1]);
               foundMacro=0;
            
              }
            if(token !=pos&&foundMacro){  
               foundMacro=-1;
               return -1;
            } 
             if(point!=NULL && *point!='\n'&& foundMacro==1 ){
                 printf("check");
             }

        }

return foundMacro;
}


  /* delete when no use */
int main(int argc, char const *argv[])
{
    char line[256];
    int m;  

    printf("Enter a line:\n ");
    if (fgets(line, sizeof(line), stdin) != NULL) {
      m= findDefinitionMacro(line);
    } else {
        printf("Error reading input.\n");
    }
    printf("m= %d",m);
    return 0;
}
