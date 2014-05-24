//
//  data_management.c
//  jvm
//
//

#include <stdio.h>
#include <stdlib.h>
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

//código UTF-8 pode ir até 6 bytes
/*u1 * convertToutf8(u1 * vet, u2 num_characters){
    u1 * vet_utf = (u1*)calloc(6*num_characters, sizeof(u1));
    u1 temp =0;
    for(int i=0, j=0;i<num_characters; i++){
        temp = vet[i];
        if((temp&0x80)==0x80){
            if(vet...
        }else{
            vet_utf[j]=temp;
            j+=6;
        }
    }
    return vet_utf;
}
*/
u1 * convertFromutf8(u1 * vet, u2 num_characters){
    u1 * vet_ascii = (u1*)calloc(num_characters, sizeof(u1));
    u1 temp =0;
    for(int i=0;i<num_characters;i++){
        temp = vet[i];
        if((temp&0xE0)==0xE0){
            vet_ascii[i] = ((temp & 0xf) << 12) + ((vet[i+1] & 0x3f) << 6) + (vet[i+2] & 0x3f);
            i+=2;
        }else if((temp&0x60)==0x60){
            vet_ascii[i] = ((temp & 0x1f) << 6) + ( vet[i+1] & 0x3f);
            i++;
        }else{
            vet_ascii[i] = temp;
        }
    }
    return vet_ascii;
}