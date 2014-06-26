#include "class_array.hpp"

u4 make_field_index(Class *);
	
ClassArray::ClassArray(int m) {
	max  = m;
	size = 0;
	classes = (Class **)calloc(max,sizeof(Class *));
	loader.temp = NULL;
}

void ClassArray::putstatic(Class *ref, char *fieldname, u4 *value, char *type) {
	int index;
	char *f_type;
	
	index = ref->get_field_index(fieldname);
	if(index == -1) {
		printf("Error field index = -1: class_array.putstatic\n");
		exit(0);
	}
	if( !isStatic(ref->get_field_flags(index)) ) {
		printf("Error field is not static: class_array.putstatic\n");
		exit(0);
	}
	f_type = ref->get_field_type(index);
	if( strcmp((char *)f_type, (char *)type) != 0) {
		printf("Error field type %s != %s\n", f_type, type);
		exit(0);
	}
	ref->putstatic(index, value, *f_type);
}

char *ClassArray::getstatic(Class *ref, char *fieldname, u4 *value) {
	int index;
	char *f_type;
	
	index = ref->get_field_index(fieldname);
	if(index == -1) {
		printf("Error field index = -1: class_array.getstatic\n");
		exit(0);
	}
	if( !isStatic(ref->get_field_flags(index)) ) {
		printf("Error field is not static: class_array.getstatic\n");
		exit(0);
	}
	f_type = ref->get_field_type(index);
	ref->getstatic(index, value, *f_type);
	
	return f_type;
}

Class *ClassArray::get_classref(char *name) {
	Class *temp = NULL;
	int index = get_index(name);
	
	if(index > -1) {
		temp = classes[index];
	}
	
	return temp;
}

Class *ClassArray::new_class(char *name) {
	Class *temp;
	temp = loader.load_class(name);

	temp->static_fields_index = new int[temp->fields_count];
	temp->static_fields_count = 0;
	
	temp->static_fields_length = make_field_index(temp);
	temp->static_fields = (u4 *) calloc(temp->static_fields_length, sizeof(u4));
	
	classes[size] = temp;
	size++;
	return temp;
}

int ClassArray::get_index(char *name) {
	int index = -1;
	for(int i=0; i<size; i++) {
		char *c_name = classes[i]->get_cp_this_class();
		if(strcmp((char *)name, (char *)c_name) == 0) {
			index = i;
			break;
		}
	}
	return index;
}

void ClassArray::print() {
	printf(">Classes\n");
	printf("  size: %d\n",size);
	printf("  ");
	for(int i=0; i<size; i++) {
		printf("[%p] %s, ",&classes[i],classes[i]->get_cp_this_class() );
	}
	printf("\n");
}

u4 make_field_index(Class *c) {
	u4 length = 0;
	
	for(int i=0; i<c->fields_count; i++) {
		char type = *( c->get_field_type(i) );
		if( isStatic(c->get_field_flags(i)) ) {
			c->static_fields_count++;
			c->static_fields_index[i] = length;
			length++;
			if( (type == TYPE_LONG) || (type == TYPE_DOUBLE) )
				length++;
		} else {
			c->static_fields_index[i] = -1;
		}
	}
	return length;
}


