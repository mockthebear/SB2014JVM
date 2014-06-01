//
//  stack_management.c
//  jvm
//
//

#include <stdio.h>
#include <stdlib.h>
#include "data_management.h"

//Empilha item
void pushToStack(StackItem * pushedItem, Stack * operationalStack){
    pushedItem->previousItem = operationalStack->topItem;
    operationalStack->topItem = pushedItem;
}

//Desempilha item
StackItem * popFromStack(Stack * operationalStack){
    StackItem *temp = operationalStack->topItem;
    operationalStack->topItem = temp->previousItem;
    temp->previousItem = NULL;
    return temp;
}

//Empilhar nova pilha para método java atual
void prepareNewStack(Stack * operationalStack){
    StackItem * temp = (StackItem*)calloc(1, sizeof(StackItem));
    temp->stackedItem = (u4*)calloc(1, sizeof(Stack));
    temp->previousItem = operationalStack->topItem;
    operationalStack->topItem = temp;
    
}

//Desalocar item da pilha
void freeStackItem(Stack * operationalStack){
    StackItem * temp = popFromStack(operationalStack);
    free(temp);
}

//Desalocar pilha empilhado
void freeStackedStack(Stack * operationalStack){
    StackItem * temp = operationalStack->topItem;
    if(sizeof(temp->stackedItem)==sizeof(Stack)){
        Stack * tempStack = (Stack*)(temp->stackedItem);
        while(tempStack->topItem!=NULL){
            freeStackItem(tempStack);
        }
    }else{
        return;
    }
}

//Obter valor do topo da pilha
void * getTopOfStack(Stack * operationalStack){
    return operationalStack->topItem->stackedItem;
}