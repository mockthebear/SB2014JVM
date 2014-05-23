//
//  stack_management.h
//  jvm
//
//  Created by gabriel on 23/05/14.
//  Copyright (c) 2014 gabrielcarvfer. All rights reserved.
//

#ifndef jvm_stack_management_h
#define jvm_stack_management_h

/*
 Structs e funções para pilha
 */
//Estrutura de item para ser empilhado
typedef struct stackItem{
    void * stackedItem;
    struct stackItem * previousItem;
}StackItem;
//Estrutura de pilha
typedef struct stack{
    StackItem * topItem;
}Stack;

#endif
