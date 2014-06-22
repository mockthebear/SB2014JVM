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

int main() {

	teste_memory();
	
	return 0;
}
