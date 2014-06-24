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
	//void invokespecial(u2 cp_index);
	void invokespecial(Class *ref, char *methodname, char *descriptor);
	void op_return();
	
	StackFrame(int);
	void pushFrame(Class *ref, char *methodname, char *descriptor);
	void popFrame();
	void pushMain(Class *ref);
	
	int isEmpty();
	
	void print();
	void print_all();
};

#endif
