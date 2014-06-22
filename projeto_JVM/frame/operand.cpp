#include "operand.hpp"


#ifdef __cplusplus
extern "C" {
#endif 

extern void _byte_copy(void *, void *);
extern void _byte_copy_w(void *, void *);
extern void _to_value64(void *, u4, u4);

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

int32_t Operand::to_int() {
	int32_t i = 0;
	
	_byte_copy(&bytes, &i);
	return i;
}

float Operand::to_float() {
	float f = 0.0F;
	
	_byte_copy(&bytes, &f);
	return f;
}

int64_t Operand::to_long(u4 high, u4 low) {
	int64_t l = 0L;
	
	_to_value64(&l, high, low);
	return l;
}

double Operand::to_double(u4 high, u4 low) {
	double d = 0.0D;
	
	_to_value64(&d, high, low);
	return d;
}

u4 Operand::to_bytes(void *src) {
	u4 bytes;
	
	_byte_copy(src, &bytes);
	return bytes;
}

void Operand::to_bytes_w(void *src, u4 *bytes) {
	_byte_copy_w(src, bytes);
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
	switch(high.type) {
		case TYPE_LONG:
			printf("long(%lld)", to_long(high.bytes, low.bytes));
			break;
		case TYPE_DOUBLE:
			printf("double(%lf)", to_double(high.bytes, low.bytes));
			break;
		default:
			break;
	}
	printf("\n");
}

