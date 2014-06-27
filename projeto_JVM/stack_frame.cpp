#include "stack_frame.hpp"

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

void StackFrame::invokespecial(Class *classRef, char *methodname, char *descriptor) {	
	int param_count;
	Operand *param;
	
	param_count = countParam(descriptor);
	param_count++;
	param = current->popParam(param_count);
	
	pushFrame(classRef, methodname, descriptor);
	
	current->setParam(param, param_count, 0);
}
void StackFrame::op_return() {
	popFrame();
}

void StackFrame::pushFrame(Class *ref, char *methodname, char *descriptor) {
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

void StackFrame::pushClinit(Class *ref) {
	if(size == max) {
		printf("Error stack over :stack_frame.pushFrame\n");
		exit(0);
	}
	int index;
	
	if(ref == NULL) {
		printf("Error class ref is NULL :stack_frame.pushFrame\n");
		exit(0);
	}
	index = ref->get_method_clinit();
	if(index < 0) {
		printf("<clinit> nao encontrado!\n");
		return;
	}
	if(strcmp(ref->get_cp_this_class(), "java/lang/Object") == 0) {
		return;
	}
	printf("<clinit> encontrado!\n");
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
