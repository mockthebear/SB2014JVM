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

	int32_t to_int();
	float to_float();
	static int64_t to_long(u4, u4);
	static double to_double(u4, u4);
	static u4 to_bytes(void *);
	static void to_bytes_w(void *, u4 *);
	
	void print();
	static void print_w(Operand, Operand);
};


#endif
