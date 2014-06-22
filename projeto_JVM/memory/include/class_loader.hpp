#ifndef CLASS_LOADER
#define CLASS_LOADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "class.hpp"

class ClassLoader {
public:
	Class *temp;
	
	Class *load_class(u1 *);
	Field *field_loader(FILE *, u2);
	Method *method_loader(FILE *, u2);
	Attribute *attribute_loader(FILE *, u2);
};

#endif

