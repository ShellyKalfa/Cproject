#include "opration.h"


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

void setOpcode( dataOperation* op, int opcode) {
    if (op != NULL) {
        op->opcode = opcode;
    }
}

void setTypeSourceOperand(  dataOperation* op, int typeSource) {
    if (op != NULL) {
        op->typeSourceOperand = typeSource;
    }
}

void setTypeDestinationOperand(  dataOperation* op, int typeDest) {
    if (op != NULL) {
        op->typeDestinationOperand = typeDest;
    }
}

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

void freeDataOperation(  dataOperation* op) {
    if (op != NULL) {
        free(op->sourceOperand);
        free(op->destinationOperand);
        free(op);
    }
}

