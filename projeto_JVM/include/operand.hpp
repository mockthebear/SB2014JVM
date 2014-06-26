#ifndef OPERAND
#define OPERAND

#include <stdio.h>
#include <stdint.h>

#include "definition.hpp"


#define TYPE_BYTE	'B'
#define TYPE_CHAR	'C'
#define TYPE_SHORT	'S'
#define TYPE_INT	'I'
#define TYPE_LONG	'J'
#define TYPE_FLOAT	'F'
#define TYPE_DOUBLE	'D'
#define TYPE_BOOL	'Z'
#define TYPE_CLASS	'L'
#define TYPE_ARRAY	'['

class Operand {
public:
	u4 type;
	u4 bytes;

	Operand();
	Operand(u1, u4);
	
	void set_byte(u1 t, u4 b);
	void set_value(u1 t, void *v);
	void set_high(u1 t, void *v);
	void set_low(u1 t, void *v);
	
	int32_t to_int();
	float to_float();
	
	void print();
	static void print_w(Operand, Operand);
	void print_min();
};


#endif
