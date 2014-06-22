#ifndef MEMORY_DATA_ARRAY
#define MEMORY_DATA_ARRAY

#include <stdio.h>

#include "definition.hpp"
#include "mem_data.hpp"
#include "access_flag.hpp"

class MemoryDataArray {
public:
	int max;
	int size;
	MemoryData **data;
	
	MemoryDataArray(int);
	
	void putfield(u4, u2, u4 *, u1);
	u1 getfield(u4, u2, u4 *);
	u4 arraylength(u4);
	/*
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
	
	u4 new_instance(Class *);
	u4 new_array(int *, u1 *, Class *);
	void print();
	void print_min();
};

#endif
