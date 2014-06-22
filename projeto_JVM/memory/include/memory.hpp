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
	
	Memory(int, int);
	
	u4 op_new(Class *);
	
	u4 newarray(int, u1);
	u4 anewarray(int, u1 *, Class *);
	u4 multianewarray(int *, u1 *, Class *);
	u4 arraylength(u4);
	/*
	
	void putstatic(Class *, u2, u4 *, u1);
	u1 getstatic(Class *, u2, u4 *);
	
	void putfield(u4, u2, u4 *, u1);
	u1 getfield(u4, u2, u4 *);
	
	
	void iaload();
	void laload();
	void faload();
	void daload();
	void aaload();
	void baload();
	void caload();
	void saload();
	
	void iastore();
	void lastore();
	void fastore();
	void dastore();
	void aastore();
	void bastore();
	void castore();
	void sastore();
	*/
	 Class *get_classref(u1 *);
	 Class *new_class(u1 *);
	 void print();
};


#endif
