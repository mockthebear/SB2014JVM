//
//  stack_management.c
//  jvm
//
//

#include <stdio.h>
#include "jclass.h"

//Empilha dado
void push(StackItem * pushedItem, Stack * operationalStack){
    pushedItem->previousItem = operationalStack->topItem;
    operationalStack->topItem = pushedItem;
}

//Desempilha dado
StackItem * pop(Stack * operationalStack){
    StackItem *temp = operationalStack->topItem;
    operationalStack->topItem = temp->previousItem;
    temp->previousItem = NULL;
    return temp;
}

