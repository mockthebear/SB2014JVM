#include <stdint.h>

#ifndef JAVASTH
#define JAVASTH

/*

*/



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
    const unsigned char *name;

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
    unsigned char       *raw;
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
    uint16_t            thispc;

} Attribute;




typedef struct{
    uint16_t            acess_flags;
    uint16_t            name_index;
    uint16_t            descriptor_index;
    uint16_t            attributes_count;
    uint16_t            this_index;
    Attribute           **Attributes;
} Method;

typedef struct{
    uint16_t            acess_flags;
    uint16_t            name_index;
    uint16_t            descriptor_index;
    uint16_t            attributes_count;
} Field;



const unsigned char Strings_[30][50] = {
    "0",
    "Utf8",
    "2",
    "3",
    "4",
    "5",
    "6",
    "Class",
    "String",
    "Fieldref",
    "Methodref",
    "InterfaceMethodRef",
    "NameAndType",
    "13",
    "14",

    };
const char Flags[40][50] = {
    "0",
    "public",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "public static",
    "10",
    "11",
    "12",
    "13",
    "14",
    "15",
    "16",
    "17",
    "18",
    "19",
    "20",
    "super user",
    "22",
    "23",
    "24",
    "25",
    "26",
    "27",
    "28",
    "29",
    "30",
    "31",
    "32",
    "super user",
    "34",
    "36",

};



#endif
