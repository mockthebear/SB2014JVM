#ifndef CLASS_ARRAY
#define CLASS_ARRAY

#include <stdio.h>
#include <string.h>

#include "definition.hpp"
#include "exception.hpp"
#include "class.hpp"
#include "class_loader.hpp"
#include "access_flag.hpp"


class ClassArray {
public:
	int max;
	int size;
	Class **classes;
	ClassLoader loader;

	ClassArray(int);
	
	void putstatic(Class *ref, int index, char *type, u4 *value);
	void getstatic(Class *ref, int index, char *type, u4 *value);
	
	Class *get_classref(char *);
	Class *new_class(char *);
	int get_index(char *);
	void setPath(char *);
	
	void print();
};

#endif
