#include "stack_frame.hpp"

int countParam(char *descriptor);
char *getReturnType(char *descriptor);

StackFrame::StackFrame(int m) {
	max = m;
	size = 0;
	stack = (Frame *) calloc(max+1, sizeof(Frame));
	current = &stack[0];
}

void StackFrame::invokeprintln(char *descriptor) {
	descriptor++;
	while(*descriptor != ')') {
		if (*descriptor == TYPE_INT) {
			printf("%d", current->popInt());
		} else if(*descriptor == TYPE_CHAR) {
			printf("%c", current->popChar());
		} else if(*descriptor == TYPE_BYTE) {
			printf("%d", current->popByte() );
		} else if(*descriptor == TYPE_BOOL) {
			u1 b = (u1)current->popInt();
			if(b)
				printf("true");
			else
				printf("false");
		} else if(*descriptor == TYPE_SHORT) {
			printf("%hd", current->popShort());
		} else if(*descriptor == TYPE_FLOAT) {
			printf("%.4f", current->popFloat());
		} else if(*descriptor == TYPE_LONG) {
			printf("%lld", current->popLong());
		} else if(*descriptor == TYPE_DOUBLE) {
			printf("%.4f", current->popDouble());
		}  else if(strstr(descriptor, "Ljava/lang/String;") == descriptor ) {
			char *string = (char *)current->popOpStack();
			printf("%s", string);
			while(*descriptor != ';')
				descriptor++;
		} else if( *descriptor == TYPE_CLASS ) {
			printf("%08X", current->popOpStack());
			while(*descriptor != ';')
				descriptor++;
		}
		descriptor++;
	}
	printf("\n");
	(void)current->popOpStack();
	
	return;	
}

void StackFrame::invokevirtual(Class *classRef, int index, char *methodname, char *descriptor) {
	if(classRef == NULL) {
		exception("NullPointerException at StackFrame.invokevirtual");
	}
	int param_count;	
	Operand *param;
	
	param_count = countParam(descriptor);
	param_count++;
	param = current->popParam(param_count);
	
	if(param[0].bytes == 0x0) {
		exception("NullPointerException at StackFrame.invokevirtual");
	}
	u2 flags = classRef->get_method_flags(index);
	
	if(isStatic(flags)) {
		exception("IncompatibleClassChangeError at StackFrame.invokespecial");
	}
	pushFrame(classRef, index, methodname, descriptor);

	current->setParam(param, param_count, 0);
}

void StackFrame::invokespecial(Class *classRef, int index, char *methodname, char *descriptor) {
	if(classRef == NULL) {
		exception("NullPointerException at StackFrame.invokespecial");
	}
	int param_count;
	Operand *param;
	
	param_count = countParam(descriptor);
	param_count++;
	param = current->popParam(param_count);
	
	if(param[0].bytes == 0x0) {
		exception("NullPointerException at StackFrame.invokespecial");
	}
	u2 flags = classRef->get_method_flags(index);
	
	if(isStatic(flags)) {
		exception("IncompatibleClassChangeError at StackFrame.invokespecial");
	}
	if(isAbstract(flags)) {
		exception(" AbstractMethodError at StackFrame.invokespecial");
	}
	pushFrame(classRef, index, methodname, descriptor);

	current->setParam(param, param_count, 0);
}

void StackFrame::invokestatic(Class *classRef, int index, char *methodname, char *descriptor) {
	if(classRef == NULL) {
		exception("NullPointerException at StackFrame.invokestatic");
	}
	int param_count;
	Operand *param;
	
	param_count = countParam(descriptor);
	param = current->popParam(param_count);
	
	
	u2 flags = classRef->get_method_flags(index);
	
	if(!isStatic(flags)) {
		exception("IncompatibleClassChangeError at StackFrame.invokestatic");
	}
	
	pushFrame(classRef, index, methodname, descriptor);

	current->setParam(param, param_count, 0);
}

void StackFrame::invokeinterface(char *interfacename, int param_count, char *methodname, char *descriptor) {
	Operand *param;
	
	param = current->popParam(param_count);
	if(param[0].bytes == 0x0) {
		exception("NullPointerException at StackFrame.invokeinterface");
	}
	MemoryData *instRef = (MemoryData *)param->bytes;
	Class *classRef = instRef->classref;
	
	int index;
	
	while( (index = classRef->get_method_index(methodname, descriptor)) == -1) {
		instRef = instRef->superInst;
		if(instRef == NULL) {
			exception("at StackFrame.invokeinterface");
		}
		classRef = instRef->classref;
	}
	if(!classRef->isInterface(interfacename)) {
		exception("IncompatibleClassChangeError at StackFrame.invokeinterface");
	}
	u2 flags = classRef->get_method_flags(index);
	
	if(!isPublic(flags)) {
		exception("IllegalAccessError at StackFrame.invokeinterface");
	}
	if(isAbstract(flags)) {
		exception("AbstractMethodError at StackFrame.invokeinterface");
	}
	
	pushFrame(classRef, index, methodname, descriptor);
	
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

void StackFrame::pushFrame(Class *classRef, int index, char *methodname, char *descriptor) {
	if(size == max) {
		printf("Error stack over :stack_frame.pushFrame\n");
		exit(0);
	}
	Code *code = classRef->get_method_code(index);

	Frame temp(classRef, code, methodname, descriptor);

	current++;
	*current = temp;
	size++;
}

void StackFrame::popFrame() {
	current--;
	size--;
}

void StackFrame::pushMain(Class *classRef) {
	if(size == max) {
		printf("Error stack over :stack_frame.pushFrame\n");
		exit(0);
	}
	if(classRef == NULL) {
		printf("Error class classRef is NULL :stack_frame.pushFrame\n");
		exit(0);
	}
	int index = classRef->get_method_main();
	
	if(index < 0) {
		printf("Error method main not found: stack_frame:pushFrame\n");
		exit(0);
	}
	char *methodname = classRef->get_method_name(index);
	char *descriptor = classRef->get_method_descriptor(index);

	pushFrame(classRef, index, methodname, descriptor);
}

int StackFrame::pushClinit(Class *classRef) {
	if(size == max) {
		printf("Error stack over :stack_frame.pushFrame\n");
		exit(0);
	}
	if(classRef == NULL) {
		printf("Error class classRef is NULL :stack_frame.pushFrame\n");
		exit(0);
	}
	int index = classRef->get_method_clinit();
	int clinitFlag = 1;
	
	if(index < 0) {
		clinitFlag = 0;
	}
	char *classname = classRef->get_cp_this_class();
	if(strcmp(classname, CLASS_OBJECT) == 0) {
		clinitFlag = 0;
	}
	if(!clinitFlag) {
		return 0;
	}
	
	char *descriptor = classRef->get_method_descriptor(index);
	char *methodname = classRef->get_method_name(index);
	Code *code = classRef->get_method_code(index);

	Frame temp(classRef, code, methodname, descriptor);

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
		if(*descriptor == TYPE_ARRAY) {
			count++;
			descriptor++;
			if(*descriptor == TYPE_CLASS) {
				while(*descriptor != ';') {
					descriptor++;
				}
			}
		} else if(*descriptor == TYPE_CLASS) {
			count++;
			while(*descriptor != ';') {
				descriptor++;
			}
		} else if( (*descriptor == TYPE_LONG) ||
				   (*descriptor == TYPE_DOUBLE) ) {
			count += 2;
		} else if (*descriptor != TYPE_ARRAY) {
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
