#include "op_stack.hpp"

#ifdef __cplusplus
extern "C" {
#endif 

extern int _push(void *, char, void *);
extern int _push_w(void *, char, void *);
extern int _pop(void *, void *);

extern int _iadd(void *);
extern int _isub(void *);
extern int _imul(void *);
extern int _idiv(void *);


#ifdef __cplusplus
}
#endif

//#define DEV

/* CONSTRUTOR */
OperandStack::OperandStack(u2 m) {
	size = 0;
	max  = m;
	stack = new Operand[max];
	top = &stack[0];
}

/* OPERACOES DO BYTE CODE */
void OperandStack::bipush(u1 in) {
	u4 temp = 0;
	temp = in;
	if(in & 0x80)
		temp |= 0xFFFFFF00;
	push_i(temp);
}

void OperandStack::sipush(u1 high, u1 low) {
	u4 temp = 0;
	temp = high;
	temp <<= 8;
	temp |= low;
	if(high & 0x80)
		temp |= 0xFFFF0000;
	push_i(temp);
}

void OperandStack::iconst_m1() {
	push_i(-1);
}
void OperandStack::iconst_0() {
	push_i(0);
}
void OperandStack::iconst_1() {
	push_i(1);
}
void OperandStack::iconst_2() {
	push_i(2);
}
void OperandStack::iconst_3() {
	push_i(3);
}
void OperandStack::iconst_4() {
	push_i(4);
}
void OperandStack::iconst_5() {
	push_i(5);
}

void OperandStack::fconst_0() {
	push_f(0.0F);
}
void OperandStack::fconst_1() {
	push_f(1.0F);
}
void OperandStack::fconst_2() {
	push_f(2.0F);
}

void OperandStack::lconst_0() {
	push_l(0L);
}
void OperandStack::lconst_1() {
	push_l(1L);
}

void OperandStack::dconst_0() {
	push_d(0.0D);
}
void OperandStack::dconst_1() {
	push_d(1.0D);
}

int OperandStack::iadd() {
	if(size < 2)
		return 0;
	top--;
	_iadd(top);
	size--;
}
int OperandStack::isub() {
	if(size < 2)
		return 0;
	top--;
	_isub(top);
	size--;
}

int OperandStack::imul() {
	if(size < 2)
		return 0;
	top--;
	_imul(top);
	size--;
}

int OperandStack::idiv() {
	if(size < 2)
		return 0;
	top--;
	_idiv(top);
	size--;
}

int OperandStack::dup() {
	if(size < 1)
		return 0;
	Operand temp;
	temp = *(top-1);
	push(temp);
}




/* OPERACAO GERAL */
int OperandStack::push(Operand op) {
#ifdef DEV
	printf("\npush\n");
	if(size == max) {
		printf("pilha cheio\n");
		return 0;
	}
#else
	if(size == max)
		return 0;
#endif
	*top = op;
	top++;
	size++;
	return 1;
}

int OperandStack::push_i(int32_t i) {
#ifdef DEV
	printf("\npush\n");
	if(size == max) {
		printf("pilha cheio\n");
		return 0;
	}
#else
	if(size == max)
		return 0;
#endif
	_push(top, TYPE_INT, &i);
	top++;
	size++;
	return 1;
}

int OperandStack::push_f(float f) {
#ifdef DEV
	printf("\npush\n");
	if(size == max) {
		printf("pilha cheio\n");
		return 0;
	}
#else
	if(size == max)
		return 0;
#endif
	_push(top, TYPE_FLOAT, &f);
	top++;
	size++;
	return 1;
}

int OperandStack::push_l(int64_t l) {
	if(size == max)
		return 0;

	_push_w(top, TYPE_LONG, &l);
	top += 2;
	size += 2;
	return 1;
}

int OperandStack::push_d(double d) {
	if(size == max)
		return 0;

	_push_w(top, TYPE_DOUBLE, &d);
	top += 2;
	size += 2;
	return 1;
}

int OperandStack::pop_i(void *v) {
	if(size == 0)
		return 0;

	top--;
	_pop(top, v);
	size--;
	return 1;
}

int OperandStack::pop(Operand *op) {
#ifdef DEV
	printf("\npop\n");
	if(size == 0) {
		printf("pilha vazio\n");
		return 0;
	}
#else
	if(size == 0)
		return 0;
#endif
	top--;
	*top = *op;
	size--;
	return 1;
}

void OperandStack::print() {
	printf("max: %d\n", max);
	printf("size: %d\n", size);
	
	for(int i=size-1; i>=0; i--) {
		printf("\t");
		stack[i].print();
	}
	printf("\tbase\n");

}


