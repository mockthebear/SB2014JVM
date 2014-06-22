#ifndef OPERAND_STACK
#define OPERAND_STACK

#include <stdio.h>
#include <stdint.h>

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
	void sipush(u1, u1);
	
	void iconst_m1();
	void iconst_0();
	void iconst_1();
	void iconst_2();
	void iconst_3();
	void iconst_4();
	void iconst_5();
	
	void fconst_0();
	void fconst_1();
	void fconst_2();
	
	void lconst_0();
	void lconst_1();
	
	void dconst_0();
	void dconst_1();
	
	int iadd();
	int isub();
	int imul();
	int idiv();
	
	
	int dup();
	
	
	int push(Operand);
	int push_i(int32_t);
	int push_f(float);
	int push_l(int64_t);
	int push_d(double);
	int pop(Operand *);
	int pop_i(void *);
	
	void print();
};

#endif
