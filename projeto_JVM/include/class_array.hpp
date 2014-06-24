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
	
	void putstatic(Class *, char *, u4 *, char *);
	char *getstatic(Class *, char *, u4 *);
	
	Class *get_classref(char *);
	Class *new_class(char *);
	int get_index(char *);
	
	void print();
};

#endif
