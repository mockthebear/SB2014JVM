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
	void lconst(int32_t l);
	void dconst();
	void aconst_null();

	void dup();
	void dup2();
	void swap();
	/*
	dup_x1
	dup2_x1
	dup_x2
	dup2_x2
	*/
	
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
	/*
	int ladd();
	int lsub();
	int lmul();
	int ldiv();
	int fadd();
	int fsub();
	int fmul();
	int fdiv();
	int dadd();
	int dsub();
	int dmul();
	int ddiv();
	
	
	void lrem();
	void lneg();
	void frem();
	void fneg();
	void drem();
	void dneg();
	
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
