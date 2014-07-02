#include "memory.hpp"

void test_array(const char *func, MemoryData *array, int index);
void test_type(const char *func, MemoryData *array, char type);


Memory::Memory(int c_array_size, int m_array_size) {
	classes = new ClassArray(c_array_size);
	data = new MemoryDataArray(m_array_size);
}

MemoryData *Memory::op_new_superInstance(char *supername, MemoryData *superInst) {
	if(strcmp(supername, CLASS_OBJECT) == 0) {
		return superInst;
	} else {
		Class *superRef = get_classref(supername);
		if(superRef == NULL) {
			exception("NullPointerException at Memory.op_new_superInstance\n");
		}
		supername = superRef->get_cp_super_class();
		superInst = op_new_superInstance(supername, superInst);
		superInst = op_new_instance(superRef, superInst);
		return superInst;
	}
}

MemoryData *Memory::op_new_instance(Class *ref, MemoryData *superInst) {
	MemoryData *instance;
	
	char *supername = ref->get_cp_super_class();
	
	instance = data->new_instance(ref, superInst);
	return instance;
}

MemoryData *Memory::op_new(Class *ref, MemoryData *superInst) {
	MemoryData *instance;
	char *supername = ref->get_cp_super_class();
	
	superInst = op_new_superInstance(supername, superInst);
	
	instance = op_new_instance(ref, superInst);
	
	return instance;
}

void Memory::putstatic(Class *ref, int index, char *type, u4 *value) {
	classes->putstatic(ref, index, type, value);
}

void Memory::getstatic(Class *ref, int index, char *type, u4 *value) {
	classes->getstatic(ref, index, type, value);
}

void Memory::putfield(u4 ref, char *classname, char *fieldname, char *type, u4 *value) {
	data->putfield(ref, classname, fieldname, type, value);
}

void Memory::getfield(u4 ref, char *classname, char *fieldname, char *type, u4 *value) {
	return data->getfield(ref, classname, fieldname, type, value);
}

u4 Memory::newarray(int size, u1 a_type) {
	enum {A_BOOL = 4, A_CHAR, A_FLOAT, A_DOUBLE, A_BYTE, A_SHORT, A_INT, A_LONG};
	u4 array;
	char *type = new char[2];

	if( (a_type == A_BOOL) || (a_type == A_CHAR) ||
		(a_type == A_BYTE) || (a_type == A_SHORT) ||
		(a_type == A_INT) ) {
		
		*type = TYPE_INT;
	} else if(a_type == A_LONG) {
		*type = TYPE_LONG;
	} else if(a_type == A_FLOAT) {
		*type = TYPE_FLOAT;
	} else if(a_type == A_DOUBLE) {
		*type = TYPE_DOUBLE;
	}
	type[1] = '\0';
	array = data->new_array(&size, type);
	return array;
}

u4 Memory::anewarray(int size, char *classname) {
	u4 array;
	int length = strlen(classname) + 1;
	char *type = (char *)calloc(length,sizeof(char));;
	
	*type = TYPE_CLASS;
	strcat(type, classname);
	
	array = data->new_array(&size, type);
	return array;
}

u4 Memory::multianewarray(int *size, char *a_type) {
	u4 array;
	int length = strlen(a_type+1);
	char *type = (char *)calloc(length,sizeof(char));
	char *temp = type;
	
	a_type++;
	while(*a_type == TYPE_ARRAY)
		*(temp++) = *(a_type++);

	if(*a_type == TYPE_CLASS) {
		while(*a_type != ';')
			*(temp++) = *(a_type++);
	} else {
		*temp = *a_type;
	}
	array = data->new_array(size, type);
	return array;
}


u4 Memory::arraylength(u4 ref) {
	return data->arraylength(ref);
}

void Memory::iaload(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_array("iaload", array, index);
	test_type("iaload", array, TYPE_INT);
	array->get_data(index, data, TYPE_INT);
}

void Memory::laload(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_array("laload", array, index);
	test_type("laload", array, TYPE_LONG);
	array->get_data(index, data, TYPE_LONG);
}

void Memory::faload(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_array("faload", array, index);
	test_type("faload", array, TYPE_FLOAT);
	array->get_data(index, data, TYPE_FLOAT);
}

void Memory::daload(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_array("daload", array, index);
	test_type("daload", array, TYPE_DOUBLE);
	array->get_data(index, data, TYPE_DOUBLE);
}

void Memory::aaload(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_array("aaload", array, index);
	if( (TYPE_CLASS != *(array->array_type)) && (TYPE_ARRAY != *(array->array_type)) ) {
		printf("Error type L/[ != %c: memory.aaload\n",*(array->array_type));
		exit(0);
	}
	if(*(array->array_type) == TYPE_CLASS)
		array->get_data(index, data, TYPE_CLASS);
	if(*(array->array_type) == TYPE_ARRAY)
		array->get_data(index, data, TYPE_ARRAY);
}

void Memory::baload(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_array("baload", array, index);
	if( (TYPE_BOOL != *(array->array_type)) && (TYPE_BYTE != *(array->array_type)) ) {
		printf("Error type B/Z != %c: memory.baload\n",*(array->array_type));
		exit(0);
	}
	if(*(array->array_type) == TYPE_BOOL)
		array->get_data(index, data, TYPE_BOOL);
	else if(*(array->array_type) == TYPE_BYTE)
		array->get_data(index, data, TYPE_BYTE);
	data[0] &= 0xFF;
}

void Memory::caload(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_array("caload", array, index);
	test_type("caload", array, TYPE_CHAR);
	array->get_data(index, data, TYPE_CHAR);
	data[0] &= 0xFF;
}

void Memory::saload(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_array("saload", array, index);
	test_type("saload", array, TYPE_SHORT);
	array->get_data(index, data, TYPE_SHORT);
	data[0] &= 0xFFFF;
}

void Memory::iastore(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_array("iastore", array, index);
	test_type("iastore", array, TYPE_INT);
	array->put_data(index, data, TYPE_INT);	
}

void Memory::lastore(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_array("lastore", array, index);
	test_type("lastore", array, TYPE_LONG);
	array->put_data(index, data, TYPE_LONG);	
}
	
void Memory::fastore(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_array("fastore", array, index);
	test_type("fastore", array, TYPE_FLOAT);
	array->put_data(index, data, TYPE_FLOAT);	
}

void Memory::dastore(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_array("dastore", array, index);
	test_type("dastore", array, TYPE_DOUBLE);
	array->put_data(index, data, TYPE_DOUBLE);	
}

void Memory::aastore(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_array("aastore", array, index);
	if( (TYPE_CLASS != *(array->array_type)) && (TYPE_ARRAY != *(array->array_type)) ) {
		printf("Error type L/[ != %c: memory.aastore\n",*(array->array_type));
		exit(0);
	}
	if(*(array->array_type) == TYPE_CLASS)
		array->put_data(index, data, TYPE_CLASS);
	if(*(array->array_type) == TYPE_ARRAY)
		array->put_data(index, data, TYPE_ARRAY);	
}

void Memory::bastore(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_array("bastore", array, index);
	if( (TYPE_BOOL != *(array->array_type)) && (TYPE_BYTE != *(array->array_type)) ) {
		printf("Error type B/Z != %c: memory.bastore\n",*(array->array_type));
		exit(0);
	}
	data[0] &= 0xFF;
	if(*(array->array_type) == TYPE_BOOL)
		array->put_data(index, data, TYPE_BOOL);
	else if(*(array->array_type) == TYPE_BYTE)
		array->put_data(index, data, TYPE_BYTE);
}

void Memory::castore(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_array("castore", array, index);
	test_type("castore", array, TYPE_CHAR);
	data[0] &= 0xFF;
	array->put_data(index, data, TYPE_CHAR);	
}

void Memory::sastore(u4 ref, int index, u4 *data) {
	MemoryData *array;
	
	array = (MemoryData *)ref;
	test_array("sastore", array, index);
	test_type("sastore", array, TYPE_SHORT);
	data[0] &= 0xFFFF;
	array->put_data(index, data, TYPE_SHORT);	
}

Class *Memory::get_classref(char *name) {
	return classes->get_classref(name);
}

Class *Memory::new_class(char *name) {
	return classes->new_class(name);
}

void Memory::print() {
	printf(">>Memory\n");
	classes->print();
	data->print();
}

void test_array(const char *func, MemoryData *array, int index) {
	if(array->type != TYPE_ARRAY) {
		printf("Error not array: memory.%s\n",func);
		exit(0);
	}
	if(index >= (int)array->data_count) {
		printf("Error index out of range index:%d array size:%d: memory.%s\n",index,array->data_count,func);
		exit(0);
	}
}
void test_type(const char *func, MemoryData *array, char type) {
	if(type != *(array->array_type)) {
		printf("Error type %c != %c: memory.%s\n",type,*(array->array_type),func);
		exit(0);
	}
}
