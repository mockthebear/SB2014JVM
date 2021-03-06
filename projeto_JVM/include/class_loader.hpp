#ifndef CLASS_LOADER
#define CLASS_LOADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "class.hpp"

class ClassLoader {
public:
	Class *temp;
	char *filepath;

	
	Class *load_class(char *);
	Field *field_loader(FILE *, u2);
	Method *method_loader(FILE *, u2);
	Attribute *attribute_loader(FILE *, u2);
	
	void setPath(char *);
};

#endif
