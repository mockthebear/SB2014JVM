#include "mem_data_array.hpp"

u4 make_fields_index(MemoryData *);
u4 make_array_index(MemoryData *);
	

MemoryDataArray::MemoryDataArray(int m) {
	max  = m;
	size = 0;
	data = new MemoryData *[max];
	for(int i=0;i<max;i++)
		data[i] = NULL;
}

void MemoryDataArray::putfield(u4 ref, char *classname, char *fieldname, char *type, u4 *value) {
	MemoryData *instance = (MemoryData *)ref;
	int index = instance->classref->get_field_index(fieldname);
	
	char *c_name = instance->classref->get_cp_this_class();
	char *f_type = instance->classref->get_field_type(index);
	
	if(strcmp(c_name, classname) != 0) {
		printf("Error class type %s != %s: mem_data_array.putfield\n", classname, c_name);
		exit(0);
	}
	if(strcmp(f_type, type) != 0) {
		printf("Error value type %s != %s: mem_data_array.putfield\n",type, f_type);
		exit(0);
	}
	if( isStatic( instance->classref->get_field_flags(index) ) ) {
		printf("Error field %s is static: mem_data_array.putfield\n", fieldname);
		exit(0);
	}
	instance->put_data(index, value, *f_type);

//#define TEST_PUTFIELD
#ifdef TEST_PUTFIELD
	printf("TEST_PUTFIELD\n")
	printf("addr %p, value %08X\n",instance, ref);
	printf("field index %d\n",index);
	printf("field type %s\n",type);
#endif

}

void MemoryDataArray::getfield(u4 ref, char *classname, char *fieldname, char *type, u4 *value) {
	MemoryData *instance = (MemoryData *)ref;
	int index = instance->classref->get_field_index(fieldname);
	
	char *c_name = instance->classref->get_cp_this_class();
	char *f_type = instance->classref->get_field_type(index);
	
	if(strcmp(c_name, classname) != 0) {
		printf("Error class type %s != %s: mem_data_array.getfield\n", classname, c_name);
		exit(0);
	}
	if(strcmp(f_type, type) != 0) {
		printf("Error value type %s != %s: mem_data_array.getfield\n",type, f_type);
		exit(0);
	}
	if( isStatic( instance->classref->get_field_flags(index) ) ) {
		printf("Error field is static: mem_data_array.getfield\n");
		exit(0);
	}
	instance->get_data(index, value, *f_type);
}

u4 MemoryDataArray::arraylength(u4 ref) {
	MemoryData *array = (MemoryData *)ref;
	u4 length = 0;
	if(array->type != TYPE_ARRAY) {
		printf("Error not array type %c: mem_data_array.arraylength\n", array->type);
		exit(0);
	}
	length = array->data_count;
	if(array->array_type == TYPE_ARRAY) {
		length *= arraylength(array->data[ array->data_index[0] ]);
	}
	return length;
}

u4 MemoryDataArray::new_instance(Class *ref) {
	MemoryData *m;
	
	if( ref->magic != 0xCAFEBABE )  {
		printf("Error invalid class format: mem_data_array.new_instance\n");
		exit(0);
	}
	m = new MemoryData;
	data[size] = m;
	size++;
	
	m->type = TYPE_CLASS;
	m->classref = ref;
	
	m->data_index = new int[ref->fields_count];
	m->data_count = (ref->fields_count) - (ref->static_fields_count);
	
	m->data_length = make_fields_index(m);
	m->data = (u4 *) calloc(m->data_length, sizeof(u4));

	
//#define TEST_NEW_INSTANCE
#ifdef TEST_NEW_INSTANCE
	printf("TEST_NEW_INSTANCE: mem_data_array\n");
	printf("instance addr %p\n", m);
#endif

	return (u4)m;
}

u4 MemoryDataArray::new_array(int *a_size, char *a_type, Class *ref) {
	MemoryData *m ;
	
	if(a_type[0] != TYPE_ARRAY) {
		printf("Error not array type %c: mem_data_array.new_array",a_type[0]);
		exit(0);
	}
	m = new MemoryData;
	data[size] = m;
	size++;
	
	m->type = TYPE_ARRAY;
	m->array_type = a_type[1];
	
	m->data_index = new int[ a_size[0] ];
	m->data_count = a_size[0];
	
	m->data_length = make_array_index(m);
	m->data = (u4 *)calloc(m->data_length, sizeof(u4));
	
	if(a_type[1] == TYPE_CLASS) {
		if(ref == NULL) {
			printf("Error class ref null %s: mem_data_array.new_array\n",a_type);
			exit(0);
		}
		for(u4 i=0; i<m->data_count; i++) {
			m->data[i] = new_instance(ref);
		}
	}
	
//#define TEST_NEW_ARRAY
#ifdef TEST_NEW_ARRAY
	printf("TEST_NEW_ARRAY: mem_data_array\n");
	printf("instance addr %p\n", m);
	printf("count %d\n",m->data_count);
	printf("size %d type %c\n", a_size[0], a_type[1]);
	printf("\n");
#endif

	if(a_type[1] == TYPE_ARRAY) {
		for(u4 i=0;i<m->data_count; i++) {
			m->data[i] = new_array(a_size+1, a_type+1, ref);
			
#ifdef TEST_NEW_ARRAY
			printf("add get [%d] %08X",i,m->data[i]);
#endif

		}
	}
	return (u4)m;
}

void MemoryDataArray::print() {
	printf("MemoryDataArray\n");
	printf("max: %d\t",max);
	printf("size:%d\n",size);
	for(int i=0; i<size; i++) {
		//printf("[%p] %c,",data[i],data[i]->type);
		printf("%d.[%p]\n",i,data[i]);
		data[i]->print();
		printf("\n");
	}
	printf("\n");
}

void MemoryDataArray::print_min() {
	printf(">Instances & Arrays\n");
	printf("  size: %d\n",size);
	printf("  ");
	for(int i=0; i<size; i++) {
		printf("[%p] ",data[i]);
		data[i]->print_min();
		//printf(", ");
	}
	printf("\n");
}

u4 make_fields_index(MemoryData *d) {
	u4 length = 0;
	
	for(u2 i=0; i<d->classref->fields_count; i++) {
		d->data_index[i] = d->classref->static_fields_index[i];
		char d_type = *( d->classref->get_field_type(i) );
		if (d->data_index[i] == -1) {
			d->data_index[i] = length++;
			if( (d_type == TYPE_LONG) || (d_type == TYPE_DOUBLE) )
				length++;
		} else {
			d->data_index[i] = -1;
		}
	}
	return length;
}

u4 make_array_index(MemoryData *d) {
	u4 length = 0;
	int inc;
	
	if( (d->array_type != TYPE_LONG) && (d->array_type != TYPE_DOUBLE) ) {
		inc = 1;
		length = d->data_count;
	} else {
		inc = 2;
		length = d->data_count * 2;
	}	
	for(u4 i=0; i<d->data_count; i++) {
		d->data_index[i] = i * inc;
	}
	return length;
}
