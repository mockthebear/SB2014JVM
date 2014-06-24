#ifndef ATTRIBUTE
#define ATTRIBUTE

#include "definition.hpp"

typedef struct a_info_t a_info;
typedef struct Code_t Code;
typedef struct Exceptions_t Exceptions;


typedef struct  {
	u2 name_index;
	union {
		a_info *info;
		Code *code;
		Exceptions *exceptions;
	};
} Attribute;

typedef struct  {
 	u2 start_pc;
	u2 end_pc;
	u2 handler_pc;
	u2 catch_type;
} exception_table_t;

struct a_info_t {
	u4 length;
	u1 *bytes;
};

struct Code_t  {
	u2 max_stack;
	u2 max_locals;
	u4 code_length;
	u1 *code;
	u2 exception_table_length;
	exception_table_t *exception_table;
	u2 attributes_count;
	Attribute *attributes;
};

struct Exceptions_t {
	u2 number_of_exceptions;
	u2 *exception_index_table;
};

#endif
