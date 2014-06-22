
static StackFrame	frames;
static Memory		memoria;

static void (*opcode[256]) () = {
	nop, aconst_null, 
	iconst_m1, iconst_0, iconst_1, iconst_2, iconst_3, iconst_4, iconst_5, 
	iload, lload, fload, dload, aload, 
	...
	istore_0, istore_1, istore_2, istore_3, 
	lstore_0, lstore_1, lstore_2, lstore_3, 
	...
};

int main(int argc, char **argv) {
	
	memoria.carrega_classe("Entrada.class");
	
	//inicia o programa
	metodo = memoria.pega_metodo("main");
	code = metodo.pega_code();
	param = metodo.pega_param();
	frames.cria_frame(code, param);
	while(!frames.esta_vazia()) {
		byte_code = frames.pega_byte_code();
		opcode(byte_code);
	}
	
	return 0;
}

void iload() {
	indice = frames.pega_byte_code();
	indice<<8;
	indice | frames.pega_byte_code();
	
	dado = frames.iload(indice); // frames.frame_atual.local_var_array.iload(indice)
	frame.push(dado);			// frames.frame_atual.operand_stack.push(dado)
}

void iconst_4() {
	// so envolve pilha de operando. por isso o frame so chama operand_stack.iconst_4()
	
	frames.iconst_4();  // frames.frame_atual.operand_stack.iconst_4()
}

void op_new() {
	//envolve memoria e vetor de variaveis. por isso eh implementado aqui
	
	indice = frames.pega_byte_code();
	indice<<8;
	indice | frames.pega_byte_code();

	classe = frames.this_class(); // frames.frame_atual.local_var_array[0]
	nome = classe.pega_constante_pool(indice);   
	referencia  = memoria.cria_classe(nome);
}

void invokevirtual() {
	indice = frames.pega_byte_code();
	indice<<8;
	indice | frames.pega_byte_code();

	instancia = frames.this_class();
	classe = instancia.pega_classe;
	nome = classe.pega_constante_pool(indice);   
	metodo = classe.pega_metodo(nome);
	code = metodo.pega_code();
	param = metodo.pega_param();
	frames.cria_frame(code, param);
}
// ... resto dos byte codes