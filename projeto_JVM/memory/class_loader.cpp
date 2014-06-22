#include "class_loader.hpp"

//#define CLASSFILE "Test1.class"
//#define DEV

#define JAVA6VER 0x32

cp_info *cp_loader(FILE *, u2);
u2 *interface_loader(FILE *, u2);
Field *field_loader(FILE *, u2);
Method *method_loader(FILE *, u2);
Attribute *attribute_loader(FILE *, u2);

u1 read_u1(FILE *);
u2 read_u2(FILE *);
u4 read_u4(FILE *);
u1 *read_n(FILE *, u4);

Class *ClassLoader::load_class(u1 *name) {
	FILE *fp;
	char name_buff[100];
	temp = NULL;
	
	strcpy(name_buff, (char *)name);
	strcat(name_buff, ".class");
	
	if( (fp = fopen(name_buff, "rb")) == NULL) {
		printf("ClassNotFoundException: %s\n", name_buff);
		exit(0);
	}
	
	if( (temp = new Class) == NULL) {
		printf("MemoryAllocationException\n");
		fclose(fp);
		exit(0);
	}
	
	
	// Chegem de magic number 
	temp->magic = read_u4(fp);
	if(temp->magic != 0xCAFEBABE) {
		printf("ClassFormatError: Incompatible magic value %08X\n", temp->magic);
		delete temp;
		fclose(fp);
		exit(0);
	}
	
	// Chegem de versao
	temp->major_version = read_u2(fp);
	temp->minor_version = read_u2(fp);
	int version = temp->major_version + temp->minor_version;
	if(version > JAVA6VER) {
		printf("UnsupportedClassVersionError: %d\n", version);
		delete temp;
		fclose(fp);
		exit(0);
	}
	
	temp->cp_count = read_u2(fp);
	temp->constant_pool = cp_loader(fp, temp->cp_count);
	temp->access_flags = read_u2(fp);
	temp->this_class = read_u2(fp);
	temp->super_class = read_u2(fp);
	temp->interfaces_count = read_u2(fp);
	temp->interfaces = interface_loader(fp, temp->interfaces_count);
	temp->fields_count = read_u2(fp);
	temp->fields = field_loader(fp, temp->fields_count);
	temp->methods_count = read_u2(fp);
	temp->methods = method_loader(fp, temp->methods_count);
	temp->attributes_count = read_u2(fp);
	temp->attributes = attribute_loader(fp, temp->attributes_count);
	
	fclose(fp);
	
	return temp;
}

cp_info *cp_loader(FILE *fp, u2 n) {
	cp_info *cp = NULL;
	u1 tag;
	cp = new cp_info[n];
	
	for(int i=1; i<n; i++) {
		tag = read_u1(fp);
		cp[i].tag = tag;
		if( tag == TAG_CLASS ) {
			cp[i].name_index = read_u2(fp);
		} if( (tag == TAG_FIELD)  ||
			(tag == TAG_METHOD) ||
			(tag == TAG_IMETHOD) ) {
			cp[i].Ref.class_index = read_u2(fp);
			cp[i].Ref.name_and_type_index = read_u2(fp);
		} else if( tag == TAG_STRING ) {
			cp[i].string_index = read_u2(fp);
		} else if( (tag == TAG_INTEGER) || (tag == TAG_FLOAT) ) {
			cp[i].bytes = read_u4(fp);
		} else if( (tag == TAG_LONG) || (tag == TAG_DOUBLE) ) {
			cp[i].high_bytes = read_u4(fp);
			i++;
			cp[i].tag = tag;
			cp[i].low_bytes = read_u4(fp);
		} else if( tag == TAG_NAMEANDTYPE ) {
			cp[i].NameAndType.name_index = read_u2(fp);
			cp[i].NameAndType.descriptor_index = read_u2(fp);
		} else if( tag == TAG_UTF8 ) {
			u2 length = read_u2(fp);
			cp[i].utf8 = new u1[length+1];
			for(int j=0; j<length; j++)
				cp[i].utf8[j] = read_u1(fp);
			cp[i].utf8[length] = '\0';
		}
	}
	
	return cp;
}

u2 *interface_loader(FILE *fp, u2 n) {
	if(n == 0) 
		return NULL;

	u2 *interfaces = NULL;
	
	interfaces = new u2[n];
	for(int i=0; i<n; i++)
		interfaces[i] = read_u2(fp);
		
	return interfaces;
}

Field *ClassLoader::field_loader(FILE *fp, u2 n) {
	if(n == 0) 
		return NULL;
		
	Field *f = NULL;
	
	f = new Field[n];
	for(int i=0; i<n; i++) {
		f[i].access_flags = read_u2(fp);
		f[i].name_index = read_u2(fp);
		f[i].descriptor_index = read_u2(fp);
		f[i].attributes_count = read_u2(fp);
		f[i].attributes = new Attribute[f[i].attributes_count];
		f[i].attributes = attribute_loader(fp, f[i].attributes_count);
	}
	return f;
}

Method *ClassLoader::method_loader(FILE *fp, u2 n) {
	if(n == 0) 
		return NULL;
	
	Method *m = NULL;
	
	m = new Method[n];
	for(int i=0; i<n; i++) {
		m[i].access_flags = read_u2(fp);
		m[i].name_index = read_u2(fp);
		m[i].descriptor_index = read_u2(fp);
		m[i].attributes_count = read_u2(fp);
 		m[i].attributes = new Attribute[m[i].attributes_count];
		m[i].attributes = attribute_loader(fp, m[i].attributes_count);
	}
	return m;
}

Attribute *ClassLoader::attribute_loader(FILE *fp, u2 n) {
	if(n == 0) 
		return NULL;
	
	Attribute *a = NULL;
	
	a = new Attribute[n];
	for(int i=0; i<n; i++) {
		u1 *name;
		u4 length;
		
		a[i].name_index = read_u2(fp);
		name = temp->get_cp_utf8(a[i].name_index);
		length = read_u4(fp);
		
		if(name == NULL)
			return NULL;
			
//#define TEST_ATTRIBUTE
#ifdef TEST_ATTRIBUTE
		printf("TEST ATTRIBUTE: closs_loader",name);
		printf("\nget %s\n",name);
#endif

		
		if( strcmp((char *)name, "Code") == 0 ) {
			a[i].code = new Code;
			a[i].code->max_stack = read_u2(fp);
			a[i].code->max_locals = read_u2(fp);
			a[i].code->code_length = read_u4(fp);
			a[i].code->code = read_n(fp, a[i].code->code_length);
			a[i].code->exception_table_length = read_u2(fp);
			for(u2 j=0; j<a[i].code->exception_table_length; j++)
				a[i].code->exception_table = (exception_table_t *)read_n(fp, sizeof(exception_table_t));
			a[i].code->attributes_count = read_u2(fp);
			

#ifdef TEST_ATTRIBUTE			
			printf("CODE\n");
			printf("stack %d\n",a[i].code->max_stack);
			printf("locals %d\n",a[i].code->max_locals);
			printf("code len %d\n",a[i].code->code_length);
			for(u2 j=0; j<a[i].code->code_length; j++)
				printf("%02X ", a[i].code->code[j]);
			printf("\n");
			printf("exp len %d\n",a[i].code->exception_table_length);
			for(u2 j=0; j<a[i].code->exception_table_length; j++)
				printf("%d %d %d %X\n", a[i].code->exception_table[j].start_pc, 
										a[i].code->exception_table[j].end_pc, 
										a[i].code->exception_table[j].handler_pc, 
										a[i].code->exception_table[j].catch_type);
			printf("att count %d\n",a[i].code->attributes_count);
#endif			

			a[i].code->attributes = attribute_loader(fp, a[i].code->attributes_count);
		} else if( strcmp((char *)name, "Exceptions") == 0 ) {
			a[i].exceptions = new Exceptions;
			a[i].exceptions->number_of_exceptions = read_u2(fp);
			a[i].exceptions->exception_index_table = new u2[a[i].exceptions->number_of_exceptions];
			for(u2 j=0; j<a[i].exceptions->number_of_exceptions; j++)
				a[i].exceptions->exception_index_table[j] = read_u2(fp);
			
#ifdef TEST_ATTRIBUTE			
			printf("EXCEPTIONS\n");
			printf("number of excep %d\n",a[i].exceptions->number_of_exceptions);
			for(u2 j=0; j<a[i].exceptions->number_of_exceptions; j++)
				printf("%X ",a[i].exceptions->exception_index_table[j]);
			printf("\n");
#endif		
		} else {
			a[i].info = new a_info;
			a[i].info->length = length;
			a[i].info->bytes = new u1[a[i].info->length];
			for(u4 j=0; j<a[i].info->length; j++)
				a[i].info->bytes[j] = read_u1(fp);

#ifdef TEST_ATTRIBUTE					
			printf("INFO\n");
			printf("info len %d\n",a[i].info->length);
			for(u2 j=0; j<a[i].info->length; j++)
				printf("%02X ",a[i].info->bytes[j]);
			printf("\n");
#endif		
		}
	}
	return a;
}

u1 read_u1(FILE* fp) {
	u1 temp = 0;
	
	fread(&temp, sizeof(u1), 1, fp);
	return temp;
}

u2 read_u2(FILE* fp) {
	u2 temp = 0;
	
	for(int i=0; i<2; i++) {
		temp <<= 8;
		fread(&temp, sizeof(u1), 1, fp);
	}
	return temp;
}

u4 read_u4(FILE* fp) {
	u4 temp = 0;
	
	for(int i=0; i<4; i++) {
		temp <<= 8;
		fread(&temp, sizeof(u1), 1, fp);
	}
	return temp;
}

u1 * read_n(FILE* fp, u4 n) {
	u1 *temp;
	temp = new u1[n];
	fread(temp, sizeof(u1), n, fp);
	return temp;
}
