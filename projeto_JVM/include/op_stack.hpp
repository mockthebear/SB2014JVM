#ifndef OPERAND_STACK
#define OPERAND_STACK

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "definition.hpp"
#include "operand.hpp"

class OperandStack {
public:
	Operand *stack;
	Operand *top;
	u4 max;
	u4 size;

	OperandStack(u2);
	
	void bipush(u1);
	void sipush(u2);
	
	
	void iconst(int32_t i);
	void fconst(float f);
	void lconst(int64_t l);
	void dconst(double d);
	void aconst_null();

	void dup();
	void dup2();
	void swap();
	
	void dup_x1();
	void dup2_x1();
	void dup_x2();
	void dup2_x2();
	
	
	int ifzero();
	int ifgt();
	int iflt();
	
	int if_cmpeq(u4);
	int if_icmpgt();
	int if_icmplt();
	
	
	void iadd();
	void isub();
	void imul();
	void idiv();
	void irem();
	void ineg();
	
	void ladd();
	void lsub();
	void lmul();
	void ldiv();
	void lrem();
	void lneg();
	
	void fadd();
	void fsub();
	void fmul();
	void fdiv();
	void frem();
	void fneg();
	
	void dadd();
	void dsub();
	void dmul();
	void ddiv();
	void drem();
	void dneg();
	
	void i2l();
	void i2f();
	void i2d();
	void i2b();
	void i2c();
	void i2s();
	
	void l2i();
	void l2f();
	void l2d();
	
	void f2i();
	void f2l();
	void f2d();
	
	void d2i();
	void d2l();
	void d2f();
	/*
	
	fcmpg
	fcmpl
	dcmpg
	dcmpl
	lcmp
	
	iinc
	
	ishl
	lshl
	ishr
	lshr
	iushr
	lushr
	iand
	land
	ior
	lor
	ixor
	lxor
	*/
	
	void push(Operand);
	Operand pop();
	Operand *pop_param(int);
	
	void print();
	void print_min();
};

#endif
