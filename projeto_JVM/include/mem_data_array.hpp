#ifndef MEMORY_DATA_ARRAY
#define MEMORY_DATA_ARRAY

#include <stdio.h>
#include <string.h>

#include "definition.hpp"
#include "mem_data.hpp"
#include "access_flag.hpp"

class MemoryDataArray {
public:
	int max;
	int size;
	MemoryData **data;
	
	MemoryDataArray(int);
	
	void putfield(u4, char *, u4 *, char *);
	char *getfield(u4, char *, u4 *);
	u4 arraylength(u4);

	u4 new_instance(Class *);
	u4 new_array(int *, char *, Class *);
	void print();
	void print_min();
};

#endif
