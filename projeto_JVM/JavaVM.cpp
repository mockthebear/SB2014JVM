#include "JavaVM.hpp"

#define STACK_SIZE  100
#define MEMORY_SIZE 100

void run(char *);
void classfile(char *);

void loadMain(char *);
void clinit(Class *);

int checkInterfaces(Class *classS, char *classnameT);
int checkType(MemoryData *objectref, char *classnameT);

int isPrimitive(char *type);
u1 get1byte();
u2 get2byte();
u4 get4byte();
char *getPath(char *);
void print();
void printHelp();

static StackFrame *frames;
static Memory     *memory;

static int printEnable;

int main(int argc, char **argv) {
	frames = new StackFrame(STACK_SIZE);
	memory = new Memory(MEMORY_SIZE, MEMORY_SIZE);
	char *fileName;

	if(argc < 2) {
		printHelp();
		return 0;
	}
	if (strcmp(argv[1], "-c") == 0) {
		fileName = getPath(argv[2]);
		memory->setPath(argv[2]);
		
		classfile(fileName);
	} else if(strcmp(argv[1], "-d") == 0) {
		fileName = getPath(argv[2]);
		memory->setPath(argv[2]);
		printEnable = 1;
		
		run(fileName);
	} else if(argv[1][0] != '-') {
		fileName = getPath(argv[1]);
		memory->setPath(argv[1]);
		printEnable = 0;
		
		run(fileName);
	} else {
		printHelp();
	}

	return 0;
}

void run(char *className) {
	loadMain(className);

	while(frames->isEmpty()) {
		u1 code = frames->current->getCode();
		if (op[code] == NULL){
				printf("[Error] Opcode [%X] Is nullptr: pc: %d\n",code,frames->current->getPC()-1);
			return;
		}else{
            op[code]();
			if(printEnable)
				print();
		}
		if(printEnable) {
			printf("ENTER para proseguir...\n");
			getchar();
		}
	}
	
}

void classfile(char *className) {
	Class *classRef;
	classRef = memory->new_class(className);
	classRef->print();
}

void loadMain(char *classname) {
	Class *classRef;
	classRef = memory->new_class(classname);

	frames->pushMain(classRef);

	if(printEnable) {
		print();
		printf("load main\n");
		printf("Method main carregado!\n");
		printf("iniciando JavaVM\n\n");
	}
	clinit(classRef);
}

void clinit(Class *classRef) {
	u1 code = 0x0;
	u1 returnCode = 0xB1;
		
	if ( frames->pushClinit(classRef) ) {
		if(printEnable)
			printf("\nInicializando nova classe carregada.\n");
		while(code != returnCode) {
			code = frames->current->getCode();
			if (op[code] == NULL){
				printf("[Error] Opcode [%X] Is nullptr: pc: %d\n",code,frames->current->getPC()-1);
				exit(0);
			} else {
				op[code]();
				if(printEnable)
					print();
			}
			if(printEnable) {
				printf("ENTER para proseguir...\n");
				getchar();
			}
		}
		if(printEnable)
			printf("Inicializacao terminada\n");
	}
}

void nop() {
	if(printEnable) {
		frames->current->printCode();
		printf("nop\n");
	}
}

void aconst_null() {
	if(printEnable) {
		frames->current->printCode();
		printf("aconst_null\n");
	}
	frames->current->aconst_null();
}

void iconst_m1() {
	if(printEnable) {
		frames->current->printCode();
		printf("iconst_m1\n");
	}
	frames->current->iconst_m1();
}

void iconst_0() {
	if(printEnable) {
		frames->current->printCode();
		printf("iconst_0\n");
	}
	frames->current->iconst_0();
}

void iconst_1() {
	if(printEnable) {
		frames->current->printCode();
		printf("iconst_1\n");
	}
	frames->current->iconst_1();
}

void iconst_2() {
	if(printEnable) {
		frames->current->printCode();
		printf("iconst_2\n");
	}
	frames->current->iconst_2();
}

void iconst_3() {
	if(printEnable) {
		frames->current->printCode();
		printf("iconst_3\n");
	}
	frames->current->iconst_3();
}

void iconst_4() {
	if(printEnable) {
		frames->current->printCode();
		printf("iconst_4\n");
	}
	frames->current->iconst_4();
}

void iconst_5() {
	if(printEnable) {
		frames->current->printCode();
		printf("iconst_5\n");
	}
	frames->current->iconst_5();
}

void lconst_0() {
	if(printEnable) {
		frames->current->printCode();
		printf("lconst_0\n");
	}
	frames->current->lconst_0();
}

void lconst_1() {
	if(printEnable) {
		frames->current->printCode();
		printf("lconst_1\n");
	}
	frames->current->lconst_1();
}

void fconst_0() {
	if(printEnable) {
		frames->current->printCode();
		printf("fconst_0\n");
	}
	frames->current->fconst_0();
}

void fconst_1() {
	if(printEnable) {
		frames->current->printCode();
		printf("fconst_1\n");
	}
	frames->current->fconst_1();
}

void fconst_2() {
	if(printEnable) {
		frames->current->printCode();
		printf("fconst_2\n");
	}
	frames->current->fconst_2();
}

void dconst_0() {
	if(printEnable) {
		frames->current->printCode();
		printf("dconst_0\n");
	}
	frames->current->dconst_0();
}

void dconst_1() {
	if(printEnable) {
		frames->current->printCode();
		printf("dconst_1\n");
	}
	frames->current->dconst_1();
}

void bipush() {
	u1 byte = get1byte();

	if(printEnable) {
		frames->current->printCode();
		printf("bipush");
		printf(" %d\n",byte);
	}
	frames->current->bipush(byte);
}

void sipush() {
	u2 bytes = get2byte();

	if(printEnable) {
		frames->current->printCode();
		printf("sipush");
		printf(" %d\n",bytes);
	}
	frames->current->sipush(bytes);
}

void ldc() {
	u2 cp_index = get1byte();
	
	if(printEnable) {
		frames->current->printCode();
		printf("ldc");
		printf("  #%d\n",cp_index);
	}
	frames->current->ldc(cp_index);
}

void ldc_w() {
	u2 cp_index = get2byte();
	
	if(printEnable) {
		frames->current->printCode();
		printf("ldc_w");
		printf("  #%d\n",cp_index);
	}
	frames->current->ldc_w(cp_index);
}

void ldc2_w() {
	u2 cp_index = get2byte();
	
	if(printEnable) {
		frames->current->printCode();
		printf("ldc2_w");
		printf("  #%d\n",cp_index);
	}
	frames->current->ldc2_w(cp_index);
}

void iload() {
	u2 index;
	
	if (frames->current->wideFlag){
        frames->current->wideFlag = false;
        index = get2byte();
	}else{
        index = get1byte();
	}
	if(printEnable) {
		frames->current->printCode();
		printf("iload");
		printf(" %d\n",index);
	}
	frames->current->iload(index);
}

void lload() {
    u2 index;
	if (frames->current->wideFlag){
        frames->current->wideFlag = false;
        index = get2byte();
	}else{
        index = get1byte();
	}
	if(printEnable) {
		frames->current->printCode();
		printf("lload");
		printf(" %d\n",index);
	}
	frames->current->lload(index);
}

void fload() {
    u2 index;
	if (frames->current->wideFlag){
        frames->current->wideFlag = false;
        index = get2byte();
	}else{
        index = get1byte();
	}
	if(printEnable) {
		frames->current->printCode();
		printf("fload\n");
		printf(" %d\n",index);
	}
	frames->current->fload(index);
}

void dload() {
    u2 index;
	if (frames->current->wideFlag){
        frames->current->wideFlag = false;
        index = get2byte();
	}else{
        index = get1byte();
	}
	if(printEnable) {
		frames->current->printCode();
		printf("dload\n");
		printf(" %d\n",index);
	}
	frames->current->dload(index);
}

void aload() {
    u2 index;
	if (frames->current->wideFlag){
        frames->current->wideFlag = false;
        index = get2byte();
	}else{
        index = get1byte();
	}
	if(printEnable) {
		frames->current->printCode();
		printf("aload\n");
		printf(" %d\n",index);
	}
	frames->current->aload(index);
}

void iload_0() {
	if(printEnable) {
		frames->current->printCode();
		printf("iload_0\n");
	}
	frames->current->iload_0();
}

void iload_1() {
	if(printEnable) {
		frames->current->printCode();
		printf("iload_1\n");
	}
	frames->current->iload_1();
}

void iload_2() {
	if(printEnable) {
		frames->current->printCode();
		printf("iload_2\n");
	}
	frames->current->iload_2();
}

void iload_3() {
	if(printEnable) {
		frames->current->printCode();
		printf("iload_3\n");
	}
	frames->current->iload_3();
}

void lload_0() {
	if(printEnable) {
		frames->current->printCode();
		printf("lload_0\n");
	}
	frames->current->lload_0();
}

void lload_1() {
	if(printEnable) {
		frames->current->printCode();
		printf("lload_1\n");
	}
	frames->current->lload_1();
}

void lload_2() {
	if(printEnable) {
		frames->current->printCode();
		printf("lload_2\n");
	}
	frames->current->lload_2();
}

void lload_3() {
	if(printEnable) {
		frames->current->printCode();
		printf("lload_3\n");
	}

	frames->current->lload_3();
}

void fload_0() {
	if(printEnable) {
		frames->current->printCode();
		printf("fload_0\n");
	}

	frames->current->fload_0();
}

void fload_1() {
	if(printEnable) {
		frames->current->printCode();
		printf("fload_1\n");
	}

	frames->current->fload_1();
}

void fload_2() {
	if(printEnable) {
		frames->current->printCode();
		printf("fload_2\n");
	}

	frames->current->fload_2();
}

void fload_3() {
	if(printEnable) {
		frames->current->printCode();
		printf("fload_3\n");
	}

	frames->current->fload_3();
}

void dload_0() {
	if(printEnable) {
		frames->current->printCode();
		printf("dload_0\n");
	}

	frames->current->dload_0();
}

void dload_1() {
	if(printEnable) {
		frames->current->printCode();
		printf("dload_1\n");
	}

	frames->current->dload_1();
}

void dload_2() {
	if(printEnable) {
		frames->current->printCode();
		printf("dload_2\n");
	}

	frames->current->dload_2();
}

void dload_3() {
	if(printEnable) {
		frames->current->printCode();
		printf("dload_3\n");
	}

	frames->current->dload_3();
}

void aload_0() {
	if(printEnable) {
		frames->current->printCode();
		printf("aload_0\n");
	}

	frames->current->aload_0();
}

void aload_1() {
	if(printEnable) {
		frames->current->printCode();
		printf("aload_1\n");
	}

	frames->current->aload_1();
}

void aload_2() {
	if(printEnable) {
		frames->current->printCode();
		printf("aload_2\n");
	}

	frames->current->aload_2();
}

void aload_3() {
	if(printEnable) {
		frames->current->printCode();
		printf("aload_3\n");
	}

	frames->current->aload_3();
}

void iaload() {
	if(printEnable) {
		frames->current->printCode();
		printf("iaload\n");
	}

	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();
	u4 value;

	memory->iaload(arrayRef, index, &value);
	frames->current->pushOpStack(TYPE_INT, value);
}

void laload() {
	if(printEnable) {
		frames->current->printCode();
		printf("laload\n");
	}

	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();
	u4 value[2];

	memory->laload(arrayRef, index, value);
	frames->current->pushOpStack(TYPE_LONG, value[0]);
	frames->current->pushOpStack(TYPE_LONG, value[1]);
}

void faload() {
	if(printEnable) {
		frames->current->printCode();
		printf("faload\n");
	}

	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();
	u4 value;

	memory->faload(arrayRef, index, &value);
	frames->current->pushOpStack(TYPE_FLOAT, value);
}

void daload() {
	if(printEnable) {
		frames->current->printCode();
		printf("daload\n");
	}

	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();
	u4 value[2];

	memory->daload(arrayRef, index, value);
	frames->current->pushOpStack(TYPE_DOUBLE, value[0]);
	frames->current->pushOpStack(TYPE_DOUBLE, value[1]);
}

void aaload() {
	if(printEnable) {
		frames->current->printCode();
		printf("aaload\n");
	}

	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();
	u4 value;

	memory->aaload(arrayRef, index, &value);
	frames->current->pushOpStack(TYPE_REF, value);
}

void baload() {
	if(printEnable) {
		frames->current->printCode();
		printf("baload\n");
	}

	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();
	u4 value;

	memory->baload(arrayRef, index, &value);
	frames->current->pushOpStack(TYPE_INT, value);
}

void caload() {
	if(printEnable) {
		frames->current->printCode();
		printf("caload\n");
	}

	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();
	u4 value;

	memory->caload(arrayRef, index, &value);
	frames->current->pushOpStack(TYPE_INT, value);
}

void saload() {
	if(printEnable) {
		frames->current->printCode();
		printf("saload\n");
	}

	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();
	u4 value;

	memory->saload(arrayRef, index, &value);
	frames->current->pushOpStack(TYPE_INT, value);
}

void istore() {
	u2 index;
	if (frames->current->wideFlag){
        frames->current->wideFlag = false;
        index = get2byte();
	}else{
        index = get1byte();
	}
	if(printEnable) {
		frames->current->printCode();
		printf("istore");
		printf("  %d\n",index);
	}
	
	frames->current->istore(index);
}

void lstore() {
	u2 index;
	if (frames->current->wideFlag){
        frames->current->wideFlag = false;
        index = get2byte();
	}else{
        index = get1byte();
	}
	if(printEnable) {
		frames->current->printCode();
		printf("lstore");
		printf("  %d\n",index);
	}
	frames->current->lstore(index);
}

void fstore() {

	u2 index;
	if (frames->current->wideFlag){
        frames->current->wideFlag = false;
        index = get2byte();
	}else{
        index = get1byte();
	}
	if(printEnable) {
		frames->current->printCode();
		printf("fstore");
		printf("  %d\n",index);
	}

	frames->current->fstore(index);
}

void dstore() {

	u2 index;
	if (frames->current->wideFlag){
        frames->current->wideFlag = false;
        index = get2byte();
	}else{
        index = get1byte();
	}
	if(printEnable) {
		frames->current->printCode();
		printf("dstore");
		printf("  %d\n",index);
	}

	frames->current->dstore(index);
}

void astore() {

	u2 index;
	if (frames->current->wideFlag){
        frames->current->wideFlag = false;
        index = get2byte();
	}else{
        index = get1byte();
	}
	if(printEnable) {
		frames->current->printCode();
		printf("astore ");
		printf("  %d\n",index);
	}
	frames->current->astore(index);
}

void istore_0() {
	if(printEnable) {
		frames->current->printCode();
		printf("istore_0\n");
	}

	frames->current->istore_0();
}

void istore_1() {
	if(printEnable) {
		frames->current->printCode();
		printf("istore_1\n");
	}

	frames->current->istore_1();
}

void istore_2() {
	if(printEnable) {
		frames->current->printCode();
		printf("istore_2\n");
	}

	frames->current->istore_2();
}

void istore_3() {
	if(printEnable) {
		frames->current->printCode();
		printf("istore_3\n");
	}

	frames->current->istore_3();
}

void lstore_0() {
	if(printEnable) {
		frames->current->printCode();
		printf("lstore_0\n");
	}

	frames->current->lstore_0();
}

void lstore_1() {
	if(printEnable) {
		frames->current->printCode();
		printf("lstore_1\n");
	}

	frames->current->lstore_1();
}

void lstore_2() {
	if(printEnable) {
		frames->current->printCode();
		printf("lstore_2\n");
	}

	frames->current->lstore_2();
}

void lstore_3() {
	if(printEnable) {
		frames->current->printCode();
		printf("lstore_3\n");
	}

	frames->current->lstore_3();
}


void fstore_0() {
	if(printEnable) {
		frames->current->printCode();
		printf("fstore_0\n");
	}

	frames->current->fstore_0();
}

void fstore_1() {
	if(printEnable) {
		frames->current->printCode();
		printf("fstore_1\n");
	}

	frames->current->fstore_1();
}

void fstore_2() {
	if(printEnable) {
		frames->current->printCode();
		printf("fstore_2\n");
	}

	frames->current->fstore_2();
}

void fstore_3() {
	if(printEnable) {
		frames->current->printCode();
		printf("fstore_3\n");
	}

	frames->current->fstore_3();
}

void dstore_0() {
	if(printEnable) {
		frames->current->printCode();
		printf("dstore_0\n");
	}

	frames->current->dstore_0();
}

void dstore_1() {
	if(printEnable) {
		frames->current->printCode();
		printf("dstore_1\n");
	}

	frames->current->dstore_1();
}

void dstore_2() {
	if(printEnable) {
		frames->current->printCode();
		printf("dstore_2\n");
	}

	frames->current->dstore_2();
}

void dstore_3() {
	if(printEnable) {
		frames->current->printCode();
		printf("dstore_3\n");
	}

	frames->current->dstore_3();
}

void astore_0() {
	if(printEnable) {
		frames->current->printCode();
		printf("astore_0\n");
	}

	frames->current->astore_0();


}

void astore_1() {
	if(printEnable) {
		frames->current->printCode();
		printf("astore_1\n");
	}

	frames->current->astore_1();
}

void astore_2() {
	if(printEnable) {
		frames->current->printCode();
		printf("astore_2\n");
	}

	frames->current->astore_2();
}

void astore_3() {
	if(printEnable) {
		frames->current->printCode();
		printf("astore_3\n");
	}

	frames->current->astore_3();
}

void iastore() {
	if(printEnable) {
		frames->current->printCode();
		printf("iastore\n");
	}

	u4 value = frames->current->popOpStack();
	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();

	memory->iastore(arrayRef, index, &value);
}

void lastore() {
	if(printEnable) {
		frames->current->printCode();
		printf("lastore\n");
	}

	u4 value[2];
	value[1]= frames->current->popOpStack();
	value[0]= frames->current->popOpStack();
	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();

	memory->lastore(arrayRef, index, value);
}

void fastore() {
	if(printEnable) {
		frames->current->printCode();
		printf("fastore\n");
	}

	u4 value = frames->current->popOpStack();
	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();

	memory->fastore(arrayRef, index, &value);
}

void dastore() {
	if(printEnable) {
		frames->current->printCode();
		printf("dastore\n");
	}

	u4 value[2];
	value[1]= frames->current->popOpStack();
	value[0]= frames->current->popOpStack();
	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();

	memory->dastore(arrayRef, index, value);
}

void aastore() {
	if(printEnable) {
		frames->current->printCode();
		printf("aastore\n");
	}

	u4 value = frames->current->popOpStack();
	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();

	memory->aastore(arrayRef, index, &value);
}

void bastore() {
	if(printEnable) {
		frames->current->printCode();
		printf("bastore\n");
	}

	u4 value = frames->current->popOpStack();
	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();

	memory->bastore(arrayRef, index, &value);
}

void castore() {
	if(printEnable) {
		frames->current->printCode();
		printf("castore\n");
	}

	u4 value = frames->current->popOpStack();
	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();

	memory->castore(arrayRef, index, &value);
}

void sastore() {
	if(printEnable) {
		frames->current->printCode();
		printf("sastore\n");
	}

	u4 value = frames->current->popOpStack();
	u4 index = frames->current->popOpStack();
	u4 arrayRef = frames->current->popOpStack();

	memory->sastore(arrayRef, index, &value);
}

void pop() {
	if(printEnable) {
		frames->current->printCode();
		printf("pop\n");
	}

	frames->current->pop();
}

void pop2() {
	if(printEnable) {
		frames->current->printCode();
		printf("pop2\n");
	}

	frames->current->pop2();
}

void dup() {
	if(printEnable) {
		frames->current->printCode();
		printf("dup\n");
	}

	frames->current->dup();
}

void dup_x1() {
	if(printEnable) {
		frames->current->printCode();
    	printf("dup_x1\n");
	}
	
	frames->current->dup_x1();
}

void dup_x2() {
	if(printEnable) {
		frames->current->printCode();
    	printf("dup_x2\n");
	}
	
	frames->current->dup_x2();
}

void dup2() {
	if(printEnable) {
		frames->current->printCode();
    	printf("dup2\n");
	}
	
	frames->current->dup2();
}

void dup2_x1() {
	if(printEnable) {
		frames->current->printCode();
    	printf("dup2_x1\n");
	}
	
	frames->current->dup2_x1();
}

void dup2_x2() {
	if(printEnable) {
		frames->current->printCode();
    	printf("dup2_x2\n");
	}
	
	frames->current->dup2_x2();
}

void swap() {
	if(printEnable) {
		frames->current->printCode();
		printf("swap\n");
	}

	frames->current->swap();

}

void iadd() {
	if(printEnable) {
		frames->current->printCode();
		printf("iadd\n");
	}

	frames->current->iadd();
}

void ladd() {
	if(printEnable) {
		frames->current->printCode();
		printf("ladd\n");
	}

	frames->current->ladd();
}


void fadd() {
	if(printEnable) {
		frames->current->printCode();
		printf("fadd\n");
	}

	frames->current->fadd();
}

void dadd() {
	if(printEnable) {
		frames->current->printCode();
		printf("dadd\n");
	}

	frames->current->dadd();
}

void isub() {
	if(printEnable) {
		frames->current->printCode();
		printf("isub\n");
	}

	frames->current->isub();
}

void lsub() {
	if(printEnable) {
		frames->current->printCode();
		printf("lsub\n");
	}

	frames->current->lsub();
}

void fsub() {
	if(printEnable) {
		frames->current->printCode();
		printf("fsub\n");
	}

	frames->current->fsub();
}

void dsub() {
	if(printEnable) {
		frames->current->printCode();
		printf("dsub\n");
	}

	frames->current->dsub();
}

void imul() {
	if(printEnable) {
		frames->current->printCode();
		printf("imul\n");
	}

	frames->current->imul();
}

void lmul() {
	if(printEnable) {
		frames->current->printCode();
		printf("lmul\n");
	}

	frames->current->lmul();
}

void fmul() {
	if(printEnable) {
		frames->current->printCode();
		printf("fmul\n");
	}

	frames->current->fmul();
}

void dmul() {
	if(printEnable) {
		frames->current->printCode();
		printf("dmul\n");
	}

	frames->current->dmul();
}

void idiv() {
	if(printEnable) {
		frames->current->printCode();
		printf("idiv\n");
	}

	frames->current->idiv();
}

void ldiv() {
	if(printEnable) {
		frames->current->printCode();
		printf("ldiv\n");
	}

	frames->current->ldiv();
}

void fdiv() {
	if(printEnable) {
		frames->current->printCode();
		printf("fdiv\n");
	}

	frames->current->fdiv();
}

void ddiv() {
	if(printEnable) {
		frames->current->printCode();
		printf("ddiv\n");
	}

	frames->current->ddiv();
}

void irem() {
	if(printEnable) {
		frames->current->printCode();
		printf("irem\n");
	}

	frames->current->irem();
}

void lrem() {
	if(printEnable) {
		frames->current->printCode();
		printf("lrem\n");
	}

	frames->current->lrem();
}

void frem() {
	if(printEnable) {
		frames->current->printCode();
		printf("frem\n");
	}

	frames->current->frem();
}

void drem() {
	if(printEnable) {
		frames->current->printCode();
		printf("drem\n");
	}

	frames->current->drem();
}

void ineg() {
	if(printEnable) {
		frames->current->printCode();
		printf("ineg\n");
	}

	frames->current->ineg();
}

void lneg() {
	if(printEnable) {
		frames->current->printCode();
		printf("lneg\n");
	}

	frames->current->lneg();
}

void fneg() {
	if(printEnable) {
		frames->current->printCode();
		printf("fneg\n");
	}

	frames->current->fneg();
}

void dneg() {
	if(printEnable) {
		frames->current->printCode();
		printf("dneg\n");
	}

	frames->current->dneg();
}

void ishl() {
	if(printEnable) {
		frames->current->printCode();
    	printf("ishl\n");
	}
	frames->current->ishl();
}

void lshl() {
	if(printEnable) {
		frames->current->printCode();
    	printf("lshl\n");
	}
	frames->current->lshl();
}

void ishr(){
	if(printEnable) {
		frames->current->printCode();
    	printf("ishr\n");
	}
	frames->current->ishr();
}

void lshr() {
	if(printEnable) {
		frames->current->printCode();
    	printf("lshr\n");
	}
	frames->current->lshr();
}

void iushr() {
	if(printEnable) {
		frames->current->printCode();
    	printf("iushr\n");
	}
	frames->current->iushr();
}

void lushr() {
	if(printEnable) {
		frames->current->printCode();
    	printf("lushr\n");
	}
	frames->current->lushr();
}

void iand() {
	if(printEnable) {
		frames->current->printCode();
    	printf("iand\n");
	}
	frames->current->iand();
}

void land(){
	if(printEnable) {
		frames->current->printCode();
		printf("land\n");
	}
	frames->current->land();
}

void ior() {
	if(printEnable) {
		frames->current->printCode();
    	printf("ior\n");
	}
	frames->current->ior();
}

void lor() {
	if(printEnable) {
		frames->current->printCode();
		printf("lor\n");
	}
	frames->current->lor();
}
void ixor() {
	if(printEnable) {
		frames->current->printCode();
    	printf("ixor\n");
	}
	frames->current->ixor();
}

void lxor() {
	if(printEnable) {
		frames->current->printCode();
		printf("lxor\n");
	}
	frames->current->lxor();
}

void iinc() {
    u2 index;
	if (frames->current->wideFlag){
        frames->current->wideFlag = false;
        index = get2byte();
	}else{
        index = get1byte();
	}
	u1 value = get1byte();

	if(printEnable) {
		frames->current->printCode();
		printf("iinc");
		printf("  %d %d\n",index,value);
	}
	
	frames->current->iinc(index, value);
}

void i2l() {
	if(printEnable) {
		frames->current->printCode();
    	printf("i2l\n");
	}
	frames->current->i2l();
}

void i2f() {
	if(printEnable) {
		frames->current->printCode();
    	printf("i2f\n");
	}
	frames->current->i2f();
}

void i2d() {
	if(printEnable) {
		frames->current->printCode();
    	printf("i2d\n");
	}
	frames->current->i2d();
}

void l2i() {
	if(printEnable) {
		frames->current->printCode();
    	printf("l2i\n");
	}
	frames->current->l2i();
}

void l2f() {
	if(printEnable) {
		frames->current->printCode();
    	printf("l2f\n");
	}
	frames->current->l2f();
}

void l2d() {
	if(printEnable) {
		frames->current->printCode();
    	printf("l2d\n");
	}
	frames->current->l2d();
}

void f2i() {
	if(printEnable) {
		frames->current->printCode();
    	printf("f2i\n");
	}
	frames->current->f2i();
}
void f2l() {
	if(printEnable) {
		frames->current->printCode();
    	printf("f2l\n");
	}
	frames->current->f2l();
}

void f2d() {
	if(printEnable) {
		frames->current->printCode();
    	printf("f2d\n");
	}
	frames->current->f2d();
}

void d2i() {
	if(printEnable) {
		frames->current->printCode();
        printf("d2i\n");
	}
	frames->current->d2i();
}

void d2l() {
	if(printEnable) {
		frames->current->printCode();
    	printf("d2l\n");
	}
	frames->current->d2l();
}

void d2f() {
	if(printEnable) {
		frames->current->printCode();
    	printf("d2f\n");
	}
	frames->current->d2f();
}

void i2b() {
	if(printEnable) {
		frames->current->printCode();
    	printf("i2b\n");
	}
	frames->current->i2b();
}

void i2c() {
	if(printEnable) {
		frames->current->printCode();
    	printf("i2c\n");
	}
	frames->current->i2c();
}

void i2s() {
	if(printEnable) {
		frames->current->printCode();
    	printf("i2s\n");
	}
	frames->current->i2s();
}

void lcmp() {
	if(printEnable) {
		frames->current->printCode();
    	printf("lcmp\n");
	}
	frames->current->lcmp();
}

void fcmpl() {
	if(printEnable) {
		frames->current->printCode();
    	printf("lcmp\n");
	}
	frames->current->fcmpl();
}

void fcmpg() {
	if(printEnable) {
		frames->current->printCode();
    	printf("fcmpg\n");
	}
	frames->current->fcmpg();
}

void dcmpl() {
	if(printEnable) {
		frames->current->printCode();
    	printf("dcmpl\n");
	}
	frames->current->dcmpl();
}

void dcmpg() {
	if(printEnable) {
		frames->current->printCode();
    	printf("dcmpg\n");
	}
	frames->current->dcmpg();
}

void ifeq() {
	int16_t pc = frames->current->getPC()-1;

	u2 branch = get2byte();
	pc += (int16_t)branch;

	if(printEnable) {
		frames->current->printCode();
		printf("ifeq");
		printf("  %d\n",pc);
	}
	frames->current->ifeq(pc);
}

void ifne() {
	int16_t pc = frames->current->getPC()-1;

	u2 branch = get2byte();
	pc += (int16_t)branch;
	
	if(printEnable) {
		frames->current->printCode();
		printf("ifne");
		printf("  %d\n",pc);
	}
	frames->current->ifne(pc);
}

void iflt() {
	int16_t pc = frames->current->getPC()-1;

	int16_t branch = (int16_t)get2byte();
	pc += branch;
	
	if(printEnable) {
		frames->current->printCode();
		printf("iflt");
		printf("  %d\n",pc);
	}

	frames->current->iflt(pc);
}

void ifge() {
	int16_t pc = frames->current->getPC()-1;

	u2 branch = get2byte();
	pc += (int16_t)branch;
	
	if(printEnable) {
		frames->current->printCode();
		printf("ifge");
		printf("  %d\n",pc);
	}

	frames->current->ifge(pc);
}

void ifgt() {
	int16_t pc = frames->current->getPC()-1;

	u2 branch = get2byte();
	pc += (int16_t)branch;
	
	if(printEnable) {
		frames->current->printCode();
		printf("ifgt");
		printf("  %d\n",pc);
	}

	frames->current->ifgt(pc);
}

void ifle() {
	int16_t pc = frames->current->getPC()-1;

	u2 branch = get2byte();
	pc += (int16_t)branch;
	
	if(printEnable) {
		frames->current->printCode();
		printf("ifle");
		printf("  %d\n",pc);
	}

	frames->current->ifle(pc);
}

void if_icmpeq() {
	int16_t pc = frames->current->getPC()-1;

	u2 branch = get2byte();
	pc += (int16_t)branch;

	if(printEnable) {
		frames->current->printCode();
		printf("if_icmpeq");
		printf("  %d\n",pc);
	}
	frames->current->if_icmpeq(pc);
}

void if_icmpne() {
	int16_t pc = frames->current->getPC()-1;

	u2 branch = get2byte();
	pc += (int16_t)branch;

	if(printEnable) {
		frames->current->printCode();
		printf("if_icmpne");
		printf("  %d\n",pc);
	}

	frames->current->if_icmpne(pc);
}

void if_icmplt() {
	int16_t pc = frames->current->getPC()-1;

	u2 branch = get2byte();
	pc += (int16_t)branch;

	if(printEnable) {
		frames->current->printCode();
		printf("if_icmplt");
		printf("  %d\n",pc);
	}

	frames->current->if_icmplt(pc);
}

void if_icmpge() {

	int16_t pc = frames->current->getPC()-1;

	u2 branch = get2byte();
	pc += (int16_t)branch;

	if(printEnable) {
		frames->current->printCode();
		printf("if_icmpge");
		printf("  %d\n",pc);
	}

	frames->current->if_icmpge(pc);
}

void if_icmpgt() {

	int16_t pc = frames->current->getPC()-1;

	u2 branch = get2byte();
	pc += (int16_t)branch;

	if(printEnable) {
		frames->current->printCode();
		printf("if_icmpgt");
		printf("  %d\n",pc);
	}

	frames->current->if_icmpgt(pc);
}

void if_icmple() {

	int16_t pc = frames->current->getPC()-1;

	u2 branch = get2byte();
	pc += (int16_t)branch;

	if(printEnable) {
		frames->current->printCode();
		printf("if_icmple");
		printf("  %d\n",pc);
	}

	frames->current->if_icmple(pc);
}

void if_acmpeq() {

	int16_t pc = frames->current->getPC()-1;

	u2 branch = get2byte();
	pc += (int16_t)branch;

	if(printEnable) {
		frames->current->printCode();
		printf("if_acmpeq");
		printf("  %d\n",pc);
	}

	frames->current->if_acmpeq(pc);
}

void if_acmpne() {

	int16_t pc = frames->current->getPC()-1;

	u2 branch = get2byte();
	pc += (int16_t)branch;

	if(printEnable) {
		frames->current->printCode();
		printf("if_acmpne");
		printf("  %d\n",pc);
	}

	frames->current->if_acmpne(pc);
}

void op_goto() {

	int16_t pc = frames->current->getPC()-1;

	u2 branch = get2byte();
	pc += (int16_t)branch;

	if(printEnable) {
		frames->current->printCode();
		printf("goto");
		printf("  %d\n",pc);
	}

	frames->current->op_goto(pc);

}

void jsr() {

	int16_t pc = frames->current->getPC()-1;

	int branch = get2byte();
	frames->current->pushOpStack( TYPE_INT ,pc);
	pc += (int16_t)branch;

	if(printEnable) {
		frames->current->printCode();
    	printf("jsr");
		printf("  %d\n",pc);
	}
	frames->current->op_goto(pc);

}
void ret() {
    u2 index;
    if (frames->current->wideFlag){
        frames->current->wideFlag = false;
        index = get2byte();
	}else{
        index = get1byte();
	}
    //TODO
    Operand op;
	op = frames->current->varArray->load(index);

	if(printEnable) {
		frames->current->printCode();
    	printf("ret");
		printf("  %d\n",index);
	}

    frames->current->op_goto(op.bytes);

}
void tableswitch()
{
	if(printEnable) {
		frames->current->printCode();
		printf("tableswitch\n");
	}
	u4 index 	= frames->current->popOpStack(),
		pc    	= frames->current->getPC()-1 ,
		i 	= 0,
		deft,
		low,
		high,
		target,
		padding =  ((pc+1) % 4);
	if (padding != 0){
		padding = 4-padding;
	}

	for (i = 0; i < padding; i++)
		get1byte();
		
	deft = get4byte();
	low  = get4byte();
	high = get4byte();

	if (index < low | index > high)
	{
		target = pc + deft;
		frames->current->setPC(target);
	}
	else
	{
		int *vet = new int[((high - low) + 1)];
		for (i = 1; i <= ((high - low) + 1); i++)
		{
			target = get4byte();
			vet[i-1] = target+pc;
			//frames->current->setPC(pc + target);
		}
		frames->current->setPC( vet[index-1]);
		delete[] vet;
	}
}


void lookupswitch()
{
	if(printEnable) {
		frames->current->printCode();
		printf("lookupswitch\n");
	}
	int32_t 	key = frames->current->popOpStack(),
			_default,
			npairs,
			*vet,
			tmp = 0;
	uint16_t 	pc  = frames->current->getPC() - 1;
	uint8_t		padding = ((pc + 1) % 4);
    int32_t i;


	if (padding != 0)
		padding = 4 - padding;

   // 	printf("Pc: %d\n",pc);

	for (i = 1; i < padding; i++)
		get1byte();
	_default = get4byte();
	//	printf("Default: %d\n",_default);

	npairs   = get4byte();
	//	printf("npairs: %d\n",npairs);

	if (npairs >= 0)
	{
		vet = new int32_t [npairs];
		for (i = 1; i <= npairs; i++)
		{
			vet[i-1] = get4byte();
			get4byte();


			//	printf("Vet[%d] = %d \n",i,vet[i-1]);
			if (vet[i-1] == key)
				tmp = pc + key;
		}
		if (tmp == 0)
			pc = pc + _default;
		else
			pc = pc + tmp;
		frames->current->setPC(pc);
		//	printf("Final pc: %d\n",pc);
		delete[] vet;
	}
}

void ireturn() {
	if(printEnable) {
		frames->current->printCode();
		printf("ireturn\n");
	}

	frames->ireturn();
}

void lreturn() {
	if(printEnable) {
		frames->current->printCode();
		printf("lreturn\n");
	}

	frames->lreturn();
}

void freturn() {
	if(printEnable) {
		frames->current->printCode();
		printf("freturn\n");
	}

	frames->freturn();
}

void dreturn() {
	if(printEnable) {
		frames->current->printCode();
		printf("dreturn\n");
	}

	frames->dreturn();
}

void areturn() {
	if(printEnable) {
		frames->current->printCode();
		printf("areturn\n");
	}

	frames->areturn();
}

void op_return() {
	if(printEnable) {
		frames->current->printCode();
		printf("return\n");
	}

	frames->op_return();
}

void getstatic() {

	u2 cp_index = get2byte();

	char *className = frames->current->get_field_class(cp_index);
	char *fieldName = frames->current->get_field_name(cp_index);
	char *fieldType = frames->current->get_field_type(cp_index);
	
	if( (strcmp(fieldName, "out") == 0) && (strcmp(fieldType, "Ljava/io/PrintStream;") == 0)) {
		frames->current->aconst_null();
		if(printEnable)
			printf("get out:java/io/PrintStream\n");
		return;
	}
	Class *classRef = memory->get_classref(className);
	
	if(classRef == NULL) {
		classRef = memory->new_class(className);
		clinit(classRef);
		if(classRef == NULL) {
			exception("NullPointerException at JavaVM.getstatic");
		}
		clinit(classRef);
	}
	int index;
	char *superName = classRef->get_cp_super_class();
	
	while( (index = classRef->get_field_index(fieldName)) == -1) {
		if(strcmp(superName, CLASS_OBJECT) == 0) {
			exception("NoSuchFieldError at JavaVM.getstatic");
		}
		classRef = memory->get_classref(superName);
		if(classRef == NULL) {
			classRef = memory->new_class(superName);
			clinit(classRef);
		}
		superName = classRef->get_cp_super_class();
	}
	u4 value[2];
	
	if(printEnable) {
		frames->current->printCode();
		printf("getstatic");
		printf("  #%d\n",cp_index);
	}
	memory->getstatic(classRef, index, fieldType, value);

	frames->current->pushOpStack(*fieldType, value[0]);
	if( (*fieldType == TYPE_LONG) || (*fieldType == TYPE_DOUBLE) ) {
		frames->current->pushOpStack(*fieldType, value[1]);
	}
}

void putstatic() {

	u2 cp_index = get2byte();

	char *className = frames->current->get_field_class(cp_index);
	char *fieldName = frames->current->get_field_name(cp_index);
	char *fieldType = frames->current->get_field_type(cp_index);

	Class *classRef = memory->get_classref(className);
	
	if(classRef == NULL) {
		classRef = memory->new_class(className);		
		if(classRef == NULL) {
			exception("NullPointerException at JavaVM.putstatic");
		}
		clinit(classRef);
	}
	int index;
	char *superName = classRef->get_cp_super_class();
	
	while( (index = classRef->get_field_index(fieldName)) == -1) {
		if(strcmp(superName, CLASS_OBJECT) == 0) {
			exception("NoSuchFieldError at JavaVM.putstatic");
		}
		classRef = memory->get_classref(superName);
		if(classRef == NULL) {
			classRef = memory->new_class(superName);
			clinit(classRef);
		}
		superName = classRef->get_cp_super_class();
	}
	u4 value[2];

	value[0] = frames->current->popOpStack();
	if( (*fieldType == TYPE_LONG) || (*fieldType == TYPE_DOUBLE) ) {
		value[1] = value[0];
		value[0] = frames->current->popOpStack();
	}
	if(printEnable) {
		frames->current->printCode();
		printf("putstatic");
		printf("  #%d\n",cp_index);
	}
	memory->putstatic(classRef, index, fieldType, value);
}

void getfield() {

	u2 cp_index = get2byte();

	char *className = frames->current->get_field_class(cp_index);
	char *fieldName = frames->current->get_field_name(cp_index);
	char *fieldType = frames->current->get_field_type(cp_index);

	u4 insRef = frames->current->popOpStack();
	u4 value[2];

	if(printEnable) {
		frames->current->printCode();
		printf("getfield");
		printf("  #%d\n",cp_index);
	}
	memory->getfield(insRef, className, fieldName, fieldType, value);

	frames->current->pushOpStack(*fieldType, value[0]);
	if( (*fieldType == TYPE_LONG) || (*fieldType == TYPE_DOUBLE) ) {
		frames->current->pushOpStack(*fieldType, value[1]);
	}

}

void putfield() {

	u2 cp_index = get2byte();

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

	if(printEnable) {
		frames->current->printCode();
		printf("putfield");
		printf("  #%d\n",cp_index);
	}
	memory->putfield(insRef, className, fieldName, fieldType, value);
}

void invokevirtual() {

	u2 cp_index = get2byte();

	char *className  = frames->current->get_method_class(cp_index);
	char *methodName = frames->current->get_method_name(cp_index);
	char *descriptor = frames->current->get_method_descriptor(cp_index);
	
	if( (strcmp(methodName, "println") == 0) && (strcmp(className, "java/io/PrintStream") == 0) ) {
		frames->invokeprintln(descriptor);
		
		return;
	}
	
	Class *classRef = memory->get_classref(className);
	if(classRef == NULL) {
		classRef = memory->new_class(className);
		clinit(classRef);
	}

	int index;
	while( (index = classRef->get_method_index(methodName, descriptor)) == -1 ) {
		char *superName = classRef->get_cp_super_class();
		if(strcmp(superName, CLASS_OBJECT) == 0) {
			exception("NoSuchMethodError at JavaVM.invokevirtual");
		}
		classRef = memory->get_classref(superName);
		if(classRef == NULL) {
			classRef = memory->new_class(superName);
			clinit(classRef);
		}
	}
	if(printEnable) {
		frames->current->printCode();
		printf("invokevirtual");
		printf("  #%d\n",cp_index);
	}
	frames->invokevirtual(classRef, index, methodName, descriptor);
}

void invokespecial() {

	u2 cp_index = get2byte();

	char *className  = frames->current->get_method_class(cp_index);
	char *methodName = frames->current->get_method_name(cp_index);
	char *descriptor = frames->current->get_method_descriptor(cp_index);

	Class *classRef = memory->get_classref(className);
	if(classRef == NULL) {
		classRef = memory->new_class(className);
		clinit(classRef);
	}

	int index;
	while( (index = classRef->get_method_index(methodName, descriptor)) == -1 ) {
		char *superName = classRef->get_cp_super_class();
		if(strcmp(superName, CLASS_OBJECT) == 0) {
			exception("NoSuchMethodError at JavaVM.invokespecial");
		}
		classRef = memory->get_classref(superName);
		if(classRef == NULL) {
			classRef = memory->new_class(superName);
			clinit(classRef);
		}
	}
	if(printEnable) {
		frames->current->printCode();
		printf("invokespecial");
		printf("  #%d\n",cp_index);
	}
	frames->invokespecial(classRef, index, methodName, descriptor);
}

void invokestatic() {

	u2 cp_index = get2byte();

	char *className  = frames->current->get_method_class(cp_index);
	char *methodName = frames->current->get_method_name(cp_index);
	char *descriptor = frames->current->get_method_descriptor(cp_index);

	Class *classRef = memory->get_classref(className);
	if(classRef == NULL) {
		classRef = memory->new_class(className);
		clinit(classRef);
	}

	int index;
	while( (index = classRef->get_method_index(methodName, descriptor)) == -1 ) {
		char *superName = classRef->get_cp_super_class();
		if(strcmp(superName, CLASS_OBJECT) == 0) {
			exception("NoSuchMethodError at JavaVM.invokestatic");
		}
		classRef = memory->get_classref(superName);
		if(classRef == NULL) {
			classRef = memory->new_class(superName);
			clinit(classRef);
		}
	}
	if(printEnable) {
		frames->current->printCode();
		printf("invokestatic");
		printf("  #%d\n",cp_index);
	}
	frames->invokestatic(classRef, index, methodName, descriptor);
}

void invokeinterface() {
	
	u2 cp_index = get2byte();
	u1 paramCount = get1byte();
	u1 zero = get1byte();
	

	char *interfaceName  = frames->current->get_imethod_class(cp_index);
	char *methodName = frames->current->get_imethod_name(cp_index);
	char *descriptor = frames->current->get_imethod_descriptor(cp_index);

	Class *intRef = memory->get_classref(interfaceName);
	if(intRef == NULL) {
		intRef = memory->new_class(interfaceName);
		clinit(intRef);
	}
	if(!isInterface(intRef->access_flags)) {
		exception("IncompatibleClassChangeError at JavaVM.invokeinterface");
	}
	int index;
	
	for(int i=0; (i < intRef->interfaces_count) &&
				 ( ( index = intRef->get_method_index(methodName, descriptor) ) == -1 ); i++ ) {
		char *superIntName = intRef->get_interface_name(i);
		intRef = memory->get_classref(superIntName);
		if(intRef == NULL) {
			intRef = memory->new_class(superIntName);
			clinit(intRef);
		}
	}
	if(index == -1) {
		exception("NoSuchMethodError at JavaVM.invokeinterface");
	}
	
	if(printEnable) {
		frames->current->printCode();
		printf("invokeinterface");
		printf("  #%d %d\n",cp_index,paramCount);
	}
	frames->invokeinterface(interfaceName, paramCount, methodName, descriptor);
}

void invokedynamic() {
	if(printEnable)
    	printf("invokedynamic[Unused]\n");
}


void op_new() {

	u2 cp_index = get2byte();

	char *classname = frames->current->get_class_name(cp_index);

	Class *classRef = memory->get_classref(classname);
	if(classRef == NULL) {
		classRef = memory->new_class(classname);
		clinit(classRef);
	}
	char *supername = classRef->get_cp_super_class();
	
	while(strcmp(supername, CLASS_OBJECT) != 0) {
		Class *superRef = memory->get_classref(supername);
		if(superRef == NULL) {
			superRef = memory->new_class(supername);
			clinit(superRef);
		}
		supername = superRef->get_cp_super_class();
	}
	
	if(printEnable) {
		frames->current->printCode();
		printf("new");
		printf("  #%d\n",cp_index);
	}
	u4 instRef = (u4)memory->op_new(classRef, NULL);
	frames->current->pushOpStack(TYPE_REF, instRef);
}

void newarray() {

	u1 atype = get1byte();

	u4 count = frames->current->popOpStack();
	u4 arrayRef;

	if(printEnable) {
		frames->current->printCode();
		printf("newarray");
		printf("  %d\n",atype);
	}
	arrayRef = memory->newarray(count, atype);
	frames->current->pushOpStack(TYPE_REF, arrayRef);
}

void anewarray() {

	u2 cp_index = get2byte();

	char *classname = frames->current->get_class_name(cp_index);

	u4 count = frames->current->popOpStack();
	u4 arrayRef;
	
	if(printEnable) {
		frames->current->printCode();
		printf("anewarray");
		printf("  #%d\n",cp_index);
	}
	arrayRef = memory->anewarray(count, classname);
	frames->current->pushOpStack(TYPE_REF, arrayRef);
}

void arraylength() {
	if(printEnable) {
		frames->current->printCode();
    	printf("arraylength\n");
	}
    u4 ref = frames->current->popOpStack();
    u4 ret = memory->arraylength(ref);
    frames->current->pushOpStack(TYPE_INT,ret);
}
void athrow() {
	if(printEnable) {
		frames->current->printCode();
		printf("athrow\n");
	}
	
	frames->athrow();
}


int checkcast_check(u2 index);

int checkInterfaces(Class *classS, char *classnameT) {	
	if(classS->isInterface(classnameT)) {
		return 1;
	} else {
		for(int i; i<classS->interfaces_count; i++) {
			char *supernameS = classS->get_interface_name(i);
			Class *superS = memory->get_classref(supernameS);
			
			if(superS == NULL) {
				superS = memory->new_class(supernameS);
				clinit(superS);
			}
			if(checkInterfaces(superS, classnameT)) {
				return 1;
			}
		}
		return 0;
	}
}

int checkType(MemoryData *objectref, char *classnameT) {

	if(objectref->type == TYPE_CLASS) {
		/* S eh classe ou interface */
		Class *classS = objectref->classref;
		char *classnameS = classS->get_cp_this_class();
		
		if( !isInterface(classS->access_flags) ) {
			/* S eh classe */
			if(classnameT[0] != TYPE_ARRAY) {
				/* T eh classe ou interface */
				Class *classT = memory->get_classref(classnameT);
				if(classT == NULL) {
					classT = memory->new_class(classnameT);
					clinit(classT);
				}
				if(!isInterface(classT->access_flags)) {
					/* T eh classe */
					/* Verifica se S igual a T  */
					while( strcmp(classnameS, classnameT) != 0 ) {
						/* Senao compara os superclasses de S com T */
						classnameS = classS->get_cp_super_class();
						/* Classe Object retorna super_class NULL  */
						if(classnameS == NULL) {
							return 0;
						}
						classS = memory->get_classref(classnameS);
						if(classS == NULL) {
							classS = memory->new_class(classnameS);
							clinit(classS);
						}
					}
					return 1;
				} else {
					/* T eh interface */
					/* Verifica se S implementa T */
					while( !classS->isInterface(classnameT) ) {
						/* Senao verifica se tem um superclasse de S que implemnta T */
						classnameS = classS->get_cp_super_class();
						/* Classe Object nao tem interface  */
						if( strcmp(classnameS, CLASS_OBJECT) == 0) {
							return 0;
						}
						classS = memory->get_classref(classnameS);
						if(classS == NULL) {
							classS = memory->new_class(classnameS);
							clinit(classS);
						}
					}
					return 1;
				}
			} else {
				exception("ClassCastException at JavaVM.checkcast");
			}
		} else {
			/* S eh interface */
			if(*classnameT != TYPE_ARRAY) {
				/* T eh classe ou interface */
				Class *classT = memory->get_classref(classnameT);
				
				if(!isInterface(classT->access_flags)) {
					/* T eh classe */
					/* T deve ser classe Object */
					if( strcmp(classnameT, CLASS_OBJECT) != 0) {
						return 0;
					}
					return 1;
				} else {
					/* T eh interface */
					/* Verifica se S igual a T  */
					if( strcmp(classnameS, classnameT) != 0 ) {
						/* Senao verifica se T eh superinterface de S  */
						if(!checkInterfaces(classS, classnameT)) {									
							return 0;
						}
					}
					return 1;
				}
			}
		}
	} else {
		/* S eh array */
		if(*classnameT != TYPE_ARRAY) {
			/* T eh classe ou interface */
			if( strcmp(classnameT, CLASS_OBJECT) == 0 ) {
				/* T eh classe Object */
				return 1;
			} else {
				Class *classT = memory->get_classref(classnameT);
				if(classT == NULL) {
					classT = memory->new_class(classnameT);
					clinit(classT);
				}
				/* Verifica se T eh interface */
				if(!isInterface(classT->access_flags)) {
					/* T eh classe mas nao eh Object */
					return 0;
				} else {
					/* T eh interface */
					/* Nesse JVM array nao implementa interface */
					return 0;
				}
			}
		} else {
			/* T eh array */
			if(strcmp(objectref->array_type, classnameT) == 0) {
				/* S e T sao arrays de mesmo tipo e dimencao */
				return 1;
			} else {
				/* S e T sao arrays de tipo ou dimencao diferente */
				char *typeS = objectref->array_type;
				char *typeT = classnameT;
				
				while(*typeS == TYPE_ARRAY)
					typeS++;
					
				while(*typeT == TYPE_ARRAY)
					typeT++;
				if(typeT[strlen(typeT)] == ';')
					typeT[strlen(typeT)] = '\0';
					
				if(strcmp(typeS, typeT) == 0) {
					/* S e T sao arrays de mesmo tipo */
					return 1;
				}
				if( (*typeS !=  TYPE_CLASS) && ( isPrimitive(typeT) ) ) {
					/* S ou T ou os dois sao de tipo primitivos e nao sao iguasis */
					return 0;
				}
				/* S e T sao classes diferentes */
				Class *classRef = memory->get_classref(typeS);
				if(classRef == NULL) {
					classRef = memory->new_class(typeS);
					clinit(classRef);
				}
				char *superName = classRef->get_cp_super_class();
				
				while( strcmp(superName, typeT) != 0) {
					if(strcmp(superName, CLASS_OBJECT) == 0) {
						/* T nao eh superclasse de S */
						return 0;
					}
					classRef = memory->get_classref(superName);
					if(classRef == NULL) {
						classRef = memory->new_class(superName);
						clinit(classRef);
					}
					superName = classRef->get_cp_super_class();
				}
				/* T eh superclasse de S */
				return 1;
			}
		}
	}
}

void checkcast() {
    u2 cp_index = get2byte();
	
	MemoryData *objectref = (MemoryData *)frames->current->getOpStackTop(); 
	char *classnameT = frames->current->get_class_name(cp_index);
	
	u4 result = checkType(objectref, classnameT);
	
	if(printEnable) {
		frames->current->printCode();
    	printf("checkcast");
    	printf("  #%d\n",cp_index);
	}
	if( !result )
		exception("ClassCastException at JavaVM.checkcast");
}

void instanceof() {
    u2 cp_index = get2byte();
	
	MemoryData *objectref = (MemoryData *)frames->current->popOpStack(); 
	char *classnameT = frames->current->get_class_name(cp_index);
	
	u4 result = checkType(objectref, classnameT);
	
	if(printEnable) {
		frames->current->printCode();
    	printf("instanceof");
    	printf("  #%d\n",cp_index);
	}
	frames->current->pushOpStack(TYPE_INT, result);
}

void monitorenter() {
	if(printEnable)
    	printf("monitorenter[Unused]\n");
}
void monitorexit() {
	if(printEnable)
    	printf("monitorexit[Unused]\n");
}
void wide() {
	if(printEnable) {
		frames->current->printCode();
    	printf("wide\n");
	}
    frames->current->wideFlag = true;
}

void multianewarray() {

	u2 cp_index = get2byte();
	int dim = get1byte();
	
	if(printEnable) {
		frames->current->printCode();
		printf("multianewarray");
		printf("  #%d %d\n",cp_index,dim);
	}
	char *arrayType = frames->current->get_class_name(cp_index);
	int32_t *count = new int32_t[dim];
	
	for(int i=dim-1; i>=0; i--) {
		count[i] = (int)frames->current->popOpStack();
	}
	u4 arrayRef;

	arrayRef = memory->multianewarray(count, arrayType);
	frames->current->pushOpStack(TYPE_REF, arrayRef);
}

void ifnull() {
	if(printEnable) {
		frames->current->printCode();
		printf("ifnull\n");
	}

	int16_t pc = frames->current->getPC()-1;

	u2 branch = get2byte();
	pc += (int16_t)branch;

	frames->current->ifnull(pc);
}

void ifnonnull() {
	if(printEnable) {
		frames->current->printCode();
		printf("ifnonnull\n");
	}

	int16_t pc = frames->current->getPC()-1;

	u2 branch = get2byte();
	pc += (int16_t)branch;

	frames->current->ifnonnull(pc);
}

void goto_w() {
	if(printEnable) {
		frames->current->printCode();
		printf("goto_w\n");
	}

	int16_t pc = frames->current->getPC()-1;

	u2 branch = get2byte();
	pc += (int16_t)branch;

	frames->current->goto_w(pc);
}

void jsr_w() {
	if(printEnable) {
		frames->current->printCode();
    	printf("jsr\n");
	}

	int16_t pc = frames->current->getPC()-1;

	u4 branch = get4byte();
	frames->current->pushOpStack( TYPE_INT ,pc);
	pc += branch;
	frames->current->op_goto(pc);
}

void breakpoint() {
	if(printEnable)
		printf("breakpoint\n");
}

void impdep() {
	if(printEnable)
		printf("impdep\n");
}

void impdep2() {
	if(printEnable)
		printf("impdep2\n");
}

int isPrimitive(char *type) {
	if(strlen(type) > 1)
		return 0;
	if(*type == TYPE_INT)
		return 1;
	if(*type == TYPE_LONG)
		return 1;
	if(*type == TYPE_FLOAT)
		return 1;
	if(*type == TYPE_DOUBLE)
		return 1;
	
	return 0;
}

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

char *getPath(char *argv) {
	char *temp = argv;
	char *aux;
	char *fileName;
	
	if( (temp = strchr(argv, '\\')) != NULL ) {	
		aux = temp;
		*temp = '/';
		while( (temp = strchr(argv, '\\')) != NULL ) {
			aux = temp;
			*temp = '/';
		}
		fileName = new char[strlen(aux)];
		aux++;
		strcpy(fileName, aux);
		*aux = '\0';
	} else {
		
		fileName = new char[strlen(argv)];
		strcpy(fileName, argv);
		*argv = '\0';
	}
	
	return fileName;
}

void print() {
	frames->print();
		printf("\n");
	memory->print();
		printf("\n");
}

void printHelp() {
	printf("prog [opcao] arq_class\n");
	printf("opcao:\n");
	printf("  N/A: executar arquivo\n");
	printf("  -c: mostrar classfile\n");
	printf("  -d: modo debug\n");
}
