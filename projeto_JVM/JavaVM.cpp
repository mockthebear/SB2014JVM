#include "JavaVM.hpp"

#define STACK_SIZE  100
#define MEMORY_SIZE 100

void loadMain(char *);
u1 get1byte();
u2 get2byte();
u4 get4byte();
void print();

static StackFrame *frames;
static Memory     *memory;

int main(int argc, char **argv) {
	frames = new StackFrame(STACK_SIZE);
	memory = new Memory(MEMORY_SIZE, MEMORY_SIZE);
	
	char name[3] = "C2";
	loadMain(name);
	
	
	
	while(frames->isEmpty()) {
		u1 code = frames->current->getCode();
		printf("%d: [%X] ",frames->current->getPC()-1,code);
		op[code]();
		print();
		printf("\nENTER para proseguir...\n");
		getchar();
	}
	
	return 0;
}

void loadMain(char *classname) {
	printf("load main\n");
	Class *classRef;
	classRef = memory->new_class(classname);
	
	frames->pushMain(classRef);
	
	print();
	
	printf("Method main carregado!\n"); 
	printf("iniciando JavaVM\n\n"); 
	frames->pushClinit(classRef);
}

void nop() {
	printf("nop\n");
}

void aconst_null() {
	printf("aconst_null\n");
	
	frames->current->aconst_null();
}

void iconst_m1() {
	printf("iconst_m1\n");
	
	frames->current->iconst_m1();
}

void iconst_0() {
	printf("iconst_0\n");
	
	frames->current->iconst_0();
}

void iconst_1() {
	printf("iconst_1\n");
	
	frames->current->iconst_1();
}

void iconst_2() {
	printf("iconst_2\n");
	
	frames->current->iconst_2();
}

void iconst_3() {
	printf("iconst_3\n");
	
	frames->current->iconst_3();
}

void iconst_4() {
	printf("iconst_4\n");
	
	frames->current->iconst_4();
}

void iconst_5() {
	printf("iconst_5\n");
	
	frames->current->iconst_5();
}

void lconst_0() {
	printf("lconst_0\n");
	
	frames->current->lconst_0();
}

void lconst_1() {
	printf("lconst_1\n");
	
	frames->current->lconst_1();
}

void fconst_0() {
	printf("fconst_0\n");
	
	frames->current->fconst_0();
}

void fconst_1() {
	printf("fconst_1\n");
	
	frames->current->fconst_1();
}

void fconst_2() {
	printf("fconst_2\n");
	
	frames->current->fconst_2();
}

void dconst_0() {
	printf("dconst_0\n");
	
	frames->current->dconst_0();
}

void dconst_1() {
	printf("dconst_1\n");
	
	frames->current->dconst_1();
}

void bipush() {
	printf("bipush");
	
	u1 byte = get1byte();
	printf(" %d\n",byte);
	
	frames->current->bipush(byte);
}

void sipush() {
	printf("sipush");
	
	u2 bytes = get2byte();
	printf(" %d\n",bytes);
	
	frames->current->sipush(bytes);
}
	
void ldc() {
	printf("ldc");
	
	u2 cp_index = get1byte();
	printf(" %d\n",cp_index);
	
	frames->current->ldc(cp_index);
}

void ldc_w() {
	printf("ldc_w");
	
	u2 cp_index = get2byte();
	printf(" %d\n",cp_index);
	
	frames->current->ldc_w(cp_index);
}

void ldc2_w() {
	printf("ldc2_w");
	
	u2 cp_index = get2byte();
	printf(" %d\n",cp_index);
	
	frames->current->ldc2_w(cp_index);
}

void iload() {
	printf("iload");
	
	u1 index = get1byte();
	printf(" %d\n",index);
	
	frames->current->iload(index);
}

void lload() {
	printf("lload");
	
	u1 index = get1byte();
	printf(" %d\n",index);
	
	frames->current->lload(index);
}

void fload() {
	printf("fload\n");
	
	u1 index = get1byte();
	
	frames->current->fload(index);
}

void dload() {
	printf("dload\n");
	
	u1 index = get1byte();
	
	frames->current->dload(index);
}

void aload() {
	printf("aload\n");
	
	u1 index = get1byte();
	
	frames->current->aload(index);
}

void iload_0() {
	printf("iload_0\n");
	
	frames->current->iload_0();
}

void iload_1() {
	printf("iload_1\n");
	
	frames->current->iload_1();
}

void iload_2() {
	printf("iload_2\n");
	
	frames->current->iload_2();
}

void iload_3() {
	printf("iload_3\n");
	
	frames->current->iload_3();
}

void lload_0() {
	printf("lload_0\n");
	
	frames->current->lload_0();
}

void lload_1() {
	printf("lload_1\n");
	
	frames->current->lload_1();
}

void lload_2() {
	printf("lload_2\n");
	
	frames->current->lload_2();
}

void lload_3() {
	printf("lload_3\n");
	
	frames->current->lload_3();
}


void fload_0() {
	printf("fload_0\n");
	
	frames->current->fload_0();
}

void fload_1() {
	printf("fload_1\n");
	
	frames->current->fload_1();
}

void fload_2() {
	printf("fload_2\n");
	
	frames->current->fload_2();
}

void fload_3() {
	printf("fload_3\n");
	
	frames->current->fload_3();
}

void dload_0() {
	printf("dload_0\n");
	
	frames->current->dload_0();
}

void dload_1() {
	printf("dload_1\n");
	
	frames->current->dload_1();
}

void dload_2() {
	printf("dload_2\n");
	
	frames->current->dload_2();
}

void dload_3() {
	printf("dload_3\n");
	
	frames->current->dload_3();
}

void aload_0() {
	printf("aload_0\n");
	
	frames->current->aload_0();
}

void aload_1() {
	printf("aload_1\n");
	
	frames->current->aload_1();
}

void aload_2() {
	printf("aload_2\n");
	
	frames->current->aload_2();
}

void aload_3() {
	printf("aload_3\n");
	
	frames->current->aload_3();
}

void iaload() {
	printf("iaload\n");
	
	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();
	u4 value;
	
	memory->iaload(arrayRef, index, &value);
	frames->current->pushOpStack(TYPE_INT, value);
}

void laload() {
	printf("laload\n");
	
	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();
	u4 value[2];
	
	memory->laload(arrayRef, index, value);
	frames->current->pushOpStack(TYPE_LONG, value[0]);
	frames->current->pushOpStack(TYPE_LONG, value[1]);
}

void faload() {
	printf("faload\n");
	
	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();
	u4 value;
	
	memory->faload(arrayRef, index, &value);
	frames->current->pushOpStack(TYPE_FLOAT, value);
}

void daload() {
	printf("daload\n");
	
	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();
	u4 value[2];
	
	memory->daload(arrayRef, index, value);
	frames->current->pushOpStack(TYPE_DOUBLE, value[0]);
	frames->current->pushOpStack(TYPE_DOUBLE, value[1]);
}

void aaload() {
	printf("aaload\n");
	
	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();
	u4 value;
	
	memory->aaload(arrayRef, index, &value);
	frames->current->pushOpStack(TYPE_REF, value);
}

void baload() {
	printf("baload\n");
	
	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();
	u4 value;
	
	memory->baload(arrayRef, index, &value);
	frames->current->pushOpStack(TYPE_INT, value);
}

void caload() {
	printf("caload\n");
	
	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();
	u4 value;
	
	memory->caload(arrayRef, index, &value);
	frames->current->pushOpStack(TYPE_INT, value);
}

void saload() {
	printf("saload\n");
	
	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();
	u4 value;
	
	memory->saload(arrayRef, index, &value);
	frames->current->pushOpStack(TYPE_INT, value);
}

void istore() {
	printf("istore\n");
	
	u1 index = get1byte();
	
	frames->current->istore(index);
}

void lstore() {
	printf("lstore\n");
	
	u1 index = get1byte();
	
	frames->current->lstore(index);
}

void fstore() {
	printf("fstore\n");
	
	u1 index = get1byte();
	
	frames->current->fstore(index);
}

void dstore() {
	printf("dstore\n");
	
	u1 index = get1byte();
	
	frames->current->dstore(index);
}

void astore() {
	printf("astore\n");
	
	u1 index = get1byte();
	
	frames->current->astore(index);
}

void istore_0() {
	printf("istore_0\n");
	
	frames->current->istore_0();
}

void istore_1() {
	printf("istore_1\n");
	
	frames->current->istore_1();
}

void istore_2() {
	printf("istore_2\n");
	
	frames->current->istore_2();
}

void istore_3() {
	printf("istore_3\n");
	
	frames->current->istore_3();
}

void lstore_0() {
	printf("lstore_0\n");
	
	frames->current->lstore_0();
}

void lstore_1() {
	printf("lstore_1\n");
	
	frames->current->lstore_1();
}

void lstore_2() {
	printf("lstore_2\n");
	
	frames->current->lstore_2();
}

void lstore_3() {
	printf("lstore_3\n");
	
	frames->current->lstore_3();
}


void fstore_0() {
	printf("fstore_0\n");
	
	frames->current->fstore_0();
}

void fstore_1() {
	printf("fstore_1\n");
	
	frames->current->fstore_1();
}

void fstore_2() {
	printf("fstore_2\n");
	
	frames->current->fstore_2();
}

void fstore_3() {
	printf("fstore_3\n");
	
	frames->current->fstore_3();
}

void dstore_0() {
	printf("dstore_0\n");
	
	frames->current->dstore_0();
}

void dstore_1() {
	printf("dstore_1\n");
	
	frames->current->dstore_1();
}

void dstore_2() {
	printf("dstore_2\n");
	
	frames->current->dstore_2();
}

void dstore_3() {
	printf("dstore_3\n");
	
	frames->current->dstore_3();
}

void astore_0() {
	printf("astore_0\n");
	
	frames->current->astore_0();
	
	
}

void astore_1() {
	printf("astore_1\n");
	
	frames->current->astore_1();
}

void astore_2() {
	printf("astore_2\n");
	
	frames->current->astore_2();
}

void astore_3() {
	printf("astore_3\n");
	
	frames->current->astore_3();
}

void iastore() {
	printf("iastore\n");
	
	u4 value = frames->current->popOpStack();
	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();
	
	memory->iastore(arrayRef, index, &value);
}

void lastore() {
	printf("lastore\n");
	
	u4 value[2];
	value[1]= frames->current->popOpStack();
	value[0]= frames->current->popOpStack();
	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();
	
	memory->lastore(arrayRef, index, value);
}

void fastore() {
	printf("fastore\n");
	
	u4 value = frames->current->popOpStack();
	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();
	
	memory->fastore(arrayRef, index, &value);
}

void dastore() {
	printf("dastore\n");
	
	u4 value[2];
	value[1]= frames->current->popOpStack();
	value[0]= frames->current->popOpStack();
	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();
	
	memory->dastore(arrayRef, index, value);
}

void aastore() {
	printf("aastore\n");
	
	u4 value = frames->current->popOpStack();
	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();
	
	memory->aastore(arrayRef, index, &value);
}

void bastore() {
	printf("bastore\n");
	
	u4 value = frames->current->popOpStack();
	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();
	
	memory->bastore(arrayRef, index, &value);
}

void castore() {
	printf("castore\n");
	
	u4 value = frames->current->popOpStack();
	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();
	
	memory->castore(arrayRef, index, &value);
}

void sastore() {
	printf("sastore\n");
	
	u4 value = frames->current->popOpStack();
	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();
	
	memory->sastore(arrayRef, index, &value);
}

void pop() {
	printf("pop\n");
	
	frames->current->pop();
}

void pop2() {
	printf("pop2\n");
	
	frames->current->pop2();
}

void dup() {
	printf("dup\n");
	
	frames->current->dup();
}

void dup_x1() {}
void dup_x2() {}
void dup2() {}
void dup2_x1() {}
void dup2_x2() {}
void swap() {
	printf("swap\n");
	
	frames->current->swap();

}

void iadd() {
	printf("iadd\n");
	
	frames->current->iadd();
}

void ladd() {
	printf("ladd\n");
	
	frames->current->ladd();
}

void fadd() {
	printf("fadd\n");
	
	frames->current->fadd();
}

void dadd() {
	printf("dadd\n");
	
	frames->current->dadd();
}

void isub() {
	printf("isub\n");
	
	frames->current->isub();
}

void lsub() {
	printf("lsub\n");
	
	frames->current->lsub();
}

void fsub() {
	printf("fsub\n");
	
	frames->current->fsub();
}

void dsub() {
	printf("dsub\n");
	
	frames->current->dsub();
}

void imul() {
	printf("imul\n");
	
	frames->current->imul();
}

void lmul() {
	printf("lmul\n");
	
	frames->current->lmul();
}

void fmul() {
	printf("fmul\n");
	
	frames->current->fmul();
}

void dmul() {
	printf("dmul\n");
	
	frames->current->dmul();
}

void idiv() {
	printf("idiv\n");
	
	frames->current->idiv();
}

void ldiv() {
	printf("ldiv\n");
	
	frames->current->ldiv();
}

void fdiv() {
	printf("fdiv\n");
	
	frames->current->fdiv();
}

void ddiv() {
	printf("ddiv\n");
	
	frames->current->ddiv();
}

void irem() {
	printf("irem\n");
	
	frames->current->irem();
}

void lrem() {
	printf("lrem\n");
	
	frames->current->lrem();
}

void frem() {
	printf("frem\n");
	
	frames->current->frem();
}

void drem() {
	printf("drem\n");
	
	frames->current->drem();
}

void ineg() {
	printf("ineg\n");
	
	frames->current->ineg();
}

void lneg() {
	printf("lneg\n");
	
	frames->current->lneg();
}

void fneg() {
	printf("fneg\n");
	
	frames->current->fneg();
}

void dneg() {
	printf("dneg\n");
	
	frames->current->dneg();
}

void ishl() {}
void lshl() {}
void ishr() {}
void lshr() {}
void iushr() {}
void lushr() {}
void iand() {}
void land() {}
void ior() {}
void lor() {}
void ixor() {}
void lxor() {}
void iinc() {
	printf("iinc\n");
	
	u1 index = get1byte();
	u1 value = get1byte();
	
	frames->current->iinc(index, value);
}

void i2l() {}
void i2f() {}
void i2d() {}
void l2i() {}
void l2f() {}
void l2d() {}
void f2i() {}
void f2l() {}
void f2d() {}
void d2i() {}
void d2l() {}
void d2f() {}
void i2b() {}
void i2c() {}
void i2s() {}
void lcmp() {}
void fcmpl() {}
void fcmpg() {}
void dcmpl() {}
void dcmpg() {}

void ifeq() {
	printf("ifeq\n");
	
	int16_t pc = frames->current->getPC()-1;
	
	u2 branch = get2byte();
	pc += (int16_t)branch;
	
	frames->current->ifeq(pc);
}

void ifne() {
	printf("ifne\n");
	
	int16_t pc = frames->current->getPC()-1;
	
	u2 branch = get2byte();
	pc += (int16_t)branch;
	
	frames->current->ifne(pc);
}

void iflt() {
	printf("iflt\n");
	
	int16_t pc = frames->current->getPC()-1;
	
	u2 branch = get2byte();
	pc += (int16_t)branch;
	
	frames->current->iflt(pc);
}

void ifge() {
	printf("ifge\n");
	
	int16_t pc = frames->current->getPC()-1;
	
	u2 branch = get2byte();
	pc += (int16_t)branch;
	
	frames->current->ifge(pc);
}

void ifgt() {
	printf("ifgt\n");
	
	int16_t pc = frames->current->getPC()-1;
	
	u2 branch = get2byte();
	pc += (int16_t)branch;
	
	frames->current->ifgt(pc);
}

void ifle() {
	printf("ifle\n");
	
	int16_t pc = frames->current->getPC()-1;
	
	u2 branch = get2byte();
	pc += (int16_t)branch;
	
	frames->current->ifle(pc);
}

void if_icmpeq() {
	printf("if_icmpeq\n");
	
	int16_t pc = frames->current->getPC()-1;
	
	u2 branch = get2byte();
	pc += (int16_t)branch;
	
	frames->current->if_icmpeq(pc);
}

void if_icmpne() {
	printf("if_icmpne\n");
	
	int16_t pc = frames->current->getPC()-1;
	
	u2 branch = get2byte();
	pc += (int16_t)branch;
	
	frames->current->if_icmpne(pc);
}

void if_icmplt() {
	printf("if_icmplt\n");
	
	int16_t pc = frames->current->getPC()-1;
	
	u2 branch = get2byte();
	pc += (int16_t)branch;
	
	frames->current->if_icmplt(pc);
}

void if_icmpge() {
	printf("if_icmpge\n");
	
	int16_t pc = frames->current->getPC()-1;
	
	u2 branch = get2byte();
	pc += (int16_t)branch;
	
	frames->current->if_icmpge(pc);
}

void if_icmpgt() {
	printf("if_icmpgt\n");
	
	int16_t pc = frames->current->getPC()-1;
	
	u2 branch = get2byte();
	pc += (int16_t)branch;
	
	frames->current->if_icmpgt(pc);
}

void if_icmple() {
	printf("if_icmple\n");
	
	int16_t pc = frames->current->getPC()-1;
	
	u2 branch = get2byte();
	pc += (int16_t)branch;
	
	frames->current->if_icmple(pc);
}

void if_acmpeq() {
	printf("if_acmpeq\n");
	
	int16_t pc = frames->current->getPC()-1;
	
	u2 branch = get2byte();
	pc += (int16_t)branch;
	
	frames->current->if_acmpeq(pc);
}

void if_acmpne() {
	printf("if_acmpne\n");
	
	int16_t pc = frames->current->getPC()-1;
	
	u2 branch = get2byte();
	pc += (int16_t)branch;
	
	frames->current->if_acmpne(pc);
}

void op_goto() {
	printf("op_goto\n");
	
	int16_t pc = frames->current->getPC()-1;
	
	u2 branch = get2byte();
	pc += (int16_t)branch;
	
	frames->current->op_goto(pc);
	
}

void jsr() {}
void ret() {}
void tableswitch() {}
void lookupswitch() {}
void ireturn() {}
void lreturn() {}
void freturn() {}
void dreturn() {}
void areturn() {}
void op_return() {
	printf("return\n");
	
	frames->op_return();
}

void getstatic() {
	printf("getstatic");
	
	u2 cp_index = get2byte();
	printf("  %d\n",cp_index);
	
	char *className = frames->current->get_field_class(cp_index);
	char *fieldName = frames->current->get_field_name(cp_index);
	char *fieldType = frames->current->get_field_type(cp_index);
	
	Class *classRef = memory->get_classref(className);
	if(classRef == NULL) {
		classRef = memory->new_class(className);
		frames->current->pcBack(3);
		frames->pushClinit(classRef);
		
		return;
	}
	u4 value[2];
	
	memory->getstatic(classRef, fieldName, fieldType, value);
	
	frames->current->pushOpStack(*fieldType, value[0]);
	if( (*fieldType == TYPE_LONG) || (*fieldType == TYPE_DOUBLE) ) {
		frames->current->pushOpStack(*fieldType, value[1]);
	}
}

void putstatic() {
	printf("putstatic");
	
	u2 cp_index = get2byte();
	printf("  %d\n",cp_index);
	
	char *className = frames->current->get_field_class(cp_index);
	char *fieldName = frames->current->get_field_name(cp_index);
	char *fieldType = frames->current->get_field_type(cp_index);
	
	Class *classRef = memory->get_classref(className);
	if(classRef == NULL) {
		classRef = memory->new_class(className);
		frames->current->pcBack(3);
		frames->pushClinit(classRef);
		
		return;
	}
	
	u4 value[2];
	
	value[0] = frames->current->popOpStack();
	if( (*fieldType == TYPE_LONG) || (*fieldType == TYPE_DOUBLE) ) {
		value[1] = value[0];
		value[0] = frames->current->popOpStack();
	}
	
	memory->putstatic(classRef, fieldName, fieldType, value);
}

void getfield() {
	printf("getfield");

	u2 cp_index = get2byte();
	printf("  %d\n",cp_index);
	
	char *className = frames->current->get_field_class(cp_index);
	char *fieldName = frames->current->get_field_name(cp_index);
	char *fieldType = frames->current->get_field_type(cp_index);
	
	u4 insRef = frames->current->popOpStack();
	u4 value[2];
	
	memory->getfield(insRef, className, fieldName, fieldType, value);
	
	frames->current->pushOpStack(*fieldType, value[0]);
	if( (*fieldType == TYPE_LONG) || (*fieldType == TYPE_DOUBLE) ) {
		frames->current->pushOpStack(*fieldType, value[1]);
	}
	
}

void putfield() {
	printf("putfield");
	
	u2 cp_index = get2byte();
	printf("  %d\n",cp_index);
	
	char *className = frames->current->get_field_class(cp_index);
	char *fieldName = frames->current->get_field_name(cp_index);
	char *fieldType = frames->current->get_field_type(cp_index);
	
	u4 value[2];
	
	value[0] = frames->current->popOpStack();
	if( (*fieldType == TYPE_LONG) || (*fieldType == TYPE_DOUBLE) ) {
		value[1] = value[0];
		value[0] = frames->current->popOpStack();
	}
	u4 insRef = frames->current->popOpStack();
	
	memory->putfield(insRef, className, fieldName, fieldType, value);
}

void invokevirtual() {
	printf("invokevirtual");
	
	u2 cp_index = get2byte();
	printf("  %d\n",cp_index);
	
	char *className  = frames->current->get_method_class(cp_index);
	char *methodName = frames->current->get_method_name(cp_index);
	char *descriptor = frames->current->get_method_descriptor(cp_index);
	
	Class *classRef = memory->get_classref(className);
	if(classRef == NULL) {
		classRef = memory->new_class(className);
		frames->current->pcBack(3);
		frames->pushClinit(classRef);
		
		return;
	}
	
	frames->invokevirtual(classRef, methodName, descriptor);
}

void invokespecial() {
	printf("invokespecial");
	
	u2 cp_index = get2byte();
	printf("  %d\n",cp_index);
	
	char *className  = frames->current->get_method_class(cp_index);
	char *methodName = frames->current->get_method_name(cp_index);
	char *descriptor = frames->current->get_method_descriptor(cp_index);
	
	Class *classRef = memory->get_classref(className);
	if(classRef == NULL) {
		classRef = memory->new_class(className);
		frames->current->pcBack(3);
		frames->pushClinit(classRef);
		
		return;
	}
	
	frames->invokespecial(classRef, methodName, descriptor);
	
}

void invokestatic() {}
void invokeinterface() {}
void invokedynamic() {}
void op_new() {
	printf("new");

	u2 cp_index = get2byte();
	printf("  %d\n",cp_index);
	
	char *classname = frames->current->get_class_name(cp_index);
	
	Class *classRef = memory->get_classref(classname);
	if(classRef == NULL) {
		classRef = memory->new_class(classname);
		frames->current->pcBack(3);
		frames->pushClinit(classRef);
		
		return;
	}
	
	u4 instRef = memory->op_new(classRef);
	frames->current->pushOpStack(TYPE_REF, instRef);
}

void newarray() {
	printf("newarray");
	
	u1 atype = get1byte();
	printf("  %d\n",atype);
	
	u4 count = frames->current->popOpStack();
	u4 arrayRef;
	
	arrayRef = memory->newarray(count, atype);
	frames->current->pushOpStack(TYPE_REF, arrayRef);
}

void anewarray() {
	printf("anewarray");
	
	u2 cp_index = get2byte();
	printf("  %d\n",cp_index);
	
	char *classname = frames->current->get_class_name(cp_index);
	
	Class *classRef = memory->get_classref(classname);
	if(classRef == NULL) {
		classRef = memory->new_class(classname);
		frames->current->pcBack(3);
		frames->pushClinit(classRef);
		
		return;
	}
	
	u4 count = frames->current->popOpStack();
	u4 arrayRef;
	arrayRef = memory->anewarray(count, classname, classRef);
	frames->current->pushOpStack(TYPE_REF, arrayRef);
}

void arraylength() {}
void athrow() {}
void checkcast() {}
void instanceof() {}
void monitorenter() {}
void monitorexit() {}
void wide() {}
void multianewarray() {
	printf("multianewarray");
	
	u2 cp_index = get2byte();
	int dim = get1byte();
	printf("  %d %d\n",cp_index,dim);
	
	char *arrayType = frames->current->get_class_name(cp_index);
	
	char *classname = new char[strlen(arrayType)];
	strcpy(classname, arrayType+dim);
	
	Class *classRef = NULL;
	if(*classname == TYPE_CLASS) {
		classname[strlen(classname)-1] = '\0';
		classname++;
		classRef = memory->get_classref(classname);
		if(classRef == NULL) {
			classRef = memory->new_class(classname);
			frames->current->pcBack(4);
			frames->pushClinit(classRef);
			
			return;
		}
	}
	
	int32_t *count = new int32_t[dim];
	for(int i=dim-1; i>=0; i--) {
		count[i] = (int)frames->current->popOpStack();
	}
	u4 arrayRef;
	printf("%s\n", arrayType);
	arrayRef = memory->multianewarray(count, arrayType, classRef);
	frames->current->pushOpStack(TYPE_REF, arrayRef);
	
	delete classname;
}

void ifnull() {
	printf("ifnull\n");
	
	int16_t pc = frames->current->getPC()-1;
	
	u2 branch = get2byte();
	pc += (int16_t)branch;
	
	frames->current->ifnull(pc);
}

void ifnonnull() {
	printf("ifnonnull\n");
	
	int16_t pc = frames->current->getPC()-1;
	
	u2 branch = get2byte();
	pc += (int16_t)branch;
	
	frames->current->ifnonnull(pc);
}

void goto_w() {
	printf("goto_w\n");
	
	int16_t pc = frames->current->getPC()-1;
	
	u2 branch = get2byte();
	pc += (int16_t)branch;
	
	frames->current->goto_w(pc);
}

void jsr_w() {}
void breakpoint() {}
void impdep() {}
void impdep2() {}

u1 get1byte() {
	return frames->current->getCode();
}

u2 get2byte() {
	u2 bytes;
	
	bytes = frames->current->getCode();
	bytes<<=8;
	bytes |= frames->current->getCode();
	return bytes;
}

u4 get4byte() {
	u4 bytes;
	
	bytes = frames->current->getCode();
	bytes<<=8;
	bytes |= frames->current->getCode();
	bytes<<=8;
	bytes |= frames->current->getCode();
	bytes<<=8;
	bytes |= frames->current->getCode();
	return bytes;
}

void print() {
	frames->print();
	printf("\n");
	memory->print();
	printf("\n");
}