#include "JavaVM.hpp"

#define STACK_SIZE  100
#define MEMORY_SIZE 100

void loadMain(char *);
u2 get2bytes();
void print();

static StackFrame *frames;
static Memory     *memory;

int main(int argc, char **argv) {
	frames = new StackFrame(STACK_SIZE);
	memory = new Memory(MEMORY_SIZE, MEMORY_SIZE);
	
	char name[3] = "C2";
	loadMain(name);
	printf("Method main carregado!\n"); 
	printf("iniciando JavaVM\n\n"); 
	while(frames->isEmpty()) {
		u1 code = frames->current->getCode();
		printf("[%X] ",code);
		op[code]();
		print();
		printf("\nENTER para proseguir...\n");
		getchar();
	}
	
	return 0;
}

void loadMain(char *classname) {
	printf("load main\n");
	Class *temp;
	temp = memory->new_class(classname);
	
	frames->pushMain(temp);
	
	print();
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
	printf("bipush\n");
	
	u1 byte = frames->current->getCode();
	
	frames->current->bipush(byte);
}

void sipush() {
	printf("sipush\n");
	
	u2 bytes = get2bytes();
	
	frames->current->sipush(bytes);
}
	
void ldc() {}
void ldc_w() {}
void ldc2_w() {}
void iload() {
	printf("iload\n");
	
	u1 index = frames->current->getCode();
	
	frames->current->iload(index);
}

void lload() {
	printf("lload\n");
	
	u1 index = frames->current->getCode();
	
	frames->current->lload(index);
}

void fload() {
	printf("fload\n");
	
	u1 index = frames->current->getCode();
	
	frames->current->fload(index);
}

void dload() {
	printf("dload\n");
	
	u1 index = frames->current->getCode();
	
	frames->current->dload(index);
}

void aload() {
	printf("aload\n");
	
	u1 index = frames->current->getCode();
	
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

void iaload() {}
void laload() {}
void faload() {}
void daload() {}
void aaload() {}
void baload() {}
void caload() {}
void saload() {}

void istore() {
	printf("istore\n");
	
	u1 index = frames->current->getCode();
	
	frames->current->istore(index);
}

void lstore() {
	printf("lstore\n");
	
	u1 index = frames->current->getCode();
	
	frames->current->lstore(index);
}

void fstore() {
	printf("fstore\n");
	
	u1 index = frames->current->getCode();
	
	frames->current->fstore(index);
}

void dstore() {
	printf("dstore\n");
	
	u1 index = frames->current->getCode();
	
	frames->current->dstore(index);
}

void astore() {
	printf("astore\n");
	
	u1 index = frames->current->getCode();
	
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

void iastore() {}
void lastore() {}
void fastore() {}
void dastore() {}
void aastore() {}
void bastore() {}
void castore() {}
void sastrore() {}
void pop() {}
void pop2() {}
void dup() {
	printf("dup\n");
	
	frames->current->dup();
}

void dup_x1() {}
void dup_x2() {}
void dup2() {}
void dup2_x1() {}
void dup2_x2() {}
void swap() {}
void iadd() {}
void ladd() {}
void fadd() {}
void dadd() {}
void isub() {}
void lsub() {}
void fsub() {}
void dsub() {}
void imul() {}
void lmul() {}
void fmul() {}
void dmul() {}
void idiv() {}
void ldiv() {}
void fdiv() {}
void ddiv() {}
void irem() {}
void lrem() {}
void frem() {}
void drem() {}
void ineg() {}
void lneg() {}
void fneg() {}
void dneg() {}
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
void iinc() {}
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
void ifeq() {}
void ifne() {}
void iflt() {}
void ifge() {}
void ifgt() {}
void ifle() {}
void if_icmpeq() {}
void if_icmpne() {}
void if_icmplt() {}
void if_icmpge() {}
void if_cmpgt() {}
void if_icmple() {}
void if_acmpeq() {}
void if_acmpne() {}
void op_goto() {}
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
	printf("getstatic\n");
	
}

void putstatic() {
	printf("putstatic\n");
	
}

void getfield() {
	printf("getfield\n");

	u2 cp_index = get2bytes();
	
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
	printf("putfield\n");
	
	u2 cp_index = get2bytes();
	
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
	printf("invokevirtual\n");
	
	u2 cp_index = get2bytes();
	
	char *className  = frames->current->get_method_class(cp_index);
	char *methodName = frames->current->get_method_name(cp_index);
	char *descriptor = frames->current->get_method_descriptor(cp_index);
	
	Class *classRef = memory->get_classref(className);
	if(classRef == NULL) {
		classRef = memory->new_class(className);
		frames->current->pcBack(3);
		printf("<clinit>\n");
		return;
	}
	
	frames->invokevirtual(classRef, methodName, descriptor);
}

void invokespecial() {
	printf("invokespecial\n");
	
	u2 cp_index = get2bytes();
	
	char *className  = frames->current->get_method_class(cp_index);
	char *methodName = frames->current->get_method_name(cp_index);
	char *descriptor = frames->current->get_method_descriptor(cp_index);
	
	Class *classRef = memory->get_classref(className);
	if(classRef == NULL) {
		classRef = memory->new_class(className);
		frames->current->pcBack(3);
		printf("<clinit>\n");
		return;
	}
	
	frames->invokespecial(classRef, methodName, descriptor);
	
}

void invokestatic() {}
void invokeinterface() {}
void invokedynamic() {}
void op_new() {
	printf("new\n");

	u2 cp_index = get2bytes();
	
	Class *temp = frames->current->classref;
	char *classname = temp->get_cp_class_name(cp_index);
	
	temp = memory->get_classref(classname);
	if(temp == NULL) {
		temp = memory->new_class(classname);
		frames->current->pcBack(3);
		return;
	}
	
	u4 instance = memory->op_new(temp);
	frames->current->pushOpStack(TYPE_REF, instance);
}

void newarray() {}
void anewarray() {}
void arraylength() {}
void athrow() {}
void checkcast() {}
void instanceof() {}
void monitorenter() {}
void monitorexit() {}
void wide() {}
void multianewarray() {}
void ifnull() {}
void ifnonnull() {}
void goto_w() {}
void jsr_w() {}
void breakpoint() {}
void impdep() {}
void impdep2() {}

u2 get2bytes() {
	u2 bytes;
	
	bytes = frames->current->getCode();
	bytes<<8;
	bytes |= frames->current->getCode();
	return bytes;
}

void print() {
	frames->print();
	printf("\n");
	memory->print();
	printf("\n");
}