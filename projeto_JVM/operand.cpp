#include "operand.hpp"


#ifdef __cplusplus
extern "C" {
#endif 

extern void _to_value32(void *, void *);
extern u4 _to_byte(void *);
extern u4 _get_high(void *);

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
	bytes = _to_byte(v);
}

void Operand::set_high(u1 t, void* v) {
	type = t;
	bytes = _get_high(v);
}

void Operand::set_low(u1 t, void* v) {
	type = t;
	bytes = _to_byte(v);
}

int32_t Operand::to_int() {
	int32_t i = 0;
	
	_to_value32(&bytes, &i);
	return i;
}

float Operand::to_float() {
	float f = 0.0F;
	
	_to_value32(&bytes, &f);
	return f;
}

void Operand::print() {
	printf("[%c] %08X ", type, bytes);
	switch(type) {
		case TYPE_INT:
			printf("int(%d)", to_int());
			break;
		case TYPE_FLOAT:
			printf("float(%f)", to_float());
			break;
		default:
			break;
	}
	printf("\n");
}

void Operand::print_w(Operand high, Operand low) {
	printf("[%c] %08X%08X ", high.type, high.bytes, low.bytes);

	printf("\n");
}

void Operand::print_min() {
	printf("(%c)%08X ", type, bytes);
}
