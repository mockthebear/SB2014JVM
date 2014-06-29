#include "local_var_array.hpp"


LocalVariableArray::LocalVariableArray(u2 s) {
	size = s;
	array = new Operand[size];
}

void LocalVariableArray::iinc(u2 index, u1 value) {
	u4 bytes = value;

	if(value & 0x80)
		bytes |= 0xFFFFFF00;
	array[index].bytes += bytes;
}

Operand LocalVariableArray::load(u2 index) {
	if(index >= size) {
		printf("Error index %d: local_var_array.load\n", index);
		exit(0);
	}
	return array[index];
}

void LocalVariableArray::store(u2 index, Operand value) {
	if(index >= size) {
		printf("Error index %d: local_var_array.store\n", index);
		exit(0);
	}
	array[index] = value;
}

void LocalVariableArray::set_param(Operand *param, int count, int ini) {
	for(int i=ini; i<count; i++)
		array[i] = param[i];
}

void LocalVariableArray::print() {
	printf(">Local Variables\n");
	printf("  size: %d\n", size);
	printf("  ");
	for(int i=0; i<size; i++) {
		printf("[%d] ",i);
		array[i].print();
	}
	printf("\n");
}

