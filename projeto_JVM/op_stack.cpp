#include "op_stack.hpp"

#ifdef __cplusplus
extern "C" {
#endif

extern void __to_value64(void *, u4, u4);

extern void __iadd(void *);
extern void __isub(void *);
extern void __imul(void *);
extern void __idiv(void *);
extern void __irem(void *);
extern void __ineg(void *);

extern void __ladd(void *);
extern void __lneg(void *);

extern void __fadd(void *);
extern void __fsub(void *);
extern void __fmul(void *);
extern void __fdiv(void *);
extern void __frem(void *);
extern void __fneg(void *);

extern void __dadd(void *);
extern void __dsub(void *);
extern void __dmul(void *);
extern void __ddiv(void *);
extern void __opDrem(void * );
//extern void __drem(void *); conflito no linux features.h:374->stdio.h:27
extern void __dneg(void *);

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
void OperandStack::clear() {
	top = &stack[0];
	size = 0;
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

void OperandStack::lconst(int64_t l) {
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

int OperandStack::ifle() {
    if(size < 1) {
        printf("Error  :op_stack.ifle\n");
        exit(0);
    }
    Operand op;
    int result = 0;

    op = pop();
    int32_t itest = op.to_int();
    if(itest <= 0)
        result = 1;
    return 0;
}

int OperandStack::ifne() {
    if(size < 1) {
        printf("Error  :op_stack.ifne\n");
        exit(0);
    }
    Operand op;
    int result = 0;

    op = pop();
    int32_t itest = op.to_int();
    if(itest != 0)
        result = 1;
    return 0;
}

int OperandStack::if_icmpeq() {
	if(size < 2) {
		printf("Error  :op_stack.if_icmpeq\n");
		exit(0);
	}
	Operand op1, op2;
	int result = 0;
	op2 = pop();
	op1 = pop();
	if( (op1.type != TYPE_INT) || (op2.type != TYPE_INT) ) {
		printf("Error type int or ref :op_stack.if_icmpeq\n");
		exit(0);
	}
	if(op1.bytes == op2.bytes)
		result = 1;
	return result;
}

int OperandStack::if_icmpne() {
    if(size < 2) {
        printf("Error  :op_stack.if_icmpeq\n");
        exit(0);
    }
    Operand op1, op2;
    int result = 0;
    op2 = pop();
    op1 = pop();
    if( (op1.type != TYPE_INT) || (op2.type != TYPE_INT) ) {
        printf("Error type int or ref :op_stack.if_icmpne\n");
        exit(0);
    }
    if(op1.bytes != op2.bytes)
        result = 1;
    return result;
}

int OperandStack::if_icmpge() {
    if(size < 2) {
        printf("Error  :op_stack.if_icmpgt\n");
        exit(0);
    }
    Operand op1, op2;
    int result = 0;

    op2 = pop();
    op1 = pop();
    if( (op1.type != TYPE_INT) || (op2.type != TYPE_INT) ) {
        printf("Error type not int: :op_stack.if_icmpge\n");
        exit(0);
    }
    int32_t int1 = op1.to_int();
    int32_t int2 = op2.to_int();
    if(int1 >= int2)
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

int OperandStack::if_icmple() {
    if(size < 2) {
        printf("Error  :op_stack.if_icmplt\n");
        exit(0);
    }
    Operand op1, op2;
    int result = 0;

    op2 = pop();
    op1 = pop();
    if( (op1.type != TYPE_INT) || (op2.type != TYPE_INT) ) {
        printf("Error type not int: :op_stack.if_icmple\n");
        exit(0);
    }
    int32_t int1 = op1.to_int();
    int32_t int2 = op2.to_int();
    if(int1 <= int2)
        result = 1;
    return result;
}

int OperandStack::if_acmpeq() {
    if(size < 2) {
        printf("Error  :op_stack.if_icmplt\n");
        exit(0);
    }
    Operand op1, op2;
    int result = 0;

    op2 = pop();
    op1 = pop();
    if( (op1.type != TYPE_REF) || (op2.type != TYPE_REF) ) {
        printf("Error type not int: :op_stack.if_acmpeq\n");
        exit(0);
    }
    int32_t int1 = op1.to_int();
    int32_t int2 = op2.to_int();
    if(int1 == int2)
        result = 1;
    return result;
}

int OperandStack::if_acmpne() {
    if(size < 2) {
        printf("Error  :op_stack.if_acmpne\n");
        exit(0);
    }
    Operand op1, op2;
    int result = 0;

    op2 = pop();
    op1 = pop();
    if( (op1.type != TYPE_REF) || (op2.type != TYPE_REF) ) {
        printf("Error type not int: :op_stack.if_icmplt\n");
        exit(0);
    }
    int32_t int1 = op1.to_int();
    int32_t int2 = op2.to_int();
    if(int1 != int2)
        result = 1;
    return result;
}

void OperandStack::iadd() {
	if(size < 2) {
		printf("Error  :op_stack.iadd\n");
		exit(0);
	}
	__iadd(top);
	top--;
	size--;
}

void OperandStack::isub() {
	if(size < 2) {
		printf("Error  :op_stack.isub\n");
		exit(0);
	}
	__isub(top);
	top--;
	size--;
}

void OperandStack::imul() {
	if(size < 2) {
		printf("Error  :op_stack.imul\n");
		exit(0);
	}
	__imul(top);
	top--;
	size--;
}

void OperandStack::idiv() {
	if(size < 2) {
		printf("Error  :op_stack.idiv\n");
		exit(0);
	}
	if(top->bytes == 0x0) {
		exception("ArithmeticException: / by zero at OpStack.idiv");
	}
	__idiv(top);
	top--;
	size--;
}

void OperandStack::irem() {
	if(size < 2) {
		printf("Error  :op_stack.irem\n");
		exit(0);
	}
	if(top->bytes == 0x0) {
		exception("ArithmeticException: / by zero at OpStack.irem");
	}
	__irem(top);
	top--;
	size--;
}

void OperandStack::ineg() {
	if(size < 1) {
		printf("Error  :op_stack.ineg\n");
		exit(0);
	}
	__ineg(top);
}

void OperandStack::ladd(){
	if(size < 4) {
		printf("Error  :op_stack.ladd\n");
		exit(0);
	}
	__ladd(top);
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

    if((opL.type != TYPE_INT) || (opH.type != TYPE_INT) || ((top)->type != TYPE_INT) || ((top-1)->type != TYPE_INT) ) {
        printf("Error type not int: :op_stack.lmul\n");
        exit(0);
    }

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

    if((opL.type != TYPE_LONG) || (opH.type != TYPE_LONG) || ((top)->type != TYPE_LONG) || ((top-1)->type != TYPE_LONG) ) {
        printf("Error type not int: :op_stack.ldiv\n");
        exit(0);
    }

	if( (opH.bytes == 0x0) && (opL.bytes==0x0) ) {
		exception("ArithmeticException: / by zero at OpStack.ldiv");
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

    if((opL.type != TYPE_LONG) || (opH.type != TYPE_LONG) || ((top)->type != TYPE_LONG) || ((top-1)->type != TYPE_LONG) ) {
        printf("Error type not int: :op_stack.ldiv\n");
        exit(0);
    }

	if( (opH.bytes == 0x0) && (opL.bytes==0x0) ) {
		exception("ArithmeticException: / by zero at OpStack.lrem");
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
	__lneg(top);
}

void OperandStack::fadd(){
    if(size < 2) {
		printf("Error  :op_stack.fadd\n");
		exit(0);
	}
	__fadd(top);
	top--;
	size--;
}

void OperandStack::fsub(){
    if(size < 2) {
		printf("Error  :op_stack.fsub\n");
		exit(0);
	}
	__fsub(top);
	top--;
	size--;
}

void OperandStack::fmul(){
     if(size < 2) {
		printf("Error  :op_stack.fmul\n");
		exit(0);
	}
	__fmul(top);
	top--;
	size--;
}

void OperandStack::fdiv(){
    if(size < 2) {
		printf("Error  :op_stack.fdiv\n");
		exit(0);
	}
	if(top->bytes == 0x0) {
		exception("ArithmeticException: / by zero at OpStack.fdiv");
	}
	__fdiv(top);
	top--;
	size--;
}

void OperandStack::frem(){
    if(size < 2) {
		printf("Error  :op_stack.frem\n");
		exit(0);
	}
	if(top->bytes == 0x0) {
		exception("ArithmeticException: / by zero at OpStack.frem");
	}
	__frem(top);
	top--;
	size--;
}

void OperandStack::fneg(){
	if(size < 2) {
		printf("Error  :op_stack.fneg\n");
		exit(0);
	}
	__fneg(top);
	top--;
	size--;
}

void OperandStack::dadd(){
    if(size < 4) {
		printf("Error  :op_stack.dadd\n");
		exit(0);
	}
	__dadd(top);
	top-=2;
	size-=2;
}

void OperandStack::dsub(){
    if(size < 4) {
		printf("Error  :op_stack.dsub\n");
		exit(0);
	}
	__dsub(top);
	top-=2;
	size-=2;
}

void OperandStack::dmul(){
    if(size < 4) {
		printf("Error  :op_stack.dmul\n");
		exit(0);
	}
	__dmul(top);
	top-=2;
	size-=2;
}

void OperandStack::ddiv(){
    if(size < 4) {
		printf("Error  :op_stack.ddiv\n");
		exit(0);
	}
	if( ( (top-1)->bytes == 0x0 ) && (top->bytes==0x0) ) {
		exception("ArithmeticException: / by zero at OpStack.ddiv");
	}
	__ddiv(top);
	top-=2;
	size-=2;
}

void OperandStack::drem(){
    if(size < 4) {
		printf("Error  :op_stack.drem\n");
		exit(0);
	}
	if( ( (top-1)->bytes == 0x0 ) && (top->bytes==0x0) ) {
		exception("ArithmeticException: / by zero at OpStack.drem");
	}
	__opDrem(top);
	top-=2;
	size-=2;
}

void OperandStack::dneg(){
	if(size < 2) {
		printf("Error  :op_stack.dneg\n");
		exit(0);
	}
	__dneg(top);
}

void OperandStack::i2l() {
	if(size < 1) {
		printf("Error  :op_stack.i2l\n");
		exit(0);
	}
	Operand opH, opL;
	int32_t i;
	int64_t l;

	opH = pop();
	i = opH.to_int();
	l = (int64_t)i;
	opH.set_high(TYPE_LONG, &l);
	opL.set_low(TYPE_LONG, &l);
	push(opH);
	push(opL);
}

void OperandStack::i2f() {
	if(size < 1) {
		printf("Error  :op_stack.i2f\n");
		exit(0);
	}
	int32_t i;
	float f;

	i = top->to_int();
	f = (float) i;
	top->set_value(TYPE_FLOAT, &f);
}

void OperandStack::i2d() {
	if(size < 1) {
		printf("Error  :op_stack.i2d\n");
		exit(0);
	}
	Operand opH, opL;
	int32_t i;
	double d;

	opH = pop();
	i = opH.to_int();
	d = (double)i;
	opH.set_high(TYPE_DOUBLE, &d);
	opL.set_low(TYPE_DOUBLE, &d);
	push(opH);
	push(opL);
}

void OperandStack::i2b() {
	if(size < 1) {
		printf("Error  :op_stack.i2b\n");
		exit(0);
	}
	top->bytes &= 0xFF;
}

void OperandStack::i2c() {
	if(size < 1) {
		printf("Error  :op_stack.i2c\n");
		exit(0);
	}
	top->bytes &= 0xFF;
}

void OperandStack::i2s() {
	if(size < 1) {
		printf("Error  :op_stack.i2s\n");
		exit(0);
	}
	top->bytes &= 0xFFFF;
}

void OperandStack::l2i(){
    Operand opL = pop();

    if((opL.type != TYPE_LONG) || (top)->type != TYPE_LONG) {
        printf("Error type not long: :op_stack.l2i\n");
        exit(0);
    }

    pop();

    opL.type = TYPE_INT;
    push(opL);
}

void OperandStack::l2f(){
    Operand opL = pop();
    Operand opH = pop();

    if((opL.type != TYPE_LONG) || (opH.type != TYPE_LONG)) {
        printf("Error type not long: :op_stack.l2f\n");
        exit(0);
    }

    float l2f = (float)((int64_t)to_long(opH.bytes, opL.bytes));

    opL.type = TYPE_FLOAT;
    opL.bytes = (u4)l2f;
    push(opL);
}

void OperandStack::l2d(){
    Operand opL = pop();
    Operand opH = pop();

    if((opL.type != TYPE_LONG) || (opH.type != TYPE_LONG)) {
        printf("Error type not long: :op_stack.l2d\n");
        exit(0);
    }

    double l2d = (double)((int64_t)to_long(opH.bytes, opL.bytes));

    opL.type = TYPE_DOUBLE;
    opL.bytes = (u4)l2d;

    opH.type = TYPE_DOUBLE;
    opH.bytes = (u4)((uint64_t)l2d>>32);

    push(opH);
    push(opL);
}

void OperandStack::f2i(){
    Operand op1 = pop();

    if(op1.type != TYPE_FLOAT) {
        printf("Error type not float: :op_stack.f2i\n");
        exit(0);
    }

    op1.type = TYPE_INT;
    op1.bytes = (u4)((int32_t)op1.bytes);

    push(op1);
}

void OperandStack::f2l(){
    Operand opL = pop();
    Operand opH;

    if(opL.type != TYPE_FLOAT) {
        printf("Error type not float: :op_stack.f2l\n");
        exit(0);
    }

    int64_t f2l = (int64_t)((float)opL.bytes);

    opL.type = TYPE_LONG;
    opL.bytes = (u4)f2l;

    opH.type = TYPE_LONG;
    opH.bytes = (u4)((uint64_t)f2l>>32);

    push(opH);
    push(opL);
}

void OperandStack::f2d(){
    Operand opL = pop();
    Operand opH;

    if(opL.type != TYPE_FLOAT) {
        printf("Error type not float: :op_stack.f2d\n");
        exit(0);
    }

    double f2d = (double)((float)opL.bytes);

    opL.type = TYPE_DOUBLE;
    opL.bytes = (u4)f2d;

    opH.type = TYPE_DOUBLE;
    opH.bytes = (u4)((uint64_t)f2d>>32);

    push(opH);
    push(opL);
}

void OperandStack::d2i(){
    Operand opL = pop();
    Operand opH = pop();

    if((opL.type != TYPE_DOUBLE) || (opH.type != TYPE_DOUBLE)) {
        printf("Error type not double: :op_stack.d2i\n");
        exit(0);
    }

    opL.bytes = (u4)(int32_t)((double)to_long(opH.bytes, opL.bytes));

    opL.type = TYPE_INT;
    push(opL);
}

void OperandStack::d2l(){
    Operand opL = pop();
    Operand opH = pop();

    if((opL.type != TYPE_DOUBLE) || (opH.type != TYPE_DOUBLE)) {
        printf("Error type not double: :op_stack.d2l\n");
        exit(0);
    }

    long d2l = (long)((double)to_long(opH.bytes, opL.bytes));

    opL.type = TYPE_LONG;
    opL.bytes = (u4)d2l;

    opH.type = TYPE_LONG;
    opH.bytes = (u4)((uint64_t)d2l>>32);

    push(opH);
    push(opL);
}

void OperandStack::d2f(){
    Operand opL = pop();
    Operand opH = pop();

    if((opL.type != TYPE_DOUBLE) || (opH.type != TYPE_DOUBLE)) {
        printf("Error type not double: :op_stack.d2f\n");
        exit(0);
    }

    opL.bytes = (u4)(float)((double)to_long(opH.bytes, opL.bytes));

    opL.type = TYPE_FLOAT;
    push(opL);
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
	printf(">Operand Stack\n");
	printf("  max: %d ", max);
	printf("size: %d\n", size);
	printf("  ");
	for(u2 i=1; i<=size; i++) {
		printf("[%d] ",i);
		stack[i].print();
	}
	printf("\n");
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

void OperandStack::fcmpg(){
    Operand op1, op2, opReturn;
    opReturn.type = TYPE_INT;

    op1 = pop();
    op2 = pop();

    if((op1.type != TYPE_FLOAT) || (op2.type != TYPE_FLOAT)) {
        printf("Error type not double: :op_stack.fcmpg\n");
        exit(0);
    }

    if(isnan(op2.bytes) || isnan(op1.bytes)){
        opReturn.bytes =1;
        push(opReturn);
        return;
    }

    if((float)op2.bytes>(float)op1.bytes){
        opReturn.bytes = 1;
    }else if((float)op2.bytes<(float)op1.bytes){
        opReturn.bytes = -1;
    }else{
        opReturn.bytes = 0;
    }

    push(opReturn);

}

void OperandStack::fcmpl(){
    Operand op1, op2, opReturn;
    opReturn.type = TYPE_INT;

    op1 = pop();
    op2 = pop();

    if((op1.type != TYPE_FLOAT) || (op2.type != TYPE_FLOAT)) {
        printf("Error type not double: :op_stack.fcmpl\n");
        exit(0);
    }

    if(isnan(op2.bytes) || isnan(op1.bytes)){
        opReturn.bytes =-1;
        push(opReturn);
        return;
    }

    if((float)op2.bytes>(float)op1.bytes){
        opReturn.bytes = 1;
    }else if((float)op2.bytes<(float)op1.bytes){
        opReturn.bytes = -1;
    }else{
        opReturn.bytes = 0;
    }

    push(opReturn);
}

void OperandStack::dcmpg(){
    Operand op1, op2, op3, op4, opReturn;
    opReturn.type = TYPE_INT;
    opReturn.type = TYPE_INT;

    op1 = pop();
    op2 = pop();
    op3 = pop();
    op4 = pop();

    if((op1.type != TYPE_DOUBLE) || (op2.type != TYPE_DOUBLE) || (op3.type != TYPE_DOUBLE) || (op4.type != TYPE_DOUBLE)) {
        printf("Error type not double: :op_stack.dcmpg\n");
        exit(0);
    }

    double d1 = (double)((uint64_t)op4.bytes<<32 &(uint32_t)op3.bytes);
    double d2 = (double)((uint64_t)op2.bytes<<32 &(uint32_t)op1.bytes);

    if(isnan(d1) || isnan(d2)){
        opReturn.bytes = 1;
    }

    if(d1>d2){
        opReturn.bytes = 1;
    }else if(d1<d2){
        opReturn.bytes = -1;
    }else{
        opReturn.bytes = 0;
    }
}

void OperandStack::dcmpl(){
    Operand op1, op2, op3, op4, opReturn;
    opReturn.type = TYPE_INT;
    opReturn.type = TYPE_INT;

    op1 = pop();
    op2 = pop();
    op3 = pop();
    op4 = pop();

    if((op1.type != TYPE_DOUBLE) || (op2.type != TYPE_DOUBLE) || (op3.type != TYPE_DOUBLE) || (op4.type != TYPE_DOUBLE)) {
        printf("Error type not double: :op_stack.dcmpl\n");
        exit(0);
    }

    double d1 = (double)((uint64_t)op4.bytes<<32 &(uint32_t)op3.bytes);
    double d2 = (double)((uint64_t)op2.bytes<<32 &(uint32_t)op1.bytes);

    if(isnan(d1) || isnan(d2)){
        opReturn.bytes = -1;
    }

    if(d1>d2){
        opReturn.bytes = 1;
    }else if(d1<d2){
        opReturn.bytes = -1;
    }else{
        opReturn.bytes = 0;
    }
}

void OperandStack::lcmp(){
    Operand op1, op2, op3, op4, opReturn;
    opReturn.type = TYPE_INT;
    opReturn.type = TYPE_INT;

    op1 = pop();
    op2 = pop();
    op3 = pop();
    op4 = pop();

    if((op1.type != TYPE_LONG) || (op2.type != TYPE_LONG) || (op3.type != TYPE_LONG) || (op4.type != TYPE_LONG)) {
        printf("Error type not long: :op_stack.lcmp\n");
        exit(0);
    }

    int64_t d1 = (int64_t)((uint64_t)op4.bytes<<32 &(uint32_t)op3.bytes);
    int64_t d2 = (int64_t)((uint64_t)op2.bytes<<32 &(uint32_t)op1.bytes);


    if(d1>d2){
        opReturn.bytes = 1;
    }else if(d1<d2){
        opReturn.bytes = -1;
    }else{
        opReturn.bytes = 0;
    }
}
//iinc

void OperandStack::ishl(){
    Operand op1, op2, opReturn;
    opReturn.type = TYPE_INT;

    op1 = pop();
    op2 = pop();

    if((op1.type != TYPE_INT) || (op2.type != TYPE_INT)) {
        printf("Error type not int: :op_stack.ishl\n");
        exit(0);
    }

    opReturn.bytes = (int32_t)op2.bytes << op1.bytes;

    push(opReturn);
}
void OperandStack::lshl(){
    Operand op1, opL, opH;

    opL = pop();
    opH = pop();
    op1 = pop();

    if((opL.type != TYPE_INT) || (opH.type != TYPE_LONG) || (opH.type != TYPE_LONG)) {
        printf("Error type not long or shift amount not an int: :op_stack.lshl\n");
        exit(0);
    }

    int64_t resultado = (int64_t)to_long( op1.bytes, opH.bytes ) << opL.bytes;

    opH.bytes = (u4)(resultado>>32);
    opL.bytes = (u4)resultado;

    push(opH);
    push(opL);
}
void OperandStack::ishr(){
    Operand op1, op2, opReturn;
    opReturn.type = TYPE_INT;

    op1 = pop();
    op2 = pop();

    if((op1.type != TYPE_INT) || (op2.type != TYPE_INT)) {
        printf("Error type not int: :op_stack.ishr\n");
        exit(0);
    }

    opReturn.bytes = (int32_t)op2.bytes >> op1.bytes;

    push(opReturn);
}

void OperandStack::lshr(){
    Operand op1, opL, opH;

    opL = pop();
    opH = pop();
    op1 = pop();

    if((opL.type != TYPE_INT) || (opH.type != TYPE_LONG) || (opH.type != TYPE_LONG)) {
        printf("Error type not long or shift amount not an int: :op_stack.lshr\n");
        exit(0);
    }

    int64_t resultado = (int64_t)to_long( op1.bytes, opH.bytes ) >> opL.bytes;

    opH.bytes = (u4)(resultado>>32);
    opL.bytes = (u4)resultado;

    push(opH);
    push(opL);
}

void OperandStack::iushr(){
    Operand op1, op2, opReturn;
    opReturn.type = TYPE_INT;

    op1 = pop();
    op2 = pop();

    if((op1.type != TYPE_INT) || (op2.type != TYPE_INT)) {
        printf("Error type not int: :op_stack.iushr\n");
        exit(0);
    }

    opReturn.bytes = op2.bytes >> op1.bytes;

    push(opReturn);
}

void OperandStack::lushr(){
    Operand op1, opL, opH;

    opL = pop();
    opH = pop();
    op1 = pop();

    if((opL.type != TYPE_INT) || (opH.type != TYPE_LONG) || (opH.type != TYPE_LONG)) {
        printf("Error type not long or shift amount not an int: :op_stack.lushr\n");
        exit(0);
    }

    uint64_t resultado = (uint64_t)to_long( op1.bytes, opH.bytes ) >> opL.bytes;

    opH.bytes = (u4)(resultado>>32);
    opL.bytes = (u4)resultado;

    push(opH);
    push(opL);
}
void OperandStack::iand(){
    Operand op1, op2, opReturn;
    opReturn.type = TYPE_INT;

    op1 = pop();
    op2 = pop();

    if((op1.type != TYPE_INT) || (op2.type != TYPE_INT)) {
        printf("Error type not int: :op_stack.iand\n");
        exit(0);
    }

    opReturn.bytes = (int32_t)op2.bytes & (int32_t)op1.bytes;

    push(opReturn);
}
void OperandStack::land(){
    Operand op1, op2, opL, opH;

    opL = pop();
    opH = pop();
    op1 = pop();
    op2 = pop();

    if((op1.type != TYPE_LONG) || (op2.type != TYPE_LONG) || (opL.type != TYPE_LONG) || (opH.type != TYPE_LONG)) {
        printf("Error type not long: :op_stack.land\n");
        exit(0);
    }

    int64_t resultado = (int64_t)to_long( op2.bytes, op1.bytes ) & (int64_t)to_long(opH.bytes, opL.bytes);

    opH.bytes = (u4)(resultado>>32);
    opL.bytes = (u4)resultado;

    push(opH);
    push(opL);
}
void OperandStack::ior(){
    Operand op1, op2, opReturn;
    opReturn.type = TYPE_INT;

    op1 = pop();
    op2 = pop();

    if((op1.type != TYPE_INT) || (op2.type != TYPE_INT)) {
        printf("Error type not int: :op_stack.ior\n");
        exit(0);
    }

    opReturn.bytes = (int32_t)op2.bytes + (int32_t)op1.bytes;

    push(opReturn);
}
void OperandStack::lor(){
    Operand op1, op2, opL, opH;

    opL = pop();
    opH = pop();
    op1 = pop();
    op2 = pop();

    if((op1.type != TYPE_LONG) || (op2.type != TYPE_LONG) || (opL.type != TYPE_LONG) || (opH.type != TYPE_LONG)) {
        printf("Error type not long: :op_stack.lor\n");
        exit(0);
    }

    int64_t resultado = (int64_t)to_long( op2.bytes, op1.bytes ) | (int64_t)to_long(opH.bytes, opL.bytes);

    opH.bytes = (u4)(resultado>>32);
    opL.bytes = (u4)resultado;

    push(opH);
    push(opL);
}
void OperandStack::ixor(){
    Operand op1, op2, opReturn;
    opReturn.type = TYPE_INT;

    op1 = pop();
    op2 = pop();

    if((op1.type != TYPE_INT) || (op2.type != TYPE_INT)) {
        printf("Error type not int: :op_stack.ixor\n");
        exit(0);
    }

    opReturn.bytes = (int32_t)op2.bytes ^ (int32_t)op1.bytes;

    push(opReturn);
}
void OperandStack::lxor(){
    Operand op1, op2, opL, opH;

    opL = pop();
    opH = pop();
    op1 = pop();
    op2 = pop();

    if((op1.type != TYPE_LONG) || (op2.type != TYPE_LONG) || (opL.type != TYPE_LONG) || (opH.type != TYPE_LONG)) {
        printf("Error type not long: :op_stack.lxor\n");
        exit(0);
    }

    int64_t resultado = (int64_t)to_long( op2.bytes, op1.bytes ) ^ (int64_t)to_long(opH.bytes, opL.bytes);

    opH.bytes = (u4)(resultado>>32);
    opL.bytes = (u4)resultado;

    push(opH);
    push(opL);
}

int32_t OperandStack::pop_i() {
	Operand op = pop();
	return op.to_int();
}

int64_t OperandStack::pop_l() {
	Operand opL = pop();
	Operand opH = pop();
	return to_long(opH.bytes, opL.bytes);
}

float OperandStack::pop_f() {
	Operand op = pop();
	return op.to_float();
}

double OperandStack::pop_d() {
	Operand opL = pop();
	Operand opH = pop();
	return to_double(opH.bytes, opL.bytes);
}

int64_t to_long(u4 high, u4 low) {
	int64_t l = 0L;

	__to_value64(&l, high, low);
	return l;
}

double to_double(u4 high, u4 low) {
	double d = 0.0;

	__to_value64(&d, high, low);
	return d;
}
