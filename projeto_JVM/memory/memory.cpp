#include "memory.hpp"

Memory::Memory(int c_array_size, int m_array_size) {
	classes = new ClassArray(c_array_size);
	data = new MemoryDataArray(m_array_size);
}

u4 Memory::op_new(Class *classref) {
	u4 instance;
	
	instance = data->new_instance(classref);
	return instance;
}

u4 Memory::newarray(int size, u1 type) {
	enum {A_BOOL = 4, A_CHAR, A_FLOAT, A_DOUBLE, A_BYTE, A_SHORT, A_INT, A_LONG};
	u4 array;
	u1 a_type[2] = {'[', 0};

	if( (type == A_BOOL) || (type == A_CHAR) ||
		(type == A_BYTE) || (type == A_SHORT) ||
		(type == A_INT) ) {
		
		a_type[1] = TYPE_INT;
	} else if(type == A_LONG) {
		a_type[1] = TYPE_LONG;
	} else if(type == A_FLOAT) {
		a_type[1] = TYPE_FLOAT;
	} else if(type == A_DOUBLE) {
		a_type[1] = TYPE_DOUBLE;
	}
	array = data->new_array(&size, a_type, NULL);
	return array;
}

u4 Memory::anewarray(int size, u1 *type, Class *ref) {
	u4 array;
	
	array = data->new_array(&size, type, ref);
	return array;
}

u4 Memory::multianewarray(int *size, u1 *type, Class *ref) {
	u4 array;
	
	array = data->new_array(size, type, ref);
	return array;
}

u4 Memory::arraylength(u4 ref) {
	return data->arraylength(ref);
}

Class *Memory::get_classref(u1 *name) {
	return classes->get_classref(name);
}

Class *Memory::new_class(u1 *name) {
	return classes->new_class(name);
}

void Memory::print() {
	classes->print();
	data->print_min();
}
