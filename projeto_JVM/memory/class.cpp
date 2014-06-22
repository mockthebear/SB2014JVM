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


u1 *Class::get_cp_this_class() {
	return get_cp_class_name(this_class);
}

u1 *Class::get_cp_super_class() {
	return get_cp_class_name(super_class);
}

u1 *Class::get_cp_class_name(u2 cp_index) {
	test_cp("get_cp_class_name", TAG_CLASS, cp_index, this);
	cp_index = constant_pool[cp_index].name_index;
	return get_cp_utf8(cp_index);
}

u1 *Class::get_cp_field_class(u2 cp_index) {
	test_cp("get_cp_field_class", TAG_FIELD, cp_index, this);
	return get_cp_ref_class(cp_index);
}

u1 *Class::get_cp_field_name(u2 cp_index) {
	test_cp("get_cp_field_name", TAG_FIELD, cp_index, this);
	return get_cp_ref_name(cp_index);
}

u1 *Class::get_cp_field_type(u2 cp_index) {
	test_cp("get_cp_field_type", TAG_FIELD, cp_index, this);
	return get_cp_ref_descriptor(cp_index);
}

u1 *Class::get_cp_method_class(u2 cp_index) {
	test_cp("get_cp_method_class", TAG_METHOD, cp_index, this);
	return get_cp_ref_class(cp_index);
}

u1 *Class::get_cp_method_name(u2 cp_index) {
	test_cp("get_cp_method_name", TAG_METHOD, cp_index, this);
	return get_cp_ref_name(cp_index);
}

u1 *Class::get_cp_method_descriptor(u2 cp_index) {
	test_cp("get_cp_field_descriptor", TAG_METHOD, cp_index, this);
	return get_cp_ref_descriptor(cp_index);
}

u1 *Class::get_cp_ref_class(u2 cp_index) {
	cp_index = constant_pool[cp_index].Ref.class_index;
	return get_cp_class_name(cp_index);
}

u1 *Class::get_cp_ref_name(u2 cp_index) {
	cp_index = constant_pool[cp_index].Ref.name_and_type_index;
	test_cp("get_cp_ref_name", TAG_NAMEANDTYPE, cp_index, this);
	cp_index = constant_pool[cp_index].NameAndType.name_index;
	return get_cp_utf8(cp_index);
}

u1 *Class::get_cp_ref_descriptor(u2 cp_index) {
	cp_index = constant_pool[cp_index].Ref.name_and_type_index;
	test_cp("get_cp_ref_descriptor", TAG_NAMEANDTYPE, cp_index, this);
	cp_index = constant_pool[cp_index].NameAndType.descriptor_index;
	return get_cp_utf8(cp_index);
}

u1 *Class::get_cp_utf8(u2 cp_index) {
	test_cp("get_cp_utf8", TAG_UTF8, cp_index, this);
	return constant_pool[cp_index].utf8;
}

int Class::get_field_index(u2 cp_index) {
	int index;
	u1 *name = get_cp_field_name(cp_index);
	
	index = get_field_index_by_name(name);
	if(index == -1) {
		printf("Error field %s not found: class.get_field_index\n", name);
		exit(0);
	}
	return index;
}

int Class::get_method_index(u2 cp_index) {
	int index;
	u1 *name = get_cp_method_name(cp_index);
	
	index = get_field_index_by_name(name);
	if(index == -1) {
		printf("Error method %s not found: class.get_method_index\n", name);
		exit(0);
	}
	return index;
}

int Class::get_field_index_by_name(u1 *name) {
	int index = -1;
	
	for(int i=0; i<fields_count; i++) {
		if(strcmp((char *)name, (char *)get_field_name(i)) == 0) {
			index = i;
			break;
		}
	}
	return index;
}

int Class::get_method_index_by_name(u1 *name) {
	int index = -1;
	
	for(int i=0; i<methods_count; i++) {
		if(strcmp((char *)name, (char *)get_method_name(i)) == 0) {
			index = i;
			break;
		}
	}
	return index;
}

u2 Class::get_field_flags(int index) {
	return fields[index].access_flags;
}

u1 *Class::get_field_name(int index) {
	u2 cp_index = fields[index].name_index;
	return get_cp_utf8(cp_index);
}

u1 *Class::get_field_type(int index) {
	u2 cp_index = fields[index].descriptor_index;
	return get_cp_utf8(cp_index);
}

u1 *Class::get_method_name(int index) {
	u2 cp_index = methods[index].name_index;
	return get_cp_utf8(cp_index);
}

u1 *Class::get_method_descriptor(int index) {
	u2 cp_index = methods[index].descriptor_index;
	return get_cp_utf8(cp_index);
}

Code *Class::get_method_code(int index) {
	Attribute a = methods[index].attributes[0];
	if( strcmp( (char *)get_cp_utf8(a.name_index), "Code" ) != 0 ) {
		printf("Error attribute[0] not code: class.get_method_code");
		exit(0);
	}
	return a.code;
}

/* Print */
void Class::print() {
	printf("class name: %s\n", get_cp_this_class());
	printf("super name: %s\n", get_cp_super_class());
	printf("fields count: %d\n", fields_count);
	for(int i=0;i<fields_count; i++) {
		printf("   [%d]", i);
		printf("\tname: %s", get_field_name(i));
		printf("\ttype: %s", get_field_type(i));
		printf("\n");
	}
	printf("methods count: %d\n", methods_count);
	for(int i=0;i<methods_count; i++) {
		printf("   [%d]", i);
		printf("\tname: %s", get_method_name(i));
		printf("\tdescr: %s", get_method_descriptor(i));
		printf("\n");
	}
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
			printf("   (%ld)\n", t);
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

void Class::print_statics() {
	printf("Static Fields\n");
	printf("statics: %d\n", static_fields_count);
	for(u2 i=0;i<static_fields_count; i++) {
		if(static_fields_index[i] != -1) {
			printf("[%d]->[%d] ",i,static_fields_index[i]);
			u1 d_type;
			d_type = *( get_field_type(i) );
			printf("%c| ",d_type);
			printf("%s\t", get_field_name(i));
			printf("%08X", static_fields[ static_fields_index[i] ]);
			if( (d_type == TYPE_LONG) || (d_type == TYPE_DOUBLE) ) {
				printf("%08X", static_fields[ static_fields_index[i]+1 ]);
			}
			printf("\n");
		}
	}
		
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
