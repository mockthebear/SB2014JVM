#ifndef MEMORY
#define MEMORY

#include <stdio.h>
#include <stdlib.h>

#include "class_array.hpp"
#include "mem_data_array.hpp"
#include "class.hpp"
#include "mem_data.hpp"


class Memory {
public:
	ClassArray *classes;
	MemoryDataArray *data;
	
	Memory(int c_size, int d_size);
	
	u4 op_new(Class *ref);
	
	void putstatic(Class *ref, u1 *fieldname, u4 *value, u1 *type);
	u1 *getstatic(Class *ref, u1 *fieldname, u4 *value);
	
	void putfield(u4 ref, u1 *fieldname, u4 *value, u1 *type);
	u1 *getfield(u4 ref, u1 *fieldname, u4 *value);
	
	u4 newarray(int size, u1 type);
	u4 anewarray(int size, u1 *type, Class *ref);
	u4 multianewarray(int *size, u1 *type, Class *ref);
	u4 arraylength(u4 ref);
	
	void iaload(u4 ref, int index, u4 *data);
	void laload(u4, int, u4 *);
	void faload(u4, int, u4 *);
	void daload(u4, int, u4 *);
	void aaload(u4, int, u4 *);
	void baload(u4, int, u4 *);
	void caload(u4, int, u4 *);
	void saload(u4, int, u4 *);
	
	void iastore(u4 ref, int index, u4 *data);
	void lastore(u4, int, u4 *);
	void fastore(u4, int, u4 *);
	void dastore(u4, int, u4 *);
	void aastore(u4, int, u4 *);
	void bastore(u4, int, u4 *);
	void castore(u4, int, u4 *);
	void sastore(u4, int, u4 *);
	
	 Class *get_classref(u1 *name);
	 Class *new_class(u1 *name);
	 void print();
};


#endif
