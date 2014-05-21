//
//  data_management.c
//  jvm
//
//

#include <stdio.h>
#include "jclass.h"
#include "data_management.h"



//Funções para conversão de ordem
void convertLittleBigEndianu2(u2 * tmp){
    u2 final = LSBY_MASK(*tmp)<<8 | MLSBY_MASK(*tmp)>>8;
    *tmp = final;
}
void convertLittleBigEndianu4(u4 * tmp){
    u4 final = LSBY_MASK(*tmp)<<24 | MLSBY_MASK(*tmp)<<8 | MHSBY_MASK(*tmp)>>8 | HSBY_MASK(*tmp)>>24;
    *tmp = final;
}
