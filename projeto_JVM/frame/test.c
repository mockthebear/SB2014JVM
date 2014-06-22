#include <stdio.h>
#include <stdint.h>

#include "definition.hpp"
#include "op_stack.hpp"
#include "local_var_array.hpp"



#ifdef __cplusplus
extern "C" {
#endif 

extern int _push(void *, char, void *);
extern int _push_w(void *, char, void *);
extern int _pop(void *, void *);
extern int _iadd(void *);
extern int _isub(void *);
extern int _imul(void *);
extern int _idiv(void *);
extern int _byte_copy_w(void *, void *);

#ifdef __cplusplus
}
#endif


union Float {
	float f;
	u4 i;
};


void teste_cost_l_d() {
	OperandStack op(100);
	
	op.lconst_1();
	op.lconst_0();
	op.dconst_1();
	op.dconst_0();
	op.print();
}

void teste_localVarArray() {
	OperandStack op(100);
	LocalVariableArray var(10);
	
	op.lconst_1();
	op.lconst_0();
	op.dconst_1();
	op.dconst_0();
	op.iconst_3();
	op.iconst_5();
	op.fconst_2();
	op.iconst_1();
	op.iconst_4();
	op.fconst_1();
	
	op.print();
	
	var.initialize(op.top-6, 6);
	var.print();
}


int main() {
	
	//teste_localVarArray();
	printf("%d\n",sizeof(Operand));
	return 0;
}

