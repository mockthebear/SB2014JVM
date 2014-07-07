#include "frame.hpp"

Frame::Frame(Class *r, Code *c, char *m_name, char *descrip) {
	pc = 0;
	retpc = 0;
	classref = r;
	code = c;
	methodname = m_name;
	descriptor = descrip;
	
	opStack = new OperandStack(code->max_stack);
	varArray = new LocalVariableArray(code->max_locals);
	wideFlag = false;
}

void Frame::bipush(u1 in) {
	opStack->bipush(in);
}

void Frame::sipush(u2 in) {
	opStack->sipush(in);
}

void Frame::ldc(u2 cp_index) {
	char tag = classref->get_cp_tag(cp_index);
	u4 byte = classref->get_cp_bytes(cp_index);
	Operand op;
	if(tag == TAG_STRING) {
		byte = (u4)get_string(byte);
        op.set_byte( TYPE_REF , byte);
	} else if(tag == TAG_INTEGER) {
		op.set_byte(TYPE_INT, byte);
	} else if(tag == TAG_FLOAT) {
		op.set_byte(TYPE_FLOAT, byte);
	} else {
		printf("Error wrong cp tag for ldc %d: frame.ldc\n",tag);
		exit(0);
	}
	opStack->push(op);
}

void Frame::ldc_w(u2 cp_index) {
	char tag = classref->get_cp_tag(cp_index);
	u4 byte = classref->get_cp_bytes(cp_index);
	Operand op;
	if(tag == TAG_STRING) {

	} else if(tag == TAG_INTEGER) {
		op.set_byte(TYPE_INT, byte);
	} else if(tag == TAG_FLOAT) {
		op.set_byte(TYPE_FLOAT, byte);
	} else {
		printf("Error wrong cp tag for ldc_w %d: frame.ldc_w\n",tag);
		exit(0);
	}
	opStack->push(op);
}

void Frame::ldc2_w(u2 cp_index) {
	char tag = classref->get_cp_tag(cp_index);
	u4 byte1 = classref->get_cp_bytes(cp_index);
	u4 byte2 = classref->get_cp_bytes(cp_index+1);
	Operand op1, op2;

	if(tag == TAG_LONG) {
		op1.set_byte(TYPE_LONG, byte1);
		op2.set_byte(TYPE_LONG, byte2);
	} else if(tag == TAG_DOUBLE) {
		op1.set_byte(TYPE_DOUBLE, byte1);
		op2.set_byte(TYPE_DOUBLE, byte2);
	} else {
		printf("Error wrong cp tag for ldc2_w %d: frame.ldc2_w\n",tag);
		exit(0);
	}
	opStack->push(op1);
	opStack->push(op2);
}

void Frame::pop() {
	(void)opStack->pop();
}

void Frame::pop2() {
	(void)opStack->pop();
	(void)opStack->pop();
}

void Frame::dup() {
	opStack->dup();
}

void Frame::dup2() {
	opStack->dup2();
}

void Frame::swap() {
	opStack->swap();
}
void Frame::dup_x1() {
	opStack->dup_x1();
}
void Frame::dup_x2() {
	opStack->dup_x2();
}
void Frame::dup2_x1() {
	opStack->dup2_x1();
}
void Frame::dup2_x2() {
	opStack->dup2_x2();
}

void Frame::ifeq(u2 branch) {
	if(opStack->ifzero()) {
		pc = (int)branch;
	}
}

void Frame::ifnull(u2 branch) {
	if(opStack->ifzero()) {
		pc = (int)branch;
	}
}

void Frame::ifgt(u2 branch) {
	if(opStack->ifgt()) {
		pc = (int)branch;
	}
}

void Frame::ifge(u2 branch) {
	if(!opStack->iflt()) {
		pc = (int)branch;
	}
}

void Frame::iflt(u2 branch) {
	if(opStack->iflt()) {
		pc = (int)branch;
	}
}

void Frame::ifle(u2 branch) {
	if(!opStack->ifgt()) {
		pc = (int)branch;
	}
}

void Frame::ifne(u2 branch) {
	if(!opStack->ifzero()) {
		pc = (int)branch;
	}
}

void Frame::ifnonnull(u2 branch) {
	if(!opStack->ifzero()) {
		pc = (int)branch;
	}
}

void Frame::if_icmpeq(u2 branch) {

	if(opStack->if_icmpeq()) {
		pc = (int)branch;
	}
}

void Frame::if_icmpgt(u2 branch) {
	if(opStack->if_icmpgt()) {
		pc = (int)branch;
	}
}

void Frame::if_icmpge(u2 branch) {
	if(!opStack->if_icmplt()) {
		pc = (int)branch;
	}
}

void Frame::if_icmplt(u2 branch) {
	if(opStack->if_icmplt()) {
		pc = (int)branch;
	}
}

void Frame::if_icmple(u2 branch) {
	if(!opStack->if_icmpgt()) {
		pc = (int)branch;
	}
}

void Frame::if_icmpne(u2 branch) {
	if(!opStack->if_icmpeq()) {
		pc = (int)branch;
	}
}

void Frame::if_acmpeq(u2 branch) {

	if(opStack->if_icmpeq()) {
		pc = (int)branch;
	}
}

void Frame::op_goto(u2 branch) {
	pc = (int)branch;
}

void Frame::goto_w(u4 branch) {
	pc = (int)branch;
}

void Frame::if_acmpne(u2 branch) {
	if(!opStack->if_icmpeq()) {
		pc = (int)branch;
	}
}

void Frame::iadd() {
	opStack->iadd();
}

void Frame::isub() {
	opStack->isub();
}

void Frame::imul() {
	opStack->imul();
}

void Frame::idiv() {
	opStack->idiv();
}

void Frame::irem() {
	opStack->irem();
}

void Frame::ineg() {
	opStack->ineg();
}

void Frame::ladd() {
	opStack->ladd();
}

void Frame::ixor() {
	opStack->ixor();
}

void Frame::ior() {
	opStack->ior();
}

void Frame::iand() {
	opStack->iand();
}

void Frame::ishl() {
	opStack->ishl();
}

void Frame::ishr() {
	opStack->ishr();
}

void Frame::iushr() {
	opStack->iushr();
}

void Frame::land() {
	opStack->land();
}

void Frame::lushr() {
	opStack->lushr();
}


void Frame::lshl() {
	opStack->lshl();
}

void Frame::lshr() {
	opStack->lshr();
}


void Frame::lxor() {
	opStack->lxor();
}

void Frame::lor() {
	opStack->lor();
}

void Frame::lsub() {
	opStack->lsub();
}

void Frame::lmul() {
	opStack->lmul();
}

void Frame::ldiv() {
	opStack->ldiv();
}

void Frame::lrem() {
	opStack->lrem();
}

void Frame::lneg() {
	opStack->lneg();
}

void Frame::fadd() {
	opStack->fadd();
}

void Frame::fsub() {
	opStack->fsub();
}

void Frame::fmul() {
	opStack->fmul();
}

void Frame::fdiv() {
	opStack->fdiv();
}

void Frame::frem() {
	opStack->frem();
}

void Frame::fneg() {
	opStack->fneg();
}

void Frame::dadd() {
	opStack->dadd();
}

void Frame::dsub() {
	opStack->dsub();
}

void Frame::dmul() {
	opStack->dmul();
}

void Frame::ddiv() {
	opStack->ddiv();
}

void Frame::drem() {
	opStack->drem();
}

void Frame::dneg() {
	opStack->dneg();
}

void Frame::i2l() {
	opStack->i2l();
}

void Frame::i2f() {
	opStack->i2f();
}

void Frame::i2d() {
	opStack->i2d();
}


void Frame::l2i() {
	opStack->l2i();
}
void Frame::l2f() {
	opStack->l2f();
}

void Frame::l2d() {
	opStack->l2d();
}
void Frame::i2b() {
	opStack->i2b();
}

void Frame::i2c() {
	opStack->i2c();
}

void Frame::i2s() {
	opStack->i2s();
}

void Frame::lcmp() {
	opStack->lcmp();
}

void Frame::fcmpl() {
	opStack->fcmpl();
}

void Frame::fcmpg() {
	opStack->fcmpg();
}

void Frame::dcmpl() {
	opStack->dcmpl();
}
void Frame::dcmpg() {
	opStack->dcmpg();
}
void Frame::f2i() {
	opStack->f2i();
}

void Frame::f2l() {
	opStack->f2l();
}

void Frame::f2d() {
	opStack->f2d();
}

void Frame::d2i() {
	opStack->d2i();
}

void Frame::d2l() {
	opStack->d2l();
}

void Frame::d2f() {
	opStack->d2f();
}
void Frame::iinc(u2 index, u1 value) {
	varArray->iinc(index, value);
}

void Frame::iconst_m1() {
	opStack->iconst(-1);
}

void Frame::iconst_0() {
	opStack->iconst(0);
}

void Frame::iconst_1() {
	opStack->iconst(1);
}

void Frame::iconst_2() {
	opStack->iconst(2);
}

void Frame::iconst_3() {
	opStack->iconst(3);
}

void Frame::iconst_4() {
	opStack->iconst(4);
}

void Frame::iconst_5() {
	opStack->iconst(5);
}

void Frame::fconst_0() {
	opStack->fconst(0.0F);
}

void Frame::fconst_1() {
	opStack->fconst(1.0F);
}

void Frame::fconst_2() {
	opStack->fconst(2.0F);
}

void Frame::lconst_0() {
	opStack->lconst(0);
}

void Frame::lconst_1() {
	opStack->lconst(1);
}

void Frame::dconst_0() {
	opStack->dconst(0);
}

void Frame::dconst_1() {
	opStack->dconst(1);
}

void Frame::aconst_null() {
	opStack->aconst_null();
}

void Frame::checkcast(u2 index){

}
void Frame::iload(u2 index) {
	Operand op;
	op = varArray->load(index);
	if(op.type != TYPE_INT) {
		printf("Error value type %c != %c index[%d]: frame.iload\n",TYPE_INT,op.type,index);
		exit(0);
	}
	opStack->push(op);
}

void Frame::lload(u2 index) {
	Operand opH, opL;
	opH = varArray->load(index);
	opL = varArray->load(index+1);
	if( (opH.type != TYPE_LONG) || (opL.type != TYPE_LONG) ) {
		printf("Error value type %c != %c index[%d]: frame.lload\n",TYPE_LONG,opH.type,index);
		exit(0);
	}
	opStack->push(opH);
	opStack->push(opL);
}

void Frame::fload(u2 index) {
	Operand op;
	op = varArray->load(index);
	if(op.type != TYPE_FLOAT) {
		printf("Error value type %c != %c index[%d]: frame.fload\n",TYPE_FLOAT,op.type,index);
		exit(0);
	}
	opStack->push(op);
}

void Frame::dload(u2 index) {
	Operand opH, opL;
	opH = varArray->load(index);
	opL = varArray->load(index+1);
	if( (opH.type != TYPE_DOUBLE) || (opL.type != TYPE_DOUBLE) ) {
		printf("Error value type %c != %c index[%d]: frame.dload\n",TYPE_DOUBLE,opH.type,index);
		exit(0);
	}
	opStack->push(opH);
	opStack->push(opL);
}

void Frame::aload(u2 index) {
	Operand op;
	op = varArray->load(index);
	if(op.type != TYPE_REF) {
		printf("Error value type %c != %c index[%d]: frame.aload\n",TYPE_REF,op.type,index);
		exit(0);
	}
	opStack->push(op);
}

void Frame::iload_0(){
	iload(0);
}

void Frame::iload_1(){
	iload(1);
}

void Frame::iload_2(){
	iload(2);
}

void Frame::iload_3(){
	iload(3);
}

void Frame::lload_0(){
	lload(0);
}

void Frame::lload_1(){
	lload(1);
}

void Frame::lload_2(){
	lload(2);
}

void Frame::lload_3(){
	lload(3);
}

void Frame::fload_0(){
	fload(0);
}

void Frame::fload_1(){
	fload(1);
}

void Frame::fload_2(){
	fload(2);
}

void Frame::fload_3(){
	fload(3);
}

void Frame::dload_0(){
	dload(0);
}

void Frame::dload_1(){
	dload(1);
}

void Frame::dload_2(){
	dload(2);
}

void Frame::dload_3(){
	dload(3);
}

void Frame::aload_0(){
	aload(0);
}

void Frame::aload_1(){
	aload(1);
}

void Frame::aload_2(){
	aload(2);
}

void Frame::aload_3(){
	aload(3);
}

void Frame::istore(u2 index) {
	Operand op;
	op = opStack->pop();
	if(op.type != TYPE_INT) {
		printf("Error value type %c != %c index[%d]: frame.istore\n",TYPE_INT,op.type,index);
		exit(0);
	}
	varArray->store(index, op);
}

void Frame::lstore(u2 index) {
	Operand opH, opL;
	opL = opStack->pop();
	opH = opStack->pop();
	if( (opH.type != TYPE_LONG) || (opL.type != TYPE_LONG) ) {
		printf("Error value type %c != %c index[%d]: frame.lstore\n",TYPE_LONG,opH.type,index);
		exit(0);
	}
	varArray->store(index, opH);
	varArray->store(index+1, opL);
}

void Frame::fstore(u2 index) {
	Operand op;
	op = opStack->pop();
	if(op.type != TYPE_FLOAT) {
		printf("Error value type %c != %c index[%d]: frame.fstore\n",TYPE_FLOAT,op.type,index);
		exit(0);
	}
	varArray->store(index, op);
}

void Frame::dstore(u2 index) {
	Operand opH, opL;
	opL = opStack->pop();
	opH = opStack->pop();
	if( (opH.type != TYPE_DOUBLE) || (opL.type != TYPE_DOUBLE) ) {
		printf("Error value type %c != %c index[%d]: frame.dstore\n",TYPE_DOUBLE,opH.type,index);
		exit(0);
	}
	varArray->store(index, opH);
	varArray->store(index+1, opL);
}

void Frame::astore(u2 index) {
	Operand op;
	op = opStack->pop();
	if(op.type != TYPE_REF) {
		printf("Error value type %d != %d index[%d]: frame.astore\n",TYPE_REF,op.type,index);
		exit(0);
	}
	varArray->store(index,op);
}

void Frame::istore_0() {
	istore(0);
}

void Frame::istore_1() {
	istore(1);
}

void Frame::istore_2() {
	istore(2);
}

void Frame::istore_3() {
	istore(3);
}

void Frame::lstore_0() {
	lstore(0);
}

void Frame::lstore_1() {
	lstore(1);
}

void Frame::lstore_2() {
	lstore(2);
}

void Frame::lstore_3() {
	lstore(3);
}

void Frame::fstore_0() {
	fstore(0);
}

void Frame::fstore_1() {
	fstore(1);
}

void Frame::fstore_2() {
	fstore(2);
}

void Frame::fstore_3() {
	fstore(3);
}

void Frame::dstore_0() {
	dstore(0);
}

void Frame::dstore_1() {
	dstore(1);
}

void Frame::dstore_2() {
	dstore(2);
}

void Frame::dstore_3() {
	dstore(3);
}

void Frame::astore_0() {
	astore(0);
}

void Frame::astore_1() {
	astore(1);
}

void Frame::astore_2() {
	astore(2);
}

void Frame::astore_3() {
	astore(3);
}

char *Frame::get_class_name(u2 cp_index) {
	return classref->get_cp_class_name(cp_index);
}

char *Frame::get_field_class(u2 cp_index) {
	return classref->get_cp_field_class(cp_index);
}

char *Frame::get_field_name(u2 cp_index) {
	return classref->get_cp_field_name(cp_index);
}

char *Frame::get_field_type(u2 cp_index) {
	return classref->get_cp_field_type(cp_index);
}

char *Frame::get_method_class(u2 cp_index) {
	return classref->get_cp_method_class(cp_index);
}

char *Frame::get_method_name(u2 cp_index) {
	return classref->get_cp_method_name(cp_index);
}

char *Frame::get_method_descriptor(u2 cp_index) {
	return classref->get_cp_method_descriptor(cp_index);
}

char *Frame::get_imethod_class(u2 cp_index) {
	return classref->get_cp_imethod_class(cp_index);
}

char *Frame::get_imethod_name(u2 cp_index) {
	return classref->get_cp_imethod_name(cp_index);
}

char *Frame::get_imethod_descriptor(u2 cp_index) {
	return classref->get_cp_imethod_descriptor(cp_index);
}

char *Frame::get_string(u2 cp_index) {
	return classref->get_cp_utf8(cp_index);
}

u1 Frame::getCode() {
	u1 c = code->code[pc];
	pc++;
	return c;
}

int16_t Frame::getPC() {
	return (int16_t)pc;
}

void Frame::pcNext() {
	pc++;
}

void Frame::pcBack(int back) {
	if(back > pc) {
		printf("Error : frame:pcBack\n");
		exit(0);
	}
	pc -= back;
}

void Frame::setParam(Operand *param, int count, int ini) {
	varArray->set_param(param, count, ini);
}

Operand *Frame::popParam(int count) {
	return opStack->pop_param(count);
}

void Frame::pushOpStack(u1 type, u4 value){
	Operand op;
	op.set_byte(type, value);
	opStack->push(op);
}

u4 Frame::popOpStack(){
	Operand op;
	op = opStack->pop();
	return op.bytes;
}

u4 Frame::getOpStackTop(){
	Operand op;
	op = *(opStack->top);
	return op.bytes;
}

void Frame::clear() {
	opStack->clear();
}

int32_t Frame::popInt() {
	return opStack->pop_i();
}

int64_t Frame::popLong() {
	return opStack->pop_l();
}

float Frame::popFloat() {
	return opStack->pop_f();
}

double Frame::popDouble() {
	return opStack->pop_d();
}

char Frame::popChar() {
	return (char)opStack->pop_i();
}

int8_t Frame::popByte() {
	return (int8_t)opStack->pop_i();
}

int16_t Frame::popShort() {
	return (int16_t)opStack->pop_i();
}

void Frame::print() {
	printf(">>Current frame\n");
	printf("  method: %s.", classref->get_cp_this_class());
	printf("%s:", methodname);
	printf("%s\n", descriptor);
	printf("  next pc: %d\n", pc);
	opStack->print();
	varArray->print();
}

void Frame::printCode() {
	printf("%d: [%X] ",pc-1,code->code[pc-1]);
}

void Frame::setPC(int pc)
{
	this->pc = pc;
}
