//
//  op_management.c
//  jvm
//
//

#include <stdio.h>
#include "data_management.h"
#include "op_management.h"

//Implementação das operações
//Primeira família de instruções
void nop (){
    
}
void aconst_null(){
    
}
void iconst_m1(){
    
}
void iconst_0(){
    
}
void iconst_1(){
    
}
void iconst_2(){
    
}
void iconst3(){
    
}
void iconst_4(){
    
}
void iconst_5(){
    
}
void lconst_0(){
    
}
void lconst_1(){
    
}
void fconst_0(){
    
}
void fconst_1(){
    
}
void fconst_2(){
    
}
void dconst_0(){
    
}
void dconst_1(){
    
}

//Segunda família de instruções
void bipush(){
    
}
void sipush(){
    
}
void ldc(){
    
}
void ldc_w(){
    
}
void ldc2_w(){
    
}
void iload(){
    
}
void lload(){
    
}
void fload(){
    
}
void dload(){
    
}
void aload(){
    
}
void iload_0(){
    
}
void iload_1(){
    
}
void iload_2(){
    
}
void iload_3(){
    
}
void lload_0(){
    
}
void lload_1(){
    
}

//Terceira família de instruções 0x2Xh
void lload_2(){
    
}
void lload_3(){
    
}
void fload_0(){
    
}
void fload_1(){
    
}
void fload_2(){
    
}
void fload_3(){
    
}
void dload_0(){
    
}
void dload_1(){
    
}
void dload_2(){
    
}
void dload_3(){
    
}
void aload_0(){
    
}
void aload_1(){
    
}
void aload_3(){
    
}
void iaload(){
    
}
void laload(){
    
}

//Quarta família de instruções 0x3Xh
void faload(){
    
}
void daload(){
    
}
void aaload(){
    
}
void baload(){
    
}
void caload(){
    
}
void saload(){
    
}
void istore(){
    
}
void lstore(){
    
}
void fstore(){
    
}
void dstore(){
    
}
void astore(){
    
}
void istore_0(){
    
}
void istore_1(){
    
}
void istore_2(){
    
}
void istore_3(){
    
}
void lstore_0(){
    
}

//Quinta família de instruções 0x4Xh
void lstore_1(){
    
}
void lstore_2(){
    
}
void lstore_3(){
    
}
void fstore_0(){
    
}
void fstore_1(){
    
}
void fstore_2(){
    
}
void fstore_3(){
    
}
void dstore_0(){
    
}
void dstore_1(){
    
}
void dstore_2(){
    
}
void dstore_3(){
    
}
void astore_0(){
    
}
void astore_1(){
    
}
void astore_2(){
    
}
void astore_3(){
    
}
void iastore(){
    
}

//Sexta família de instruções 0x5Xh
void lastore(){
    
}
void fastore(){
    
}
void dastore(){
    
}
void aastore(){
    
}
void bastore(){
    
}
void castore(){
    
}
void sastore(){
    
}
void pop(){
    
}
void pop2(){
    
}
void _dup(){
    
}
void dup_x1(){
    
}
void dup_x2(){
    
}
void _dup2(){
    
}
void dup2_x1(){
    
}
void dup2_x2(){
    
}
void swap(){
    
}

//Sétima família de instruções 0x6Xh
void iadd(){
    
}
void ladd(){
    
}
void fadd(){
    
}
void dadd(){
    
}
void isub(){
    
}
void lsub(){
    
}
void fsub(){
    
}
void dsub(){
    
}
void imul(){
    
}
void lmul(){
    
}
void fmul(){
    
}
void dmul(){
    
}
void idiv(){
    
}
void _ldiv(){
    
}
void fdiv(){
    
}
void ddiv(){
    
}

//Oitava família de instruções 0x7Xh
void irem(){
    
}
void lrem(){
    
}
void frem(){
    
}
void _drem(){
    
}
void ineg(){
    
}
void lneg(){
    
}
void fneg(){
    
}
void dneg(){
    
}
void ishl(){
    
}
void lshl(){
    
}
void ishr(){
    
}
void lshr(){
    
}
void iushr(){
    
}
void lushr(){
    
}
void iand(){
    
}
void land(){
    
}

//Nona família de instruções 0x8Xh
void ior(){
    
}
void lor(){
    
}
void ixor(){
    
}
void lxor(){
    
}
void iinc(){
    
}
void i2l(){
    
}
void i2f(){
    
}
void i2d(){
    
}
void l2i(){
    
}
void l2f(){
    
}
void l2d(){
    
}
void f2i(){
    
}
void f2l(){
    
}
void f2d(){
    
}
void d2i(){
    
}
void _d2i(){
    
}

//Décima família de instruções 0x9Xh
void d2f(){
    
}
void i2b(){
    
}
void i2c(){
    
}
void i2s(){
    
}
void lcmp(){
    
}
void fcmpl(){
    
}
void fcmpg(){
    
}
void dcmpl(){
    
}
void dcmpg(){
    
}
void ifeq(){
    
}
void ifne(){
    
}
void iflt(){
    
}
void ifge(){
    
}
void ifgt(){
    
}
void ifle(){
    
}
void if_icmpeq(){
    
}

//Décima primeira família de instruções 0xAXh
void if_icmpne(){
    
}
void if_icmplt(){
    
}
void if_icmpge(){
    
}
void if_icmpgt(){
    
}
void if_icmple(){
    
}
void if_acmpeg(){
    
}
void if_acmpne(){
    
}
void _goto(){
    
}
void jsr(){
    
}
void ret(){
    
}
void table_switch(){
    
}
void lookup_switch(){
    
}
void ireturn(){
    
}
void lreturn(){
    
}
void freturn(){
    
}
void dreturn(){
    
}

//Décima segunda família de instruções 0xBXh
void areturn(){
    
}
void _return(){
    
}
void getstatic(){
    
}
void putstatic(){
    
}
void getfield(){
    
}
void putfield(){
    
}
void invokevirtual(){
    
}
void invokespecial(){
    
}
void invokestatic(){
    
}
void invokeInterface(){
    
}
void new(){
    
}
void newArray(){
    
}
void anewArray(){
    
}
void arrayLength(){
    
}
void athrow(){
    
}

//Décima terceira família de instruções 0xCXh
void checkLast(){
    
}
void instanceOf(){
    
}
void monitorEnter(){
    
}
void monitorExit(){
    
}
void wide(){
    
}
void multiNewArray(){
    
}
void ifNull(){
    
}
void ifNonNull(){
    
}
void goto_w(){
    
}
void jsr_w(){
    
}
void breakPoint(){
    
}

//Décima quarta família de instruções 0xDXh

//Décima quinta família de instruções 0xEXh

//Décima sexta família de instruções 0xFXh
void impdep1(){
    
}
void impdep2(){
    
}


//Tabela de operações
void * op_table[256]={
    //Primeira família de instruções 0x0Xh
    &nop, &aconst_null, &iconst_m1, &iconst_0, &iconst_1, &iconst_2, &iconst3, &iconst_4,
    &iconst_5, &lconst_0, &lconst_1, &fconst_0, &fconst_1, &fconst_2, &dconst_0, &dconst_1,
    
    //Segunda família de instruções 0x1Xh
    &bipush, &sipush, &ldc, &ldc_w, &ldc2_w, &iload, &lload, &fload,
    &dload, &aload, &iload_0, &iload_1, &iload_2, &iload_3, &lload_0, &lload_1,
    
    //Terceira família de instruções 0x2Xh
    &lload_2, &lload_3, &fload_0, &fload_1, &fload_2, &fload_3, &dload_0, &dload_1,
    &dload_2, &dload_3, &aload_0, &aload_1, &aload_3, &iaload, &laload,
    
    //Quarta família de instruções 0x3Xh
    &faload, &daload, &aaload, &baload, &caload, &saload, &istore, &lstore,
    &fstore, &dstore, &astore, &istore_0, &istore_1, &istore_2, &istore_3, &lstore_0,
    
    //Quinta família de instruções 0x4Xh
    &lstore_1, &lstore_2, &lstore_3, &fstore_0, &fstore_1, &fstore_2, &fstore_3, &dstore_0,
    &dstore_1, &dstore_2, &dstore_3, &astore_0, &astore_1, &astore_2, &astore_3, &iastore,
    
    //Sexta família de instruções 0x5Xh
    &lastore, &fastore, &dastore, &aastore, &bastore, &castore, &sastore, &pop,
    &pop2, &_dup, &dup_x1, &dup_x2, &_dup2, &dup2_x1, &dup2_x2, &swap,
    
    //Sétima família de instruções 0x6Xh
    &iadd, &ladd, &fadd, &dadd, &isub, &lsub, &fsub, &dsub,
    &imul, &lmul, &fmul, &dmul, &idiv, &_ldiv, &fdiv, &ddiv,
    
    //Oitava família de instruções 0x7Xh
    &irem, &lrem, &frem, &_drem, &ineg, &lneg, &fneg, &dneg,
    &ishl, &lshl, &ishr, &lshr, &iushr, &lushr, &iand, &land,
    
    //Nona família de instruções 0x8Xh
    &ior, &lor, &ixor, &lxor, &iinc, &i2l, &i2f, &i2d,
    &l2i, &l2f, &l2d, &f2i, &f2l, &f2d, &d2i, &_d2i,
    
    //Décima família de instruções 0x9Xh
    &d2f, &i2b, &i2c, &i2s, &lcmp, &fcmpl, &fcmpg, &dcmpl,
    &dcmpg, &ifeq, &ifne, &iflt, &ifge, &ifgt, &ifle, &if_icmpeq,
    
    //Décima primeira família de instruções 0xAXh
    &if_icmpne, &if_icmplt, &if_icmpge, &if_icmpgt, &if_icmple, &if_acmpeg, &if_acmpne, &_goto,
    &jsr, &ret, &table_switch, &lookup_switch, &ireturn, &lreturn, &freturn, &dreturn,
    
    //Décima segunda família de instruções 0xBXh
    &areturn, &_return, &getstatic, &putstatic, &getfield, &putfield, &invokevirtual, &invokespecial,
    &invokestatic, &invokeInterface, NULL, &new, &newArray, &anewArray, &arrayLength, &athrow,
    
    //Décima terceira família de instruções 0xCXh
    &checkLast, &instanceOf, &monitorEnter, &monitorExit, &wide, &multiNewArray, &ifNull, &ifNonNull,
    &goto_w, &jsr_w, &breakPoint,NULL, NULL, NULL, NULL, NULL,
    
    //Décima quarta família de instruções 0xDXh
    NULL, NULL, NULL, NULL,NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL,NULL, NULL, NULL, NULL,
    
    //Décima quinta família de instruções 0xEXh
    NULL, NULL, NULL, NULL,NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL,NULL, NULL, NULL, NULL,
    
    //Décima sexta família de instruções 0xFXh
    NULL, NULL, NULL, NULL,NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL,NULL, NULL, &impdep1, &impdep2
};
void * op_num_args_table[256]={
    //Primeira família de instruções 0x0Xh
    
    //Segunda família de instruções 0x1Xh
    
    //Terceira família de instruções 0x2Xh
    
    //Quarta família de instruções 0x3Xh
    
    //Quinta família de instruções 0x4Xh
    
    //Sexta família de instruções 0x5Xh
    
    //Sétima família de instruções 0x6Xh
    
    //Oitava família de instruções 0x7Xh
    
    //Nona família de instruções 0x8Xh
    
    //Décima família de instruções 0x9Xh
    
    //Décima primeira família de instruções 0xAXh
    
    //Décima segunda família de instruções 0xBXh
    
    //Décima terceira família de instruções 0xCXh
    
    //Décima quarta família de instruções 0xDXh
    
    //Décima quinta família de instruções 0xEXh
    
    //Décima sexta família de instruções 0xFXh
    
};

//Busca operação por opcode
void * get_op(u1 index){
        return op_table[index];
}
