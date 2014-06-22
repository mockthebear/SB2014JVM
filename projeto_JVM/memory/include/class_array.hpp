#ifndef CLASS_ARRAY
#define CLASS_ARRAY

#include <stdio.h>
#include <string.h>

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
	
	void putstatic(Class *, int, u4 *, u1);
	u1 getstatic(Class *, int, u4 *);
	
	Class *get_classref(u1 *);
	Class *new_class(u1 *);
	int get_index(u1 *);
	
	void print();
};

#endif
