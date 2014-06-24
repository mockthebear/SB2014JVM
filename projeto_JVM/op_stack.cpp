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
extern int _irem(void *);
extern int _ineg(void *);


#ifdef __cplusplus
}
#endif

//#define DEV

/* CONSTRUTOR */
OperandStack::OperandStack(u2 m) {
	size = 0;
	max  = m;
	stack = (Operand *) calloc(max+1, sizeof(Operand));
	top = &stack[0];
}

/* OPERACOES DO BYTE CODE */
void OperandStack::bipush(u1 in) {
	u4 value = 0;
	Operand op;
	
	value = in;
	if(in & 0x80)
		value |= 0xFFFFFF00;
	op.set_byte(TYPE_INT, value);
	push(op);
}

void OperandStack::sipush(u2 in) {
	u4 value = 0;
	Operand op;
	
	value= in;
	if(in & 0x8000)
		value |= 0xFFFF0000;
	op.set_byte(TYPE_INT, value);
	push(op);
}

void OperandStack::iconst(int32_t i) {
	Operand op;
	
	op.set_value(TYPE_INT, &i);
	push(op);
}

void OperandStack::fconst(float f) {
	Operand op;
	
	op.set_value(TYPE_FLOAT, &f);
	push(op);
}

void OperandStack::lconst(int32_t l) {
	Operand op;
	
	op.set_byte(TYPE_LONG, 0x0);
	push(op);
	
	op.set_value(TYPE_LONG, &l);
	push(op);
}

void OperandStack::dconst() {
	
}

void OperandStack::aconst_null() {
	Operand op;
	
	op.set_byte(TYPE_REF, 0x0);
	push(op);
}

void OperandStack::dup() {
	if(size < 1) {
		printf("Error  :op_stack.dup\n");
		exit(0);
	}
	Operand temp;
	
	temp = *(top);
	push(temp);
}

void OperandStack::dup2() {
	if(size < 2) {
		printf("Error  :op_stack.dup2\n");
		exit(0);
	}
	Operand temp1;
	Operand temp2;
	
	temp1 = *(top-1);
	temp2 = *(top);
	push(temp1);
	push(temp2);
}

void OperandStack::swap() {
	if(size < 2) {
		printf("Error  :op_stack.swap\n");
		exit(0);
	}
	Operand temp;
	
	temp = *(top-1);
	*(top-1) = *top;
	*top = temp;
}

int OperandStack::ifzero() {
	if(size < 1) {
		printf("Error  :op_stack.ifzero\n");
		exit(0);
	}
	Operand op;
	int result = 0;
	
	op = pop();
	if(op.bytes == 0x0)
		result = 1;
	return result;
}

int OperandStack::ifgt() {
	if(size < 1) {
		printf("Error  :op_stack.ifgt\n");
		exit(0);
	}
	Operand op;
	int result = 0;
	
	op = pop();
	int itest = op.to_int();
	if(itest > 0)
		result = 1;
	return 0;
}

int OperandStack::iflt() {
	if(size < 1) {
		printf("Error  :op_stack.iflt\n");
		exit(0);
	}
	Operand op;
	int result = 0;
	
	op = pop();
	int itest = op.to_int();
	if(itest < 0)
		result = 1;
	return 0;
}

int OperandStack::if_cmpeq(u4 type) {
	if(size < 2) {
		printf("Error  :op_stack.if_cmpeq\n");
		exit(0);
	}
	Operand op1, op2;
	int result = 0;
	op2 = pop();
	op1 = pop();
	if( (op1.type != type) || (op2.type != type) ) {
		printf("Error type int or ref :op_stack.f_icmpeq\n");
		exit(0);
	}
	if(op1.bytes == op2.bytes)
		result = 1;
	return result;
}

int OperandStack::if_icmpgt() {
	if(size < 2) {
		printf("Error  :op_stack.if_icmpgt\n");
		exit(0);
	}
	Operand op1, op2;
	int result = 0;
	
	op2 = pop();
	op1 = pop();
	if( (op1.type != TYPE_INT) || (op2.type != TYPE_INT) ) {
		printf("Error type not int: :op_stack.if_icmpgt\n");
		exit(0);
	}
	int int1 = op1.to_int();
	int int2 = op2.to_int();
	if(int1 > int2)
		result = 1;
	return result;
}

int OperandStack::if_icmplt() {
	if(size < 2) {
		printf("Error  :op_stack.if_icmplt\n");
		exit(0);
	}
	Operand op1, op2;
	int result = 0;
	
	op2 = pop();
	op1 = pop();
	if( (op1.type != TYPE_INT) || (op2.type != TYPE_INT) ) {
		printf("Error type not int: :op_stack.if_icmplt\n");
		exit(0);
	}
	int int1 = op1.to_int();
	int int2 = op2.to_int();
	if(int1 < int2)
		result = 1;
	return result;
}

void OperandStack::iadd() {
	if(size < 2) {
		printf("Error  :op_stack.iadd\n");
		exit(0);
	}
	_iadd(top);
	top--;
	size--;
}

void OperandStack::isub() {
	if(size < 2) {
		printf("Error  :op_stack.isub\n");
		exit(0);
	}
	_isub(top);
	top--;
	size--;
}

void OperandStack::imul() {
	if(size < 2) {
		printf("Error  :op_stack.imul\n");
		exit(0);
	}
	_imul(top);
	top--;
	size--;
}

void OperandStack::idiv() {
	if(size < 2) {
		printf("Error  :op_stack.idiv\n");
		exit(0);
	}
	_idiv(top);
	top--;
	size--;
}

void OperandStack::irem() {
	if(size < 2) {
		printf("Error  :op_stack.irem\n");
		exit(0);
	}
	_irem(top);
	top--;
	size--;
}

void OperandStack::ineg() {
	if(size < 1) {
		printf("Error  :op_stack.ineg\n");
		exit(0);
	}
	_ineg(top);
}

/* OPERACAO GERAL */
void OperandStack::push(Operand op) {
	if(size == max) {
		printf("Error stack over :op_stack.push\n");
		exit(0);
	}
	top++;
	*top = op;
	size++;
}

Operand OperandStack::pop() {
	if(size == 0) {
		printf("Error stack empty :op_stack.pop\n");
		exit(0);
	}
	Operand op;
	
	op = *top;
	top--;
	size--;
	return op;
}

Operand *OperandStack::pop_param(int count) {
	if(size == 0) {
		printf("Error stack empty :op_stack.pop_param\n");
		exit(0);
	}
	Operand *op;
	
	top -= (count-1);
	op = top;
	top--;
	size -= count;
	return op;
}

void OperandStack::print() {
	printf(">OperandStack\n");
	printf("max: %d ", max);
	printf("size: %d\n", size);
	
	for(int i=size-1; i>=0; i--) {
		printf("\t");
		stack[i].print();
	}
	printf("\tbase\n");

}


void OperandStack::print_min() {
	printf(">Operand Stack\n");
	printf("  max: %d ", max);
	printf("size: %d\n", size);
	printf("  ");
	for(u2 i=1; i<=size; i++) {
		printf("[%d] ",i);
		stack[i].print_min();
	}
	printf("\n");
}
