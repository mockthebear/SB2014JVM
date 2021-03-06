#include "class_array.hpp"

u4 make_field_index(Class *);
	
ClassArray::ClassArray(int m) {
	max  = m;
	size = 0;
	classes = (Class **)calloc(max,sizeof(Class *));
	loader.temp = NULL;
	loader.filepath = NULL;
}

void ClassArray::putstatic(Class *ref, int index , char *type, u4 *value) {
	if(ref == NULL) {
		exception("NullPointerException at ClassArray.putstatic");
	}
	u2 flags = ref->get_field_flags(index);
	
	if( !isStatic(flags) ) {
		exception("IncompatibleClassChangeError at ClassArray.putstatic");
	}
	char *f_type = ref->get_field_type(index);
	
	if( strcmp(f_type, type) != 0) {
		printf("Error field type %s != %s: class_array.putstatic\n", f_type, type);
		exit(0);
	}
	ref->putstatic(index, value, *f_type);
}

void ClassArray::getstatic(Class *ref, int index, char *type, u4 *value) {
	if(ref == NULL) {
		exception("NullPointerException at ClassArray.getstatic");
	}
	u2 flags = ref->get_field_flags(index);
	
	if( !isStatic(flags) ) {
		exception("IncompatibleClassChangeError at ClassArray.getstatic");
	}
	char *f_type = ref->get_field_type(index);
	
	if( strcmp(f_type, type) != 0) {
		printf("Error field type %s != %s: class_array.getstatic\n", f_type, type);
		exit(0);
	}
	ref->getstatic(index, value, *f_type);
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

void ClassArray::setPath(char *path) {
	loader.setPath(path);
}

void ClassArray::print() {
	printf(">Classes\n");
	printf("  size: %d\n",size);
	for(int i=0; i<size; i++) {
		printf("  [%p] %s\n",&classes[i],classes[i]->get_cp_this_class() );
		classes[i]->print_statics();
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
