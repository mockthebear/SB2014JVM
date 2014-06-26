#include "op_stack.hpp"

#ifdef __cplusplus
extern "C" {
#endif 

extern void _to_value64(void *, u4, u4);

extern void _iadd(void *);
extern void _isub(void *);
extern void _imul(void *);
extern void _idiv(void *);
extern void _irem(void *);
extern void _ineg(void *);

extern void _ladd(void *);
extern void _lneg(void *);

extern void _fadd(void *);
extern void _fsub(void *);
extern void _fmul(void *);
extern void _fdiv(void *);
extern void _frem(void *);
extern void _fneg(void *);

extern void _dadd(void *);
extern void _dsub(void *);
extern void _dmul(void *);
extern void _ddiv(void *);
extern void _drem(void *);
extern void _dneg(void *);

#ifdef __cplusplus
}
#endif

int64_t to_long(u4 high, u4 low);
double to_double(u4 high, u4 low);

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
	
	op.set_high(TYPE_LONG, &l);
	push(op);
	
	op.set_low(TYPE_LONG, &l);
	push(op);
}

void OperandStack::dconst(double d) {
	Operand op;
	
	op.set_high(TYPE_DOUBLE, &d);
	push(op);
	
	op.set_low(TYPE_DOUBLE, &d);
	push(op);
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
	int32_t itest = op.to_int();
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
	int32_t itest = op.to_int();
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
	int32_t int1 = op1.to_int();
	int32_t int2 = op2.to_int();
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
	int32_t int1 = op1.to_int();
	int32_t int2 = op2.to_int();
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
	if(top->bytes == 0x0) {
		printf("Excecao de divisao por zero\n");
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

void OperandStack::ladd(){
	if(size < 4) {
		printf("Error  :op_stack.ladd\n");
		exit(0);
	}
	_ladd(top);
	top-=2;
	size-=2;
}

void OperandStack::lsub(){
	if(size < 4) {
		printf("Error  :op_stack.lsub\n");
		exit(0);
	}
	lneg();
	ladd();
}

void OperandStack::lmul(){
	if(size < 4) {
		printf("Error  :op_stack.lmul\n");
		exit(0);
	}
    Operand opL, opH;
	
    opL = pop();
    opH = pop();//multiplicador
    
	int64_t resultado = to_long( (top-1)->bytes, (top)->bytes ) * to_long(opH.bytes, opL.bytes);
	(top-1)->set_high(TYPE_LONG, &resultado);
	top->set_low(TYPE_LONG, &resultado);
}

void OperandStack::ldiv(){
	if(size < 4) {
		printf("Error  :op_stack.ldiv\n");
		exit(0);
	}
    Operand opL, opH;
	
    opL = pop();
    opH = pop();//divisor
    
	if( (opH.bytes == 0x0) && (opL.bytes==0x0) ) {
		printf("Excecao de divisao por zero\n");
		exit(0);
	}
	int64_t resultado = to_long( (top-1)->bytes, (top)->bytes ) / to_long(opH.bytes, opL.bytes);
	(top-1)->set_high(TYPE_LONG, &resultado);
	top->set_low(TYPE_LONG, &resultado);
}

void OperandStack::lrem(){
	if(size < 4) {
		printf("Error  :op_stack.lrem\n");
		exit(0);
	}
    Operand opL, opH;
	
    opL = pop();
    opH = pop();
    
	if( (opH.bytes == 0x0) && (opL.bytes==0x0) ) {
		printf("Excecao de divisao por zero\n");
		exit(0);
	}
	int64_t resultado = to_long( (top-1)->bytes, (top)->bytes ) % to_long(opH.bytes, opL.bytes);
	(top-1)->set_high(TYPE_LONG, &resultado);
	top->set_low(TYPE_LONG, &resultado);
}

void OperandStack::lneg(){
	if(size < 2) {
		printf("Error  :op_stack.lneg\n");
		exit(0);
	}
	_lneg(top);
}

void OperandStack::fadd(){
    if(size < 2) {
		printf("Error  :op_stack.fadd\n");
		exit(0);
	}
	_fadd(top);
	top--;
	size--;
}

void OperandStack::fsub(){
    if(size < 2) {
		printf("Error  :op_stack.fsub\n");
		exit(0);
	}
	_fsub(top);
	top--;
	size--;
}

void OperandStack::fmul(){
     if(size < 2) {
		printf("Error  :op_stack.fmul\n");
		exit(0);
	}
	_fmul(top);
	top--;
	size--;
}

void OperandStack::fdiv(){
    if(size < 2) {
		printf("Error  :op_stack.fdiv\n");
		exit(0);
	}
	if(top->bytes == 0x0) {
		printf("Excecao de divisao por zero\n");
		exit(0);
	}
	_fdiv(top);
	top--;
	size--;
}

void OperandStack::frem(){
    if(size < 2) {
		printf("Error  :op_stack.frem\n");
		exit(0);
	}
	if(top->bytes == 0x0) {
		printf("Excecao de divisao por zero\n");
		exit(0);
	}
	_frem(top);
	top--;
	size--;
}

void OperandStack::fneg(){
	if(size < 2) {
		printf("Error  :op_stack.fneg\n");
		exit(0);
	}
	_fneg(top);
	top--;
	size--;
}

void OperandStack::dadd(){
    if(size < 4) {
		printf("Error  :op_stack.dadd\n");
		exit(0);
	}
	_dadd(top);
	top-=2;
	size-=2;
}

void OperandStack::dsub(){
    if(size < 4) {
		printf("Error  :op_stack.dsub\n");
		exit(0);
	}
	_dsub(top);
	top-=2;
	size-=2;
}

void OperandStack::dmul(){
    if(size < 4) {
		printf("Error  :op_stack.dmul\n");
		exit(0);
	}
	_dmul(top);
	top-=2;
	size-=2;
}

void OperandStack::ddiv(){
    if(size < 4) {
		printf("Error  :op_stack.ddiv\n");
		exit(0);
	}
	if( ( (top-1)->bytes == 0x0 ) && (top->bytes==0x0) ) {
		printf("Excecao de divisao por zero\n");
		exit(0);
	}
	_ddiv(top);
	top-=2;
	size-=2;
}

void OperandStack::drem(){
    if(size < 4) {
		printf("Error  :op_stack.drem\n");
		exit(0);
	}
	if( ( (top-1)->bytes == 0x0 ) && (top->bytes==0x0) ) {
		printf("Excecao de divisao por zero\n");
		exit(0);
	}
	_drem(top);
	top-=2;
	size-=2;
}

void OperandStack::dneg(){
	if(size < 2) {
		printf("Error  :op_stack.dneg\n");
		exit(0);
	}
	_dneg(top);
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

int64_t to_long(u4 high, u4 low) {
	int64_t l = 0L;
	
	_to_value64(&l, high, low);
	return l;
}

double to_double(u4 high, u4 low) {
	double d = 0.0;
	
	_to_value64(&d, high, low);
	return d;
}

void OperandStack::dup_x1(){
    Operand op1, op2;
    op1 = pop();
    op2 = pop();
    push(op1);
    push(op2);
    push(op1);
}

void OperandStack::dup2_x1(){
    Operand op1, op2, op3;
    op1 = pop();
    op2 = pop();
    op3 = pop();
    
    
}

void OperandStack::dup_x2(){
    Operand op1, op2, op3;
    op1 = pop();
    op2 = pop();
    op3 = pop();
    
    push(op2);
    push(op1);
    push(op3);
    push(op2);
    push(op1);
}

void OperandStack::dup2_x2(){
    Operand op1, op2, op3, op4;
    op1 = pop();
    op2 = pop();
    op3 = pop();
    
    push(op2);
    push(op1);
    push(op4);
    push(op3);
    push(op2);
    push(op1);
}

 
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