#include "stack_frame.hpp"
#include "access_flag.hpp"

int countParam(char *descriptor);
char *getReturnType(char *descriptor);

StackFrame::StackFrame(int m) {
	max = m;
	size = 0;
	stack = (Frame *) calloc(max+1, sizeof(Frame));
	current = &stack[0];
}

void StackFrame::invokevirtual(Class *ref, char *methodname, char *descriptor) {
	int param_count;
	Operand *param;

	param_count = countParam(descriptor);
	param_count++;
	param = current->popParam(param_count);

	pushFrame(ref, methodname, descriptor);

	current->setParam(param, param_count, 0);
}

void StackFrame::invokestatic(Class *ref, char *methodname, char *descriptor) {
	int param_count;
	Operand *param;

	param_count = countParam(descriptor);
	param_count++;

    param = current->popParam(param_count);

	pushFrame(ref, methodname, descriptor,true);

	current->setParam(param, param_count, 0);
}

void StackFrame::invokespecial(Class *classRef, char *methodname, char *descriptor) {
	int param_count;
	Operand *param;

	param_count = countParam(descriptor);
	param_count++;
	param = current->popParam(param_count);

	pushFrame(classRef, methodname, descriptor);

	current->setParam(param, param_count, 0);
}

void StackFrame::ireturn() {
	u4 value = current->popOpStack();

	popFrame();
	current->pushOpStack(TYPE_INT, value);
}

void StackFrame::lreturn() {
	u4 valueL = current->popOpStack();
	u4 valueH = current->popOpStack();

	popFrame();
	current->pushOpStack(TYPE_LONG, valueH);
	current->pushOpStack(TYPE_LONG, valueL);
}

void StackFrame::freturn() {
	u4 value = current->popOpStack();

	popFrame();
	current->pushOpStack(TYPE_FLOAT, value);
}

void StackFrame::dreturn() {
	u4 valueL = current->popOpStack();
	u4 valueH = current->popOpStack();

	popFrame();
	current->pushOpStack(TYPE_DOUBLE, valueH);
	current->pushOpStack(TYPE_DOUBLE, valueL);
}

void StackFrame::areturn() {
	u4 value = current->popOpStack();

	popFrame();
	current->pushOpStack(TYPE_REF, value);
}

void StackFrame::op_return() {
	popFrame();
}

void StackFrame::athrow() {
	u4 expRef = current->popOpStack();
	MemoryData *instRef = (MemoryData *)expRef;
	Class *exception = instRef->classref;
	char *excepName = exception->get_cp_this_class();
	
	popFrame();
	
	current->clear();
	int pc = current->getPC();
	current->pushOpStack(TYPE_REF, expRef);
	int length = current->code->exception_table_length;
	int start;
	int end;
	u2 expNameIndex;
	u2 handlerPC;
	for(int i=0; i<length; i++) {
		start = current->code->exception_table[i].start_pc;
		end = current->code->exception_table[i].end_pc;
		expNameIndex = current->code->exception_table[i].catch_type;
		handlerPC = current->code->exception_table[i].handler_pc;
		if( ((pc>=start) && (pc<=end) )&& 
			strcmp( exception->get_cp_this_class(), current->get_class_name(expNameIndex) ) == 0 ) {
			current->op_goto(handlerPC);
			break;
		}
	}
}

void StackFrame::pushFrame(Class *ref, char *methodname, char *descriptor,bool isStaticFlag) {
	if(size == max) {
		printf("Error stack over :stack_frame.pushFrame\n");
		exit(0);
	}
	int index;


	if(ref == NULL) {
		printf("Error class ref is NULL :stack_frame.pushFrame\n");
		exit(0);
	}



	index = ref->get_method_index(methodname, descriptor);

	if(index < 0) {
		printf("Error method %s:%s not found: stack_frame:pushFrame\n", methodname,descriptor);
		exit(0);
	}


	Code *code = ref->get_method_code(index);
	char *rType = getReturnType(descriptor);

	if (isStaticFlag && isStatic(ref->methods[index].access_flags) ){
        printf("Error method %s:%s is not static: stack_frame:pushFrame\n", methodname,descriptor);
		exit(0);
    }

	Frame temp(ref, code, NULL, 0, rType);
	temp.methodname = methodname;

	current++;
	*current = temp;
	size++;
}

void StackFrame::popFrame() {
	current--;
	size--;
}

void StackFrame::pushMain(Class *ref) {
	if(size == max) {
		printf("Error stack over :stack_frame.pushFrame\n");
		exit(0);
	}
	int index;

	if(ref == NULL) {
		printf("Error class ref is NULL :stack_frame.pushFrame\n");
		exit(0);
	}
	index = ref->get_method_main();
	if(index < 0) {
		printf("Error method main not found: stack_frame:pushFrame\n");
		exit(0);
	}
	char *descriptor = ref->get_method_descriptor(index);
	char *name = ref->get_method_name(index);
	char *rType = getReturnType(descriptor);

	Code *code = ref->get_method_code(index);
	Frame temp(ref, code, NULL, 0, rType);
	temp.methodname = name;

	current++;
	*current = temp;
	size++;
}

int StackFrame::pushClinit(Class *ref) {
	if(size == max) {
		printf("Error stack over :stack_frame.pushFrame\n");
		exit(0);
	}
	int index;

	if(ref == NULL) {
		printf("Error class ref is NULL :stack_frame.pushFrame\n");
		exit(0);
	}
	printf("Nova classe carregada. Inicializando classe.\n");
	index = ref->get_method_clinit();
	if(index < 0) {
		printf("<clinit> nao encontrado!\n");
		return 0;
	}
	if(strcmp(ref->get_cp_this_class(), "java/lang/Object") == 0) {
		return 0;
	}
	printf("<clinit> encontrado! Instrucao eh interrompida\n");
	char *descriptor = ref->get_method_descriptor(index);
	char *name = ref->get_method_name(index);
	char *rType = getReturnType(descriptor);

	Code *code = ref->get_method_code(index);
	Frame temp(ref, code, NULL, 0, rType);
	temp.methodname = name;

	current++;
	*current = temp;
	size++;
	return 1;
}

int StackFrame::isEmpty() {
	return size;
}

void StackFrame::print() {
	printf(">>>StackFrame\n");
	printf("  size: %d\n",size);
	if(size > 0)
		current->print();
}

void StackFrame::print_all() {
	printf("StackFrame\n");
	for(int i=1;i<=size;i++) {
		stack[i].print();
	}
}

int countParam(char *descriptor) {
	int count = 0;

	descriptor++;
	while(*descriptor != ')') {
		if(*descriptor == TYPE_CLASS) {
			count++;
			while(*descriptor != ';') {
				descriptor++;
			}
		} else if( (*descriptor == TYPE_LONG) ||
				   (*descriptor == TYPE_DOUBLE) ) {
			count += 2;
		} else {
			count++;
		}
		descriptor++;
	}
	return count;
}

char *getReturnType(char *descriptor) {
	while(*descriptor != ')')
		descriptor++;

	return descriptor+1;
}
