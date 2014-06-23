#include <stdio.h>

#include "memory.hpp"
#include "class.hpp"

void teste_memory() {
	Memory memory(100, 100);
	Class *a, *b;
	u4 out;
	int index;
	
	a = memory.get_classref((u1 *)"C1");
	if(a == NULL) {
		Code *c;
		a = memory.new_class((u1 *)"C1");
		index = a->get_method_index_by_name((u1 *)"<clinit>");
		printf("index %d\n",index);
		if(index != -1)
			c = a->get_method_code(index);
	}
	//(void)memory.new_class((u1 *)"C2");
	
	b = memory.get_classref((u1 *)"C2");
	if(b == NULL) {
		Code *c;
		b = memory.new_class((u1 *)"C2");
		index = b->get_method_index_by_name((u1 *)"<clinit>");
		printf("index %d\n",index);
		if(index != -1) {
			c = b->get_method_code(index);
			for(u4 i=0; i<c->code_length;i++)
				printf("%X ",c->code[i]);
			printf("\n");
		}
	}
	
	out = memory.newarray(3, 4);
	printf("new array %08X\n",out);
	out = memory.arraylength(out);
	printf("array size %d\n",out);
	out = memory.anewarray(2, (u1 *)"[L", b);
	printf("new array %08X\n",out);
	out = memory.arraylength(out);
	printf("array size %d\n",out);
	int size[5] = {2,2,2};
	out = memory.multianewarray(size, (u1 *)"[[[L", a);
	printf("new array %08X\n",out);
	out = memory.arraylength(out);
	printf("array size %d\n",out);
	memory.print();
}

void teste_memory2() {
	Memory memory(100, 100);
	Class *a, *b;
	u4 out;
	
	a = memory.new_class((u1 *)"C1");
	b = memory.new_class((u1 *)"C2");
	
	u4 data[10] = {0x55, 0x99, 0x45, 0x811};
	u4 data1[2] = {-1,-1};
	u4 index;
	out = memory.newarray(3, 4);
	index = 1;
	memory.iastore(out, index, data);
	index = 2;
	memory.iastore(out, index, data+1);
	memory.iaload(out, index, data1);
	printf("value %X %X\n",data1[0],data1[1]);
	
	out = memory.anewarray(2, (u1 *)"[J", b);
	index = 1;
	memory.lastore(out, index, data+2);
	
	memory.print();
}

int main() {

	teste_memory2();
	
	return 0;
}
