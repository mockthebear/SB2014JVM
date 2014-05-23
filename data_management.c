//
//  data_management.c
//  jvm
//
//

#include <stdio.h>
#include "jclass.h"
#include "data_management.h"



//Funções para conversão de ordem
/*void convertLittleBigEndianu2(u2 * mp){
    U2_CONVERTION(*mp);
}
void convertLittleBigEndianu4(u4 * mp){
    U4_CONVERTION(*mp);
    //u4 final = LSBY_MASK(*tmp)<<24 | MLSBY_MASK(*tmp)<<8 | MHSBY_MASK(*tmp)>>8 | HSBY_MASK(*tmp)>>24;
    //tmp = final;
}*/

//Funções de leitura
u1 readu1(FILE * fp){
    u1 temp;
    fread(&temp, 1, sizeof(u1), fp);
    return temp;
}
u2 readu2(FILE * fp){
    u2 temp;
    fread(&temp, 1, sizeof(u2), fp);
    //convertLittleBigEndianu2(&temp);
    U2_CONVERTION(temp);
    return temp;
}
u4 readu4(FILE * fp){
    u4 temp;
    fread(&temp, 1, sizeof(u4), fp);
    //convertLittleBigEndianu4(&temp);
    U4_CONVERTION(temp);
    return temp;
}