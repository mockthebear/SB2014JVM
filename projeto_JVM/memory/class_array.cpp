#include "class_array.hpp"

u4 make_field_index(Class *);
	
ClassArray::ClassArray(int m) {
	max  = m;
	size = 0;
	//classes = new Class *[max];
	classes = (Class **)calloc(max,sizeof(Class *));
}

void ClassArray::putstatic(Class *classref, int index, u4 *data, u1 type) {
	/*
	u1 *classname;
	u1 *fieldname; 
	u1 *fieldtype;
	int index;
	
	classname = classref->get_cp_field_class(cp_index);
	fieldname = classref->get_cp_field_name(cp_index);
	fieldtype = classref->get_cp_field_type(cp_index);
	
	if(*fieldtype != type) {
		printf("Error field type %c != %c: class_array.putstatic\n", *fieldtype,type);
		exit(0);
	}
	classref = get_classref(classname);
	index = classref->get_field_index_by_name(fieldname);
	
	*/
	if(index == -1) {
		printf("Error field index = -1: class_array.putstatic\n");
		exit(0);
	}
	
	if( !isStatic(classref->get_field_flags(index)) ) {
		printf("Error field is not static: class_array.putstatic\n");
		exit(0);
	}
	classref->putstatic(index, data, type);
}

u1 ClassArray::getstatic(Class *classref, int index, u4 *data) {
	u1 type;
	/*
	u1 *classname;
	u1 *fieldname; 
	u1 *fieldtype;
	int index;
	
	classname = classref->get_cp_field_class(cp_index);
	fieldname = classref->get_cp_field_name(cp_index);
	fieldtype = classref->get_cp_field_type(cp_index);
	
	classref = get_classref(classname);
	index = classref->get_field_index_by_name(fieldname);
	*/
	if(index == -1) {
		printf("Error field index = -1: class_array.getstatic\n");
		exit(0);
	}
	if( !isStatic(classref->get_field_flags(index)) ) {
		printf("Error field is not static: class_array.getstatic\n");
		exit(0);
	}
	type = *( classref->get_field_type(index) );
	classref->getstatic(index, data, type);
	
	return type;
}

Class *ClassArray::get_classref(u1 *name) {
	Class *temp = NULL;
	int index = get_index(name);
	
	if(index > -1) {
		temp = classes[index];
	} /*else {
		temp = new_class(name);
	}*/
	return temp;
}

Class *ClassArray::new_class(u1 *name) {
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

int ClassArray::get_index(u1 *name) {
	int index = -1;
	for(int i=0; i<size; i++) {
		u1 *temp = classes[i]->get_cp_this_class();
		if(strcmp((char *)name, (char *)temp) == 0) {
			index = i;
			break;
		}
	}
	return index;
}

void ClassArray::print() {
	printf("ClassArray\n");
	printf("size: %d\n",size);
	for(int i=0; i<size; i++) {
		printf("[%p] %s, ",&classes[i],classes[i]->get_cp_this_class() );
	}
	printf("\n");
}

u4 make_field_index(Class *c) {
	u4 length = 0;
	
	for(int i=0; i<c->fields_count; i++) {
		u1 type = *( c->get_field_type(i) );
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


