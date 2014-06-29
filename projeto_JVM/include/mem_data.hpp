#ifndef MEMORY_DATA
#define MEMORY_DATA

#include <stdio.h>
#include <stdlib.h>

#include "definition.hpp"
#include "class.hpp"

class MemoryData {
public:
	u4 type;
	union {
		Class *classref;
		char array_type;
	};
	u4 superInst;
	u4 data_count;
	int *data_index;
	u4	data_length;
	u4 *data;
	
	void put_data(int, u4 *, char);
	void get_data(int, u4 *, char);
	
	void print();
};

#endif

