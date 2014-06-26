#include "JavaVM.hpp"

#define STACK_SIZE  100
#define CLASS_SIZE  100
#define MEMORY_SIZE 100

void loadMain(char *);
void print();

static StackFrame *frames;
static Memory     *memory;

int main(int argc, char **argv) {
	frames = new StackFrame(STACK_SIZE);
	memory = new Memory(CLASS_SIZE, MEMORY_SIZE);
	
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

void nop() {}
void aconst_null() {}
void iconst_m1() {}
void iconst_0() {}
void iconst_1() {
	printf("iconst_1\n");
	
	frames->current->iconst_1();
}

void iconst_2() {}
void iconst_3() {}
void iconst_4() {}
void iconst_5() {}
void lconst_0() {}
void lconst_1() {
	printf("lconst_1\n");
	
	frames->current->lconst_1();
}

void fconst_0() {}
void fconst_1() {
	printf("fconst_1\n");
	
	frames->current->fconst_1();
}

void fconst_2() {}
void dconst_0() {}
void dconst_1() {}
void bipush() {}
void sipush() {}
void ldc() {}
void ldc_w() {}
void ldc2_w() {}
void iload() {}
void lload() {}
void fload() {}
void dload() {}
void aload() {
	printf("aload\n");
	
}

void iload_0() {
	printf("iload_0\n");
	
}

void iload_1() {}
void iload_2() {}
void iload_3() {}
void lload_0() {}
void lload_1() {}
void lload_2() {}
void lload_3() {}
void fload_0() {}
void fload_1() {}
void fload_2() {}
void fload_3() {}
void dload_0() {}
void dload_1() {}
void dload_2() {}
void dload_3() {}
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

void aload_3() {}
void iaload() {}
void laload() {}
void faload() {}
void daload() {}
void aaload() {}
void baload() {}
void caload() {}
void saload() {}
void istore() {}
void lstore() {}
void fstore() {}
void dstore() {}
void astore() {}
void istore_0() {}
void istore_1() {}
void istore_2() {}
void istore_3() {}
void lstore_0() {}
void lstore_1() {}
void lstore_2() {}
void lstore_3() {}
void fstore_0() {}
void fstore_1() {}
void fstore_2() {}
void fstore_3() {}
void dstore_0() {}
void dstore_1() {}
void dstore_2() {}
void dstore_3() {}
void astore_0() {}
void astore_1() {
	printf("astore_1\n");
	
	frames->current->astore_1();
}

void astore_2() {}
void astore_3() {}
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

void getstatic() {}
void putstatic() {}
void getfield() {}
void putfield() {}
void invokevirtual() {
	printf("invokevirtual\n");
	
	u2 cp_index = frames->current->getCode();
	cp_index<<8;
	cp_index |= frames->current->getCode();
	
	Class *classRef = frames->current->classref;
	char *classname  = classRef->get_cp_method_class(cp_index);
	char *methodname = classRef->get_cp_method_name(cp_index);
	char *descriptor = classRef->get_cp_method_descriptor(cp_index);
	
	classRef = memory->get_classref(classname);
	if(classRef == NULL) {
		classRef = memory->new_class(classname);
		frames->current->pcBack(3);
		printf("<clinit>\n");
		return;
	}
	
	frames->invokevirtual(classRef, methodname, descriptor);
}

void invokespecial() {
	printf("invokespecial\n");
	
	u2 cp_index = frames->current->getCode();
	cp_index<<8;
	cp_index |= frames->current->getCode();
	
	Class *classRef = frames->current->classref;
	char *classname  = classRef->get_cp_method_class(cp_index);
	char *methodname = classRef->get_cp_method_name(cp_index);
	char *descriptor = classRef->get_cp_method_descriptor(cp_index);
	
	classRef = memory->get_classref(classname);
	if(classRef == NULL) {
		classRef = memory->new_class(classname);
		frames->current->pcBack(3);
		printf("<clinit>\n");
		return;
	}
	
	frames->invokespecial(classRef, methodname, descriptor);
	
}

void invokestatic() {}
void invokeinterface() {}
void invokedynamic() {}
void op_new() {
	printf("new\n");

	u2 cp_index = frames->current->getCode();
	cp_index<<8;
	cp_index |= frames->current->getCode();
	
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

void print() {
	frames->print();
	printf("\n");
	memory->print();
	printf("\n");
}