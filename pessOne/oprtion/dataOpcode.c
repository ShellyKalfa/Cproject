#include "opration.h"


dataOperation* createDataOperation() {
   dataOperation* newOp = ( dataOperation*)malloc(sizeof( dataOperation));
    if (newOp == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
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
/*
int main() {
   
      dataOperation* myOp = createDataOperation();
    if (myOp != NULL) {
        setOpcode(myOp, 1);
        setTypeSourceOperand(myOp, 2);
        setTypeDestinationOperand(myOp, 3);
        setSourceOperand(myOp, "source");
        setDestinationOperand(myOp, "destination");

        printf("Opcode: %d\n", myOp->opcode);
        printf("Type Source Operand: %d\n", myOp->typeSourceOperand);
        printf("Type Destination Operand: %d\n", myOp->typeDestinationOperand);
        printf("Source Operand: %s\n", myOp->sourceOperand);
        printf("Destination Operand: %s\n", myOp->destinationOperand);

        freeDataOperation(myOp);
    }

    return 0;
}*/
