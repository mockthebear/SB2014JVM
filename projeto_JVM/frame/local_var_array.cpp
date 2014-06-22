#include "local_var_array.hpp"



LocalVariableArray::LocalVariableArray(u2 s) {
	size = s;
	array = new Operand[size];
}

void LocalVariableArray::initialize(Operand *vars, u2 count) {
	for(int i=1; i<count; i++)
		array[i] = vars[i];
}

void LocalVariableArray::print() {
	printf("size %d\n", size);
	for(int i=0; i<size; i++) {
		printf("[%d] ",i);
		array[i].print();
	}
}



