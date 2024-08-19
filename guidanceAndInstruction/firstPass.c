#include "firstPassHeader.h"

/* keeping track on number IC */
int numberOfIC=0;
/* keeping track on number DC */
int numberOfDC=0;

int handelLine(char * line){
    char *continueLine=NULL;
    int McheckForOpration=-1,MwhichDirective=-1,McheckDataOperation=0,i;  
    int lineNmber=5,m=-1,addSymbolSuccsses=-1,printDClistSucsses=-1;
    int isCheckDirective=0;
    dataOperation * myOp;
    /**/
    char EsaveSymbol[]="the save for symbol faild ";

    CurrentLabel=NULL;
    continueLine=thereIsSymbol(line);
    if(continueLine==NULL){
      errorMessagesInLine(lineNmber,'r',0);
      return -1;
    }
    /*for me */
     printf("\n continueLine:");
       for (i = 0; i < strlen(continueLine); i++)
        {
          printf("%c", *(continueLine+i));
        }
    /*end*/
     /*check directive*/
    isCheckDirective=checkDirective(continueLine);
    printf("isCheckDirective=%d",isCheckDirective);
    if(isCheckDirective==-1){
          errorMessagesInLine(lineNmber,'r',0);
         return -1;
      }
    if (isCheckDirective){
          MwhichDirective=whichDirective(isCheckDirective,continueLine);
          printf("MwhichDirective=%d \n",MwhichDirective);
          if(CurrentLabel != NULL){
            errorMessagesWithText(CurrentLabel,strlen(CurrentLabel),'g');
             addSymbolSuccsses= addSymbol(mySymbolTabel,CurrentLabel,strlen(CurrentLabel),'D',100);
             if(addSymbolSuccsses==-1){
                errorMessagesWithText(EsaveSymbol,strlen(EsaveSymbol),'r');
                return -1;
              }
              printSymbolTabel(mySymbolTabel);
          }
          
         /*save DC*/
         printDClistSucsses=putLineInDC(myDClist, isCheckDirective,MwhichDirective);
         printDClist(myDClist);
          /*store info in DC*/
          return 1; 
    }
    if(!isCheckDirective){
    
     myOp = createDataOperation();
     McheckForOpration=checkForOpration(continueLine,myOp);
     printf("McheckForOpration=%d \n",McheckForOpration);
     if(McheckForOpration!=-1){
        printf("Opcode: %d\n", myOp->opcode);
        printf("Type Source Operand: %d\n", myOp->typeSourceOperand);
        printf("Type Destination Operand: %d\n", myOp->typeDestinationOperand);
        printf("Source Operand: %s\n", myOp->sourceOperand);
        printf("Destination Operand: %s\n", myOp->destinationOperand);
        McheckDataOperation = checkDataOperation(myOp);
        if(McheckDataOperation !=-1 ){
          /*store in ic*/
         m=getOprtion( myOp);
         printIClist(myIClist);
         printf("m=%d",m);
         if(CurrentLabel != NULL){
            addSymbolSuccsses= addSymbol(mySymbolTabel,CurrentLabel,strlen(CurrentLabel),'I',100);
            if(addSymbolSuccsses==-1){
             errorMessagesWithText(EsaveSymbol,strlen(EsaveSymbol),'r');
             return -1;
             }
          }
        }
        
         freeDataOperation(myOp);
      }
         
    }
    return 1 ;
  

}