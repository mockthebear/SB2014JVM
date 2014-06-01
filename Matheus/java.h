#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "filereader.h"
#ifndef JAVAH
#define JAVAH


char Strings_[30][50];
char Flags[30][50];
typedef struct{
    uint8_t tag;
    uint16_t index;
    //10 method ref / 2 field ref
    uint16_t class_index;
    uint16_t name_and_type_index;
    //8 string
    uint16_t string_index;
    // 7 = class
    uint16_t name_index;
    // 12 = NameAndType
    uint16_t descriptor_index;

    // 1 = Utf8
    uint16_t lengh;
    unsigned char *bytes;
    //
    unsigned char *name;

} contstant_method;

typedef struct{
    uint16_t attribute_name_index;
    uint32_t attribute_lenght;
    uint16_t sourcefile_index;
} FileAttr;
typedef struct{
    uint16_t            start_pc;
    uint16_t            line_number;
} LNT;  //Line_Number_Table
typedef struct{
    uint16_t            attribute_name_index;
    uint32_t            attribute_lenght;
    uint16_t            line_number_table_lenght;
    LNT                 **LNTs;
} AttrOfAttr;

typedef struct{
    uint16_t            attribute_name_index;
    uint32_t            attribute_lenght;
    uint16_t            max_stack;
    uint16_t            max_locals;
    uint32_t            code_lenght;
    unsigned char       *code;
    uint16_t            exception_table_lenght;
    uint16_t            attributes_count;
    AttrOfAttr          **Attrs;

} Attribute;


typedef struct{
    uint16_t            acess_flags;
    uint16_t            name_index;
    uint16_t            descriptor_index;
    uint16_t            attributes_count;
    Attribute           **Attributes;
} Method;

typedef struct{
    uint32_t            magic;
    uint16_t            minor;
    uint16_t            major;
    uint16_t            constant_pull_count;
    contstant_method    **constant_pool;
    uint16_t            access_flags;
    uint16_t            this_class;
    uint16_t            super_class;
    uint16_t            interfaces_count;
    uint16_t            fields_count;
    uint16_t            methods_count;
    Method              **methods;
    uint16_t            attributes_count;
    FileAttr            **FAttr;


} Java;


Java *JAVA_createJava(FileHandler *f);
const unsigned char* JAVA_GetUTF8(Java *j,int i);
int JAVA_parseFileAttributes(FileHandler *f,Java *j);
int JAVA_parseConstantPool(FileHandler *f,Java *j);
int JAVA_parseMethods(FileHandler *f,Java *j);
void JAVA_freeJava(Java *j);

#endif // JAVAH
