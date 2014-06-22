#ifndef JAVAVM
#define JAVAVM

#include <stdio.h>

void nop();
void aconst_null();
void iconst_m1();
void iconst_0();
void iconst_1();
void iconst_2();
void iconst_3();
void iconst_4();
void iconst_5();
void lconst_0();
void lconst_1();
void fconst_0();
void fconst_1();
void fconst_2();
void dconst_0();
void dconst_1();
void bipush();
void sipush();
void ldc();
void ldc_w();
void ldc2_w();
void iload();
void lload();
void fload();
void dload();
void aload();
void iload_0();
void iload_1();
void iload_2();
void iload_3();
void lload_0();
void lload_1();
void lload_2();
void lload_3();
void fload_0();
void fload_1();
void fload_2();
void fload_3();
void dload_0();
void dload_1();
void dload_2();
void dload_3();
void aload_0();
void aload_1();
void aload_2();
void aload_3();
void iaload();
void laload();
void faload();
void daload();
void aaload();
void baload();
void caload();
void saload();
void istore();
void lstore();
void fstore();
void dstore();
void astore();
void istore_0();
void istore_1();
void istore_2();
void istore_3();
void lstore_0();
void lstore_1();
void lstore_2();
void lstore_3();
void fstore_0();
void fstore_1();
void fstore_2();
void fstore_3();
void dstore_0();
void dstore_1();
void dstore_2();
void dstore_3();
void astore_0();
void astore_1();
void astore_2();
void astore_3();
void iastore();
void lastore();
void fastore();
void dastore();
void aastore();
void bastore();
void castore();
void sastrore();
void pop();
void pop2();
void dup();
void dup_x1();
void dup_x2();
void dup2();
void dup2_x1();
void dup2_x2();
void swap();
void iadd();
void ladd();
void fadd();
void dadd();
void isub();
void lsub();
void fsub();
void dsub();
void imul();
void lmul();
void fmul();
void dmul();
void idiv();
void ldiv();
void fdiv();
void ddiv();
void irem();
void lrem();
void frem();
void drem();
void ineg();
void lneg();
void fneg();
void dneg();
void ishl();
void lshl();
void ishr();
void lshr();
void iushr();
void lushr();
void iand();
void land();
void ior();
void lor();
void ixor();
void lxor();
void iinc();
void i2l();
void i2f();
void i2d();
void l2i();
void l2f();
void l2d();
void f2i();
void f2l();
void f2d();
void d2i();
void d2l();
void d2f();
void i2b();
void i2c();
void i2s();
void lcmp();
void fcmpl();
void fcmpg();
void dcmpl();
void dcmpg();
void ifeq();
void ifne();
void iflt();
void ifge();
void ifgt();
void ifle();
void if_icmpeq();
void if_icmpne();
void if_icmplt();
void if_icmpge();
void if_cmpgt();
void if_icmple();
void if_acmpeq();
void if_acmpne();
void op_goto();
void jsr();
void ret();
void tableswitch();
void lookupswitch();
void ireturn();
void lreturn();
void freturn();
void dreturn();
void areturn();
void op_return();
void getstatic();
void putstatic();
void getfield();
void putfield();
void invokevirtual();
void invokespecial();
void invokestatic();
void invokeinterface();
void invokedynamic();
void op_new();
void newarray();
void anewarray();
void arraylength();
void athrow();
void checkcast();
void instanceof();
void monitorenter();
void monitorexit();
void wide();
void multianewarray();
void ifnull();
void ifnonnull();
void goto_w();
void jsr_w();
void breakpoint();
void impdep();
void impdep2();

void (*op[256]) () = {
	nop, aconst_null, 
	iconst_m1, iconst_0, iconst_1, iconst_2, iconst_3, iconst_4, iconst_5, 
	lconst_0, lconst_1, fconst_0, fconst_1, fconst_2, dconst_0, dconst_1, 
	bipush, sipush, ldc, ldc_w, ldc2_w, 
	iload, lload, fload, dload, aload, 
	iload_0, iload_1, iload_2, iload_3, 
	lload_0, lload_1, lload_2, lload_3, 
	fload_0, fload_1, fload_2, fload_3, 
	dload_0, dload_1, dload_2, dload_3, 
	aload_0, aload_1, aload_2, aload_3, 
	iaload, laload, faload, daload, aaload, baload, caload, saload, 
	istore, lstore, fstore, dstore, astore, 
	istore_0, istore_1, istore_2, istore_3, 
	lstore_0, lstore_1, lstore_2, lstore_3, 
	fstore_0, fstore_1, fstore_2, fstore_3, 
	dstore_0, dstore_1, dstore_2, dstore_3, 
	astore_0, astore_1, astore_2, astore_3, 
	iastore, lastore, fastore, dastore, aastore, bastore, castore, sastrore, 
	pop, pop2, dup, dup_x1, dup_x2, dup2, dup2_x1, dup2_x2, swap, 
	iadd, ladd, fadd, dadd, 
	isub, lsub, fsub, dsub, 
	imul, lmul, fmul, dmul, 
	idiv, ldiv, fdiv, ddiv, 
	irem, lrem, frem, drem, 
	ineg, lneg, fneg, dneg, 
	ishl, lshl, ishr, lshr, iushr, lushr, 
	iand, land, ior, lor, ixor, lxor, iinc, 
	i2l, i2f, i2d, l2i, l2f, l2d, f2i, f2l, f2d, d2i, d2l, d2f, i2b, i2c, i2s, 
	lcmp, fcmpl, fcmpg, dcmpl, dcmpg, ifeq, ifne, iflt, ifge, ifgt, ifle, 
	if_icmpeq, if_icmpne, if_icmplt, if_icmpge, if_cmpgt, if_icmple, if_acmpeq, if_acmpne, 
	op_goto, jsr, ret, tableswitch, lookupswitch, 
	ireturn, lreturn, freturn, dreturn, areturn, op_return, 
	getstatic, putstatic, getfield, putfield, 
	invokevirtual, invokespecial, invokestatic, invokeinterface, invokedynamic, 
	op_new, newarray, anewarray, arraylength, athrow, 
	checkcast, instanceof, monitorenter, monitorexit, 
	wide, multianewarray, ifnull, ifnonnull, goto_w, jsr_w, breakpoint,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, impdep, impdep2
};



#endif
