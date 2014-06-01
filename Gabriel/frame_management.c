//
//  frame_data_management.c
//  SB2014JVM
//
//

#include <stdio.h>
#include <stdlib.h>
#include "data_management.h"

//Estrutura do Frame de memória de um método
/*typedef struct memFrame{
    Stack * varStack;
    VarVector * varVector;
    ObjectRef * objectRef;
}MemFrame;*/

void newFrame(Stack * operationalStack){
    MemFrame * temp = (MemFrame*)calloc(1, sizeof(MemFrame));
    StackItem * stackItem = (StackItem*)calloc(1,sizeof(StackItem));
    stackItem->stackedItem = (u4*)temp;
    stackItem->type_of_item = MEMFRAME;
    pushToStack(stackItem, operationalStack);
    return;
}

void freeFrame(Stack * operationalStack){
    StackItem * temp = popFromStack(operationalStack);
    MemFrame tempFrame = *(MemFrame*)temp->stackedItem;
    freeStackedStack(tempFrame.frameStack);
    //freeVarVector(tempFrame.varVector);
    freeStackItem(operationalStack);
}

