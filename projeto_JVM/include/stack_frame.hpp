#ifndef STACK_FRAME
#define STACK_FRAME

#include <stdio.h>
#include <stdlib.h>

#include "definition.hpp"
#include "exception.hpp"
#include "frame.hpp"
#include "class.hpp"
#include "mem_data.hpp"
#include "operand.hpp"
#include "access_flag.hpp"

class StackFrame {
public:
	int max;
	int size;
	Frame *current;
	Frame *stack;

	void invokevirtual(Class *ref, int index, char *methodname, char *descriptor);
	void invokespecial(Class *ref, int index, char *methodname, char *descriptor);
	void invokestatic(Class *ref, int index, char *methodname, char *descriptor);
	void invokeinterface(char *interfacename, int param_count, char *methodname, char *descriptor);
	
	void ireturn();
	void lreturn();
	void freturn();
	void dreturn();
	void areturn();
	void op_return();
	
	void athrow();

	StackFrame(int);
	void pushFrame(Class *ref, int index, char *methodname, char *descriptor);
	void popFrame();
	void pushMain(Class *ref);
	int pushClinit(Class *ref);

	int isEmpty();

	void print();
	void print_all();
};

#endif
