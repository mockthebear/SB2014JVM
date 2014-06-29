#include "operand.hpp"


#ifdef __cplusplus
extern "C" {
#endif 

extern void __to_value32(void *, u4);
extern u4 __get_byte(void *);
extern u4 __get_high(void *);

#ifdef __cplusplus
}
#endif

Operand::Operand() {
	type = 0;
	bytes = 0;
}

Operand::Operand(u1 t, u4 b) {
	type = t;
	bytes = b;
}

void Operand::set_byte(u1 t, u4 b) {
	type = t;
	bytes = b;
}

void Operand::set_value(u1 t, void* v) {
	type = t;
	bytes = __get_byte(v);
}

void Operand::set_high(u1 t, void* v) {
	type = t;
	bytes = __get_high(v);
}

void Operand::set_low(u1 t, void* v) {
	type = t;
	bytes = __get_byte(v);
}

int32_t Operand::to_int() {
	int32_t i = 0;
	
	__to_value32(&i, bytes);
	return i;
}

float Operand::to_float() {
	float f = 0.0F;
	
	__to_value32(&f, bytes);
	return f;
}

void Operand::print() {
	printf("(%c)%08X ", type, bytes);
}
