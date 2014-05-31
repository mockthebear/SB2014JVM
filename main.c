//
//  main.c
//  SB2014JVM
//
//  Created by gabriel on 30/05/14.
//  Copyright (c) 2014 gabrielcarvfer. All rights reserved.
//

#include <stdio.h>
#include "jclass.h"
#include "op_management.h"


int main(int argc, char** argv) {
    
    java_class jclass;
    
    //Lê arquivo .class para memória
    jclass = *readClassFile("/Users/gabriel/SB2014JVM/HelloWorld.class", &jclass);
    
    //Impressão dos dados do arquivo .class
    printClassFileContent(&jclass);
    
    //Libera .class da memória
    freeJClass(&jclass);
    return 0;
}