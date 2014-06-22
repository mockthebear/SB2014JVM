#ifndef CLASS
#define CLASS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definition.hpp"
#include "attribute.hpp"


typedef struct {
	u4 tag;
	union {	// todos os membros tem tamanho 4 bytes
		u2 name_index;	// Class
		struct {		// Fieldref, Methodref, IMethodref
			u2 class_index;
			u2 name_and_type_index;
		} Ref;
		u2 string_index;// String
		u4 bytes;		// Integer, Float
		u4 high_bytes;	// Long, Double
		u4 low_bytes;
		struct {		// Name and Type
			u2 name_index;
			u2 descriptor_index;
		} NameAndType;
		u1 *utf8;		// Utf8
	};
} cp_info;

typedef struct {
	u2 access_flags;
	u2 name_index;
	u2 descriptor_index;
	u2 attributes_count;
	Attribute *attributes;
} Field;

typedef struct {
	u2 access_flags;
	u2 name_index;
	u2 descriptor_index;
	u2 attributes_count;
	Attribute *attributes;
} Method;


class Class {
public:
	u4 magic;
	u2 minor_version;
	u2 major_version;
	u2 cp_count;
	cp_info *constant_pool;
	u2 access_flags;
	u2 this_class;
	u2 super_class;
	u2 interfaces_count;
	u2 *interfaces;
	u2 fields_count;
	Field *fields;
	u2 methods_count;
	Method *methods;
	u2 attributes_count;
	Attribute *attributes;
	
	u2 static_fields_count;
	int *static_fields_index;
	u4 static_fields_length;
	u4 *static_fields;
	
	void putstatic(int, u4 *, u1);
	void getstatic(int, u4 *, u1);
	
	
	u1 *get_cp_this_class();
	u1 *get_cp_super_class();
	u1 *get_cp_class_name(u2);
	u1 *get_cp_field_class(u2);
	u1 *get_cp_field_name(u2);
	u1 *get_cp_field_type(u2);
	u1 *get_cp_method_class(u2);
	u1 *get_cp_method_name(u2);
	u1 *get_cp_method_descriptor(u2);
	u1 *get_cp_ref_class(u2);
	u1 *get_cp_ref_name(u2);
	u1 *get_cp_ref_descriptor(u2);
	u1 *get_cp_utf8(u2);
	
	int get_field_index(u2);
	int get_method_index(u2);
	int get_field_index_by_name(u1 *);
	int get_method_index_by_name(u1 *);
	u2 get_field_flags(int);
	u1 *get_field_name(int);
	u1 *get_field_type(int);
	u1 *get_method_name(int);
	u1 *get_method_descriptor(int);
	Code *get_method_code(int);
		
	void print();
	void print_cp();
	void print_statics();
};

enum cp_tag { 	ZERO, 
				TAG_UTF8,	//1
				DOIS, 		
				TAG_INTEGER,//3 
				TAG_FLOAT, 	//4
				TAG_LONG, 	//5
				TAG_DOUBLE, //6
				TAG_CLASS, 	//7
				TAG_STRING, //8
				TAG_FIELD, 	//9
				TAG_METHOD,	//10
				TAG_IMETHOD, //11
				TAG_NAMEANDTYPE	//12
			};

#endif