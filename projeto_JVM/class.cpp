#include "class.hpp"

void test_cp(const char *, u2 , u2, Class * );

void Class::putstatic(int index, u4 *in_data, u1 in_type) {
	u1 d_type;
	
	d_type = *( get_field_type(index) );

	if(d_type != in_type) {
		printf("Error data type %c != %c: class.pustatic\n",d_type,in_type);
		exit(0);
	}
	if(static_fields_index[index] == -1) {
		printf("Error index value %d: class.pustatic\n" ,(short)static_fields_index[index]);
		exit(0);
	}
	
	static_fields[ static_fields_index[index] ] = in_data[0];
	if( (d_type == TYPE_LONG) || (d_type == TYPE_DOUBLE) )
		static_fields[ static_fields_index[index]+1 ] = in_data[1];
}

void Class::getstatic(int index, u4 *out_data, u1 out_type) {
	u1 d_type;
	
	d_type = *( get_field_type(index) );

	if(d_type != out_type) {
		printf("Error data type %c != %c: class.gettatic\n",d_type,out_type);
		exit(0);
	}
	if(static_fields_index[index] == -1) {
		printf("Error index value %d: class.gettatic\n" ,(short)static_fields_index[index]);
		exit(0);
	}
	
	out_data[0] = static_fields[ static_fields_index[index] ];
	if( (d_type == TYPE_LONG) || (d_type == TYPE_DOUBLE) )
		out_data[1] = static_fields[ static_fields_index[index]+1 ];
}

u4 Class::get_cp_tag(u2 cp_index) {
	if(cp_index<1 || cp_index>cp_count) {
		printf("Error cp index %d: class.get_cp_tag\n",cp_index);
		exit(0);
	}
	return constant_pool[cp_index].tag;
}

u4 Class::get_cp_bytes(u2 cp_index) {
	if(cp_index<1 || cp_index>cp_count) {
		printf("Error cp index %d: class.get_cp_tag\n",cp_index);
		exit(0);
	}
	return constant_pool[cp_index].bytes;
}

char *Class::get_cp_this_class() {
	return get_cp_class_name(this_class);
}

char *Class::get_cp_super_class() {
	if(super_class > 0)
		return get_cp_class_name(super_class);
	else
		return NULL;
}

char *Class::get_cp_class_name(u2 cp_index) {
	test_cp("get_cp_class_name", TAG_CLASS, cp_index, this);
	cp_index = constant_pool[cp_index].name_index;
	return get_cp_utf8(cp_index);
}

char *Class::get_cp_field_class(u2 cp_index) {
	test_cp("get_cp_field_class", TAG_FIELD, cp_index, this);
	return get_cp_ref_class(cp_index);
}

char *Class::get_cp_field_name(u2 cp_index) {
	test_cp("get_cp_field_name", TAG_FIELD, cp_index, this);
	return get_cp_ref_name(cp_index);
}

char *Class::get_cp_field_type(u2 cp_index) {
	test_cp("get_cp_field_type", TAG_FIELD, cp_index, this);
	return get_cp_ref_descriptor(cp_index);
}

char *Class::get_cp_method_class(u2 cp_index) {
	test_cp("get_cp_method_class", TAG_METHOD, cp_index, this);
	return get_cp_ref_class(cp_index);
}

char *Class::get_cp_method_name(u2 cp_index) {
	test_cp("get_cp_method_name", TAG_METHOD, cp_index, this);
	return get_cp_ref_name(cp_index);
}

char *Class::get_cp_method_descriptor(u2 cp_index) {
	test_cp("get_cp_method_descriptor", TAG_METHOD, cp_index, this);
	return get_cp_ref_descriptor(cp_index);
}

char *Class::get_cp_imethod_class(u2 cp_index) {
	test_cp("get_cp_imethod_class", TAG_IMETHOD, cp_index, this);
	return get_cp_ref_class(cp_index);
}

char *Class::get_cp_imethod_name(u2 cp_index) {
	test_cp("get_cp_imethod_name", TAG_IMETHOD, cp_index, this);
	return get_cp_ref_name(cp_index);
}

char *Class::get_cp_imethod_descriptor(u2 cp_index) {
	test_cp("get_cp_imethod_descriptor", TAG_IMETHOD, cp_index, this);
	return get_cp_ref_descriptor(cp_index);
}

char *Class::get_cp_ref_class(u2 cp_index) {
	cp_index = constant_pool[cp_index].Ref.class_index;
	return get_cp_class_name(cp_index);
}

char *Class::get_cp_ref_name(u2 cp_index) {
	cp_index = constant_pool[cp_index].Ref.name_and_type_index;
	test_cp("get_cp_ref_name", TAG_NAMEANDTYPE, cp_index, this);
	cp_index = constant_pool[cp_index].NameAndType.name_index;
	return get_cp_utf8(cp_index);
}

char *Class::get_cp_ref_descriptor(u2 cp_index) {
	cp_index = constant_pool[cp_index].Ref.name_and_type_index;
	test_cp("get_cp_ref_descriptor", TAG_NAMEANDTYPE, cp_index, this);
	cp_index = constant_pool[cp_index].NameAndType.descriptor_index;
	return get_cp_utf8(cp_index);
}

char *Class::get_cp_string(u2 cp_index) {
	test_cp("get_cp_string", TAG_STRING, cp_index, this);
	cp_index = constant_pool[cp_index].string_index;
	return get_cp_utf8(cp_index);
}

char *Class::get_cp_utf8(u2 cp_index) {
	test_cp("get_cp_utf8", TAG_UTF8, cp_index, this);
	return constant_pool[cp_index].utf8;
}

int Class::get_cp_field_index(u2 cp_index) {
	int index;
	char *name = get_cp_field_name(cp_index);
	
	index = get_field_index(name);
	if(index == -1) {
		printf("Error field %s not found: class.get_field_index\n", name);
		exit(0);
	}
	return index;
}

int Class::get_cp_method_index(u2 cp_index) {
	int index;
	char *name = get_cp_method_name(cp_index);
	char *descriptor = get_cp_method_descriptor(cp_index);
	
	index = get_method_index(name, descriptor);
	if(index == -1) {
		printf("Error method %s not found: class.get_method_index\n", name);
		exit(0);
	}
	return index;
}

int Class::get_field_index(char *name) {
	int index = -1;
	
	for(int i=0; i<fields_count; i++) {
		if(strcmp((char *)name, (char *)get_field_name(i)) == 0) {
			index = i;
			break;
		}
	}
	return index;
}

int Class::get_method_index(char *name, char *descriptor) {
	int index = -1;
	
	for(int i=0; i<methods_count; i++) {
		if( (strcmp(name, get_method_name(i)) == 0) &&
			(strcmp(descriptor, get_method_descriptor(i)) == 0) )
		{
			index = i;
			break;
		}
	}
	return index;
}

int Class::get_method_main() {
	int index = -1;
	
	for(int i=0; i<methods_count; i++) {
		if(strcmp("main", get_method_name(i)) == 0) {
			index = i;
			break;
		}
	}
	return index;
}

int Class::get_method_clinit() {
	int index = -1;
	
	for(int i=0; i<methods_count; i++) {
		if(strcmp("<clinit>", get_method_name(i)) == 0) {
			index = i;
			break;
		}
	}
	return index;
}

u2 Class::get_field_flags(int index) {
	return fields[index].access_flags;
}

char *Class::get_field_name(int index) {
	u2 cp_index = fields[index].name_index;
	return get_cp_utf8(cp_index);
}

char *Class::get_field_type(int index) {
	u2 cp_index = fields[index].descriptor_index;
	return get_cp_utf8(cp_index);
}

u2 Class::get_method_flags(int index) {
	return methods[index].access_flags;
}

char *Class::get_method_name(int index) {
	u2 cp_index = methods[index].name_index;
	return get_cp_utf8(cp_index);
}

char *Class::get_method_descriptor(int index) {
	u2 cp_index = methods[index].descriptor_index;
	return get_cp_utf8(cp_index);
}

Code *Class::get_method_code(int index) {
	Attribute a = methods[index].attributes[0];
	if( strcmp( get_cp_utf8(a.name_index), "Code" ) != 0 ) {
		printf("Error attribute[0] not code: class.get_method_code");
		exit(0);
	}
	return a.code;
}

char *Class::get_interface_name(int index) {
	if(index>0 || index<interfaces_count) {
		printf("Error index value: class.get_interface_name");
		exit(0);
	}
	u2  cp_index = interfaces[index];
	return get_cp_class_name(cp_index);
}

bool Class::isInterface(char *interface) {
	bool result = false;
	for(int i=0; i<interfaces_count; i++) {
		if(strcmp( interface, get_interface_name(i) ) == 0) {
			result = true;
			break;
		}
	}
	
	return result;
}

/* Print */
void Class::print() {
	printf("magic number: 0x%X\n", magic);
	printf("major ver: 0x%02X (%d)\n", major_version, major_version);
	printf("minor ver: 0x%02X (%d)\n", minor_version, minor_version);
	printf("access flags: 0x%04X (%d)\n", access_flags, access_flags);
	printf("class name: %s\n", get_cp_this_class());
	printf("super name: %s\n", get_cp_super_class());
	printf("\n");
	printf("cp count: %d\n", cp_count);
	print_cp();
	printf("\n");
	printf("fields count: %d\n", fields_count);
	printField();
	printf("\n");
	printf("methods count: %d\n", methods_count);
	printMethod();
}

void Class::print_cp() {
	const char *tipo[16] = { NULL, "Utf8", NULL, "Integer", "Float", "Long", "Double", "Class",
						"String", "Field", "Method", "Interface", "Name&Type"};
	u2 tag;
	printf("ConstantPool\n");
	for(int i=1; i<cp_count; i++) {
		tag = constant_pool[i].tag;
		printf("  %2d.%s\t ", i, tipo[tag]);
		if(tag == TAG_CLASS) {
			printf("#%2d\t", constant_pool[i].name_index);
			
			printf("    %s\n", get_cp_class_name(i));
		} else if( (tag == TAG_FIELD)  ||
				   (tag == TAG_METHOD) ||
				   (tag == TAG_IMETHOD) ) {
			printf("#%2d, ",constant_pool[i].Ref.class_index);
			printf("#%2d", constant_pool[i].Ref.name_and_type_index);
			
			printf("   %s, ", get_cp_ref_class(i) );
			printf("%s, ", get_cp_ref_name(i) );
			printf("%s\n", get_cp_ref_descriptor(i) );
		} else if(tag == TAG_STRING) {
			printf("#%2d\n", constant_pool[i].string_index);
		} else if(tag == TAG_INTEGER) {
			printf("%08X   (%d)\n", constant_pool[i].bytes, constant_pool[i].bytes);
		} else if(tag == TAG_FLOAT) {
			printf("%08X   (%.4f)\n", constant_pool[i].bytes, *((float *)&constant_pool[i].bytes));
		} else if(tag == TAG_LONG) {
			printf("%08X, ", constant_pool[i].high_bytes);
			printf("%08X ", constant_pool[i+1].low_bytes);
			
			int64_t t = constant_pool[i].high_bytes;
			t<<=32;
			t|=constant_pool[i+1].low_bytes;
			printf("   (%lld)\n", t);
			i++;
		} else if(tag == TAG_DOUBLE) {
			printf("%08X, ", constant_pool[i].high_bytes);
			printf("%08X ", constant_pool[i+1].low_bytes);
			
			int64_t t = constant_pool[i].high_bytes;
			t<<=32;
			t|=constant_pool[i+1].low_bytes;
			printf("  (%.4lf)\n", *((double *)&t) );
			i++;
		} else if(tag == TAG_NAMEANDTYPE) {
			printf("#%2d, ", constant_pool[i].NameAndType.name_index);
			printf("#%2d", constant_pool[i].NameAndType.descriptor_index);
			
			printf("   %s, ", get_cp_utf8(constant_pool[i].NameAndType.name_index));
			printf("%s\n", get_cp_utf8(constant_pool[i].NameAndType.descriptor_index));
		} else if(tag == TAG_UTF8) {
			printf("%s\n", constant_pool[i].utf8);
		} else {
			printf("tag invalido: %d\n", tag);
		}
	}
}

void Class::print_cp_utf8(u2 cp_index) {
	cp_info cp = constant_pool[cp_index];
	u2 tag = cp.tag;
	switch (tag) {
		case (TAG_CLASS):
			printf("; //class \" %s \" ", get_cp_class_name(cp_index));
			break;
	 
		case (TAG_FIELD):
			printf("; //Field %s.", get_cp_ref_class(cp_index) );
			printf("%s:", get_cp_ref_name(cp_index) );
			printf("%s", get_cp_ref_descriptor(cp_index) );
			break;
			
		case (TAG_METHOD):
			printf("; //Method %s.", get_cp_ref_class(cp_index) );
			printf("%s:", get_cp_ref_name(cp_index) );
			printf("%s", get_cp_ref_descriptor(cp_index) );
			break;
			
		case (TAG_IMETHOD):
			printf("; //IMethod %s.", get_cp_ref_class(cp_index) );
			printf("%s:", get_cp_ref_name(cp_index) );
			printf("%s", get_cp_ref_descriptor(cp_index) );
			break;
		
		case (TAG_STRING):
			printf("; //String %s", get_cp_string(cp_index));
			break;
			
		case (TAG_INTEGER):
			int32_t *i;
			i = (int32_t *)(&cp.bytes);
			printf("; //int %d", *i);
			break;
			
		case (TAG_LONG):
			int64_t *l;
			uint64_t x;
			x = cp.bytes;
			x <<= 32;
			cp = constant_pool[cp_index+1];
			x |= cp.bytes;
			l = (int64_t *) &x;
			printf("; //long %lldl", *l);
			break;
			
		case (TAG_FLOAT):
			float *f;
			f = (float *)(&cp.bytes);
			printf("; //float %.4ff", *f);
			break;
			
		case (TAG_DOUBLE):
			double *d;
			uint64_t y;
			y = cp.bytes;
			y <<= 32;
			cp = constant_pool[cp_index+1];
			y |= cp.bytes;
			d = (double *) &y;
			printf("; //double %.4lfd", *d);
			break;
	}
}

void print_access(u2 flags) {
	if(isPublic(flags))
		printf("public ");
	if(isPrivate(flags))
		printf("private ");
	if(isProtected(flags))
		printf("protected ");
	if(isFinal(flags))
		printf("final ");
	if(isAbstract(flags))
		printf("abstract ");
	if(isStatic(flags))
		printf("static ");
}

void Class::printField() {
	for(int i=0;i<fields_count; i++) {
		printf("[%d] ", i);
		print_access(get_field_flags(i));
		printf("%s:", get_field_name(i));
		printf("%s\n", get_field_type(i));
	}
}

void Class::printMethod() {
	const char * op_nameTable[256]={
		//Primeira familia de instrucoes 0x0Xh
		"nop", "aconst_null", "iconst_m1", "iconst_0", "iconst_1", "iconst_2", "iconst3", "iconst_4",
		"iconst_5", "lconst_0", "lconst_1", "fconst_0", "fconst_1", "fconst_2", "dconst_0", "dconst_1",
		
		//Segunda familia de instrucoes 0x1Xh
		"bipush", "sipush", "ldc", "ldc_w", "ldc2_w", "iload", "lload", "fload",
		"dload", "aload", "iload_0", "iload_1", "iload_2", "iload_3", "lload_0", "lload_1",
		
		//Terceira familia de instrucoes 0x2Xh
		"lload_2", "lload_3", "fload_0", "fload_1", "fload_2", "fload_3", "dload_0", "dload_1",
		"dload_2", "dload_3", "aload_0", "aload_1", "aload_2", "aload_3", "iaload", "laload",
		
		//Quarta familia de instrucoes 0x3Xh
		"faload", "daload", "aaload", "baload", "caload", "saload", "istore", "lstore",
		"fstore", "dstore", "astore", "istore_0", "istore_1", "istore_2", "istore_3", "lstore_0",
		
		//Quinta familia de instrucoes 0x4Xh
		"lstore_1", "lstore_2", "lstore_3", "fstore_0", "fstore_1", "fstore_2", "fstore_3", "dstore_0",
		"dstore_1", "dstore_2", "dstore_3", "astore_0", "astore_1", "astore_2", "astore_3", "iastore",
		
		//Sexta familia de instrucoes 0x5Xh
		"lastore", "fastore", "dastore", "aastore", "bastore", "castore", "sastore", "pop",
		"pop2", "dup", "dup_x1", "dup_x2", "dup2", "dup2_x1", "dup2_x2", "swap",
		
		//Setima familia de instrucoes 0x6Xh
		"iadd", "ladd", "fadd", "dadd", "isub", "lsub", "fsub", "dsub",
		"imul", "lmul", "fmul", "dmul", "idiv", "ldiv", "fdiv", "ddiv",
		
		//Oitava familia de instrucoes 0x7Xh
		"irem", "lrem", "frem", "drem", "ineg", "lneg", "fneg", "dneg",
		"ishl", "lshl", "ishr", "lshr", "iushr", "lushr", "iand", "land",
		
		//Nona familia de instrucoes 0x8Xh
		"ior", "lor", "ixor", "lxor", "iinc", "i2l", "i2f", "i2d",
		"l2i", "l2f", "l2d", "f2i", "f2l", "f2d", "d2i", "d2l",
		
		//Decima familia de instrucoes 0x9Xh
		"d2f", "i2b", "i2c", "i2s", "lcmp", "fcmpl", "fcmpg", "dcmpl",
		"dcmpg", "ifeq", "ifne", "iflt", "ifge", "ifgt", "ifle", "if_icmpeq",
		
		//Decima primeira familia de instrucoes 0xAXh
		"if_icmpne", "if_icmplt", "if_icmpge", "if_icmpgt", "if_icmple", "if_acmpeg", "if_acmpne", "goto",
		"jsr", "ret", "table_switch", "lookup_switch", "ireturn", "lreturn", "freturn", "dreturn",
		
		//Decima segunda familia de instrucoes 0xBXh
		"areturn", "return", "getstatic", "putstatic", "getfield", "putfield", "invokevirtual", "invokespecial",
		"invokestatic", "invokeInterface", NULL, "new", "newArray", "anewArray", "arrayLength", "athrow",
		
		//Decima terceira familia de instrucoes 0xCXh
		"checkCast", "instanceOf", "monitorEnter", "monitorExit", "wide", "multiNewArray", "ifNull", "ifNonNull",
		"goto_w", "jsr_w", "breakPoint",NULL, NULL, NULL, NULL, NULL,
		
		//Decima quarta familia de instrucoes 0xDXh
		NULL, NULL, NULL, NULL,NULL, NULL, NULL, NULL,
		NULL, NULL, NULL, NULL,NULL, NULL, NULL, NULL,
		
		//Decima quinta familia de instrucoes 0xEXh
		NULL, NULL, NULL, NULL,NULL, NULL, NULL, NULL,
		NULL, NULL, NULL, NULL,NULL, NULL, NULL, NULL,
		
		//Decima sexta familia de instrucoes 0xFXh
		NULL, NULL, NULL, NULL,NULL, NULL, NULL, NULL,
		NULL, NULL, NULL, NULL,NULL, NULL, "impdep1", "impdep2"
	};
	
	for(int i=0;i<256; i++) {
		//printf("[%02X] %s\n",i,op_nameTable[i]);
	}
	for(int i=0;i<methods_count; i++) {
		printf("[%d] ", i);
		print_access(get_method_flags(i));
		printf("%s: ", get_method_name(i));
		printf("%s\n", get_method_descriptor(i));
		Code *c = get_method_code(i);
		printf("  stack=%d, locals=%d\n", c->max_stack, c->max_locals);
		for(u2 pc = 0; pc<c->code_length; pc++) {
			u1 op = c->code[pc];
			//printf("  %2d:[%02X] %s\t", pc, op, op_nameTable[op]);
			printf("  %2d:  %s\t", pc, op_nameTable[op]);
			if( 
				(op==0x10) || (op==0x15) || (op==0x16) || (op==0x17) || (op==0x18) || 
				(op==0x19) || (op==0x36) || (op==0x37) || (op==0x38) || (op==0x39) || 
				(op==0x3A) || (op==0xA9) || (op==0xBC)
			) {
				printf(" %d", (int8_t)c->code[++pc]);
			} else if( (op==0x12) ) {		// ldc
				u2 t = c->code[++pc];
				printf(" #%d", t);
				print_cp_utf8(t);
			} else if(
				(op==0x13) || (op==0x14) || (op==0xB2) || (op==0xB3) || (op==0xB4) || 
				(op==0xB5) || (op==0xB6) || (op==0xB7) || (op==0xB8) || (op==0xBB) || 
				(op==0xBD) || (op==0xC0) || (op==0xC1)		// constant pool index
			) {
				u2 t = c->code[++pc];
				t <<= 8;
				t |= c->code[++pc];
				printf(" #%d", t);
				print_cp_utf8(t);
			} else if(
				(op==0x99) || (op==0x9A) || (op==0x9B) || (op==0x9C) || (op==0x9D) || 
				(op==0x9E) || (op==0x9F) || (op==0xA0) || (op==0xA1) || (op==0xA2) || 
				(op==0xA3) || (op==0xA4) || (op==0xA5) || (op==0xA6) || (op==0xA7) || 
				(op==0xA8) || (op==0xC6) || (op==0xC7)		// branch bytes
			) {
				u2 t = c->code[++pc];
				t <<= 8;
				t |= c->code[++pc];
				t = (pc-2) + t;
				printf(" %d", t);
			} else if( (op==0x11) ) {		// sipush
				u2 t = c->code[++pc];
				t <<= 8;
				t |= c->code[++pc];
				printf(" %d", (int16_t)t);
			} else if( (op==0x84) ) {		// iinc
				printf(" %d,", c->code[++pc]);
				printf(" %d", c->code[++pc]);
			} else if( (op==0xC5) ) {		// multianewarray
				u2 t = c->code[++pc];
				t <<= 8;
				t |= c->code[++pc];
				printf(" #%d,", t);
				printf(" %d", c->code[++pc]);
				print_cp_utf8(t);
			} else if( (op==0xB9) ) { 		// invokeinterface
				u2 t = c->code[++pc];
				t <<= 8;
				t |= c->code[++pc];
				printf(" #%d,", t);
				printf(" %d,", c->code[++pc]);
				printf(" %d", c->code[++pc]);
				print_cp_utf8(t);
			} else if( (op==0xC8) || (op==0xC9) ) {	// goto_w, jsr_w
				u4 t = c->code[++pc];
				t <<= 8;
				t |= c->code[++pc];
				t <<= 8;
				t |= c->code[++pc];
				t <<= 8;
				t |= c->code[++pc];
				printf(" #%d", t);
				print_cp_utf8(t);
			} else if( (op==0xC4) ) {		// wide
				printf("\n");
				op = c->code[++pc];
				if(op!=0x84) {	// <t>load, <t>store
					printf("%d: %s\t", pc, op_nameTable[op]);
					u2 t = c->code[++pc];
					t <<= 8;
					t |= c->code[++pc];
					printf(" #%d", t);
					print_cp_utf8(t);
				} else {		// iinc
					printf("%d: %s\t", pc, op_nameTable[op]);
					u2 t = c->code[++pc];
					t <<= 8;
					t |= c->code[++pc];
					printf(" %d,", t);
					t = c->code[++pc];
					t <<= 8;
					t |= c->code[++pc];
					printf(" %d", t);
				}
			}
			printf("\n");
		}
		printf("\n");
	}
}

void Class::print_statics() {
	//printf("Static Fields\n");
	printf("    statics: %d\n", static_fields_count);
	printf("    ");
	for(u2 i=0;i<fields_count; i++) {
		if(static_fields_index[i] != -1) {
			printf("[%d] ",static_fields_index[i]);
			u1 d_type;
			d_type = *( get_field_type(i) );
			printf("(%c)",d_type);
			printf("%08X ", static_fields[ static_fields_index[i] ]);
			if( (d_type == TYPE_LONG) || (d_type == TYPE_DOUBLE) ) {
				printf("[%d] ",static_fields_index[i]+1);
				printf("(%c)",d_type);
				printf("%08X ", static_fields[ static_fields_index[i]+1 ]);
			}
		}
	}
	printf("\n");
		
}

void test_cp(const char *func, u2 tag, u2 cp_index, Class *c) {
	if(cp_index<1 || cp_index>c->cp_count) {
		printf("Error cp index %d: class.%s\n",cp_index,func);
		exit(0);
	}
	if(c->constant_pool[cp_index].tag != tag) {
		printf("Error cp tag %d != %d[%d]: class.%s\n",tag, c->constant_pool[cp_index].tag,cp_index,func);
		exit(0);
	}
}
