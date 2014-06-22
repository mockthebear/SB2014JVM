#ifndef LOCAL_VARIABLE_ARRAY
#define LOCAL_VARIABLE_ARRAY

#include <stdio.h>

#include "definition.hpp"
#include "Operand.hpp"


class LocalVariableArray {
public:
	Operand *array;
	u2 size;
	LocalVariableArray(u2);

	void initialize(Operand *, u2);
	void print();
};

#endif
