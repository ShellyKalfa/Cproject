#include "firstPassHeader.h"

/*create Data Operation to save the data from Operation */
dataOperation* createDataOperation() {
   dataOperation* newOp = ( dataOperation*)malloc(sizeof( dataOperation));
    if (newOp == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    } 
    newOp->opcode=-1;
    newOp->typeSourceOperand=-1;
    newOp->typeDestinationOperand=-1;
    newOp->sourceOperand=NULL;
    newOp->destinationOperand=NULL;
    return newOp;
}
/*set Opcode */
void setOpcode( dataOperation* op, int opcode) {
    if (op != NULL) {
        op->opcode = opcode;
    }
}
/*set Type Source Operand */
void setTypeSourceOperand(  dataOperation* op, int typeSource) {
    if (op != NULL) {
        op->typeSourceOperand = typeSource;
    }
}
/*setTypeDestinationOperand */
void setTypeDestinationOperand(  dataOperation* op, int typeDest) {
    if (op != NULL) {
        op->typeDestinationOperand = typeDest;
    }
}
/*set Source Operand*/
void setSourceOperand(  dataOperation* op, const char* srcOperand) {
    if (op != NULL) {
      if(srcOperand != NULL){
          op->sourceOperand = (char*)malloc(strlen(srcOperand) + 1); 
        if (op->sourceOperand != NULL) {
            strcpy(op->sourceOperand, srcOperand); 
        }
      }
    }
}
/*set Destination Operand*/
void setDestinationOperand(  dataOperation* op, const char* destOperand) {
    if (op != NULL) {
    if(destOperand != NULL){
          op->destinationOperand = (char*)malloc(strlen(destOperand) + 1); 
        if (op->destinationOperand != NULL) {
            strcpy(op->destinationOperand, destOperand); 
        }
     }
    }
}
/* free Data Operation*/
void freeDataOperation(  dataOperation* op) {
    if (op != NULL) {
        free(op->sourceOperand);
        free(op->destinationOperand);
        free(op);
    }
}
