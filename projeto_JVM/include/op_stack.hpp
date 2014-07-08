#ifndef OPERAND_STACK
#define OPERAND_STACK

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "definition.hpp"
#include "exception.hpp"
#include "operand.hpp"

class OperandStack {
public:
	Operand *stack;
	Operand *top;
	u4 max;
	u4 size;

	OperandStack(u2);

    void clear();

	void bipush(u1);
	void sipush(u2);

	void iconst(int32_t i);
	void fconst(float f);
	void lconst(int64_t l);
	void dconst(double d);
	void aconst_null();

	void dup();
	void dup_x1();
	void dup_x2();
	void dup2();
	void dup2_x1();
	void dup2_x2();
	void swap();

	int ifzero();
	int ifgt();
	int iflt();
    int ifle();
    int ifne();

    int if_icmpge();
	int if_icmpgt();
    int if_icmpne();
	int if_icmplt();
    int if_icmple();
    int if_acmpeq();
    int if_acmpne();
    int if_icmpeq();

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

	void fcmpg();
	void fcmpl();
	void dcmpg();
	void dcmpl();
	void lcmp();

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

	void push(Operand);
	Operand pop();
	Operand *pop_param(int);

	int32_t pop_i();
	int64_t pop_l();
	float pop_f();
	double pop_d();
	
	void print();
};

#endif
