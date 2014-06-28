#ifndef STACK_FRAME
#define STACK_FRAME

#include <stdio.h>
#include <stdlib.h>

#include "frame.hpp"
#include "class.hpp"
#include "mem_data.hpp"
#include "operand.hpp"

class StackFrame {
public:
	int max;
	int size;
	Frame *current;
	Frame *stack;

	void invokevirtual(Class *ref, char *methodname, char *descriptor);
	void invokespecial(Class *ref, char *methodname, char *descriptor);
	void invokestatic(Class *ref, char *methodname, char *descriptor);

	void ireturn();
	void lreturn();
	void freturn();
	void dreturn();
	void areturn();
	void op_return();
	
	void athrow();

	StackFrame(int);
	void pushFrame(Class *ref, char *methodname, char *descriptor,bool isStaticFlag=false);
	void popFrame();
	void pushMain(Class *ref);
	int pushClinit(Class *ref);

	int isEmpty();

	void print();
	void print_all();
};

#endif
