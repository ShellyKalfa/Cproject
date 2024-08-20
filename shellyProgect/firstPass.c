#include "firstPassHeader.h"

/*the start that go from 100*/
#define L 100

/*
get line by line and check for opcod or directive
*/
int handelLine(char * line){
    char *continueLine=NULL;
    int McheckForOpration=-1,MwhichDirective=-1,McheckDataOperation=0;  
    int lineNmber=5,m=-1,addSymbolSuccsses=-1,printDClistSucsses=0;
    int isCheckDirective=0;
    dataOperation * myOp;
    /**/
    char EsaveSymbol[]="the save for symbol faild ";
    char EsaveDC[]="the save for directive faild ";

    CurrentLabel=NULL;
    continueLine=thereIsSymbol(line);
    if(continueLine==NULL){
      return -1;
    }
     /*check directive*/
    isCheckDirective=checkDirective(continueLine);
    
    if(isCheckDirective==-1){
          errorMessagesInLine(lineNmber,'r',0);
         return -1;
      }
    if (isCheckDirective){
          MwhichDirective=whichDirective(isCheckDirective,continueLine);
          if(MwhichDirective ==-1){
            return -1;
          }
          if(CurrentLabel != NULL && isCheckDirective <18 ){
             addSymbolSuccsses= addSymbol(mySymbolTabel,CurrentLabel,strlen(CurrentLabel),'D',myIClist->numbersOfLineInIC+L+myDClist->numbersOfLineInDC);
             if(addSymbolSuccsses==-1){
                errorMessagesWithText(EsaveSymbol,strlen(EsaveSymbol),'r');
                return -1;
              }
          }
          
         /*save DC*/
         printDClistSucsses=putLineInDC(myDClist, isCheckDirective,MwhichDirective);
         if(printDClistSucsses==-1){
            errorMessagesWithText(EsaveDC,strlen(EsaveDC),'r');
            return -1;
         }
          /*store info in DC*/
          return 1; 
    }
    if(!isCheckDirective){
    
     myOp = createDataOperation();
     McheckForOpration=checkForOpration(continueLine,myOp);
     if(McheckForOpration!=-1){
        McheckDataOperation = checkDataOperation(myOp);
        if(McheckDataOperation !=-1 ){
          /*store in ic*/
         m=getOprtion( myOp);
         if(CurrentLabel != NULL){
            addSymbolSuccsses= addSymbol(mySymbolTabel,CurrentLabel,strlen(CurrentLabel),'I',myIClist->numbersOfLineInIC+L-m);
            if(addSymbolSuccsses==-1){
             errorMessagesWithText(EsaveSymbol,strlen(EsaveSymbol),'r');
             return -1;
             }
          }
        }
         freeDataOperation(myOp);
      }else{
          return -1;
        }
    }
    
        
    return 1 ;
  

}