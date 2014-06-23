#include "memory.hpp"

void test_load(char func, u1 type);
void test_store(char func, u1 type);


Memory::Memory(int c_array_size, int m_array_size) {
	classes = new ClassArray(c_array_size);
	data = new MemoryDataArray(m_array_size);
}

u4 Memory::op_new(Class *ref) {
	u4 instance;
	
	instance = data->new_instance(classref);
	return instance;
}

void Memory::putstatic(Class *ref, u1 *fieldname, u4 *value, u1 *type) {
	classes->putstatic(ref, fieldname, value, type);
}

u1 *Memory::getstatic(Class *ref, u1 *fieldname, u4 *value) {
	return classes->getstatic(ref, fieldname, value);
}

void Memory::putfield(u4 ref, u1 *fieldname, u4 *value, u1 *type) {
	data->putfield(ref, fieldname, value, type);
}

u1 *Memory::getfield(u4 ref, u1 *fieldname, u4 *value) {
	return data->getfield(ref, fieldname, value);
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

void Memory::iaload(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_load('i', array->type);
	array->get_data(index, data, TYPE_INT);
}

void Memory::laload(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_load('c', array->type);
	array->get_data(index, data, TYPE_LONG);
}

void Memory::faload(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_load('f', array->type);
	array->get_data(index, data, TYPE_FLOAT);
}

void Memory::daload(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_load('d', array->type);
	array->get_data(index, data, TYPE_DOUBLE);
}

void Memory::aaload(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_load('a', array->type);
	if(array->array_type == TYPE_CLASS)
		array->get_data(index, data, TYPE_CLASS);
	if(array->array_type == TYPE_ARRAY)
		array->get_data(index, data, TYPE_ARRAY);
}

void Memory::baload(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	
	test_load('d', array->type);
	if(array->array_type == TYPE_BOOL)
		array->get_data(index, data, TYPE_BOOL);
	else if(array->array_type == TYPE_BYTE)
		array->get_data(index, data, TYPE_BYTE);
	data[0] &= 0xFF;
}

void Memory::caload(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_load('c', array->type);
	array->get_data(index, data, TYPE_CHAR);
	data[0] &= 0xFF;
}

void Memory::saload(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_load('s', array->type);
	array->get_data(index, data, TYPE_CHAR);
	data[0] &= 0xFFFF;
}

void iastore(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_store('i', array->type);
	array->put_data(index, data, TYPE_INT);	
}

void lastore(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_store('l', array->type);
	array->put_data(index, data, TYPE_LONG);	
}
	
void fastore(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_store('f', array->type);
	array->put_data(index, data, TYPE_FLOAT);	
}

void dastore(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_store('d', array->type);
	array->put_data(index, data, TYPE_DOUBLE);	
}

void aastore(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_store('a', array->type);
	if(array->array_type == TYPE_CLASS)
		array->put_data(index, data, TYPE_CLASS);
	if(array->array_type == TYPE_ARRAY)
		array->put_data(index, data, TYPE_ARRAY);	
}

void bastore(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_store('b', array->type);
	data[0] &= 0xFF;
	if(array->array_type == TYPE_BOOL)
		array->put_data(index, data, TYPE_BOOL);
	else if(array->array_type == TYPE_BYTE)
		array->put_data(index, data, TYPE_BYTE);
}

void castore(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_store('c', array->type);
	data[0] &= 0xFF;
	array->put_data(index, data, TYPE_CHAR);	
}

void sastore(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_store('s', array->type);
	data[0] &= 0xFFFF;
	array->put_data(index, data, TYPE_SHORT);	
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

void test_load(char func, u1 type) {
	if(type != TYPE_ARRAY) {
		printf("Error not array: memory.%caload\n",func);
		exit(0);
	}
}

void test_store(char func, u1 type) {
	if(type != TYPE_ARRAY) {
		printf("Error not array: memory.%castore\n",func);
		exit(0);
	}
}
