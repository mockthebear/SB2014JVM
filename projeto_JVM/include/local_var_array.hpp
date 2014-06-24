#ifndef LOCAL_VARIABLE_ARRAY
#define LOCAL_VARIABLE_ARRAY

#include <stdio.h>
#include <stdlib.h>

#include "definition.hpp"
#include "Operand.hpp"


class LocalVariableArray {
public:
	Operand *array;
	u2 size;
	
	LocalVariableArray(u2);

	void iinc(u1, u1);
	
	Operand load(u2 index);
	void store(u2 index, Operand value);
	
	void set_param(Operand *, int, int);
	void print();
	void print_min();
};

#endif