//
//  jclass.h
//  jvm
//
//

#ifndef jvm_jclass_h
#define jvm_jclass_h
/*
 Includes
 */
#include "data_management.h"

/*
 Macros
 */
#define VALID_MAGIC_SIGNATURE 0xCAFEBABE

//Flags de direito de acesso
#define ACCESS_FLAG_PUBLIC    0x0001h
#define ACCESS_FLAG_PRIVATE   0x0002h
#define ACCESS_FLAG_PROTECTED 0x0004h
#define ACCESS_FLAG_STATIC    0x0008h
#define ACCESS_FLAG_FINAL     0x0010h
#define ACCESS_FLAG_SUPER     0x0020h
#define ACCESS_FLAG_BRIDGE    0x0040h
#define ACCESS_FLAG_VARARGS   0x0080h
#define ACCESS_FLAG_NATUVE    0x0100h
#define ACCESS_FLAG_INTERFACE 0x0200h
#define ACCESS_FLAG_ABSTRACT  0x0400h
#define ACCESS_FLAG_STRICT    0x0800h
#define ACCESS_FLAG_SYNTHETIC 0x1000h
#define ACCESS_FLAG_ENUM      0x4000h

//Tags de tipos constante
#define CONSTANT_UTF8                1
#define CONSTANT_INTEGER             3
#define CONSTANT_FLOAT               4
#define CONSTANT_LONG                5
#define CONSTANT_DOUBLE              6
#define CONSTANT_CLASS               7
#define CONSTANT_STRING              8
#define CONSTANT_FIELDREF            9
#define CONSTANT_METHODREF          10
#define CONSTANT_INTERFACEMETHODREF 11
#define CONSTANT_NAMEANDTYPE        12
#define CONSTANT_METHODHANDLE       15
#define CONSTANT_METHODTYPE         16
#define CONSTANT_INVOKEDYNAMIC      18


/*
 Typedefs JVM
 */


//Tabela de constantes
typedef struct cpinfo{
    u1 tag;
    u1 info[];
}cp_info;

//Tabela de atributos
typedef struct attributeinfo{
    u2 attribute_name_index;
    u4 attribute_length;
    u1 info[];//info[attribute_length];
}attribute_info;

//Tabela de campos
typedef struct fieldinfo{
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info attributes[];//attributes[attributes_count];
}field_info;

//Tabela de métodos
typedef struct methodinfo{
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info attributes[];//attributes[attributes_count];
}method_info;



//Informação da classe
typedef struct classinfo{
    u1 tag;
    u2 name_index;
}CONSTANT_Class_info;

//Representa field
typedef struct fieldrefInfo{
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
}CONSTANT_FieldRef_info;

//Representa field ou método sem indicar de quem
typedef struct nameAndTypeInfo{
    u1 tag;
    u2 name_index;
    u2 descriptor_index;
}CONSTANT_NameAndType_info;

//Representa string utf8
typedef struct utf8Info{
    u1 tag;
    u2 length;
    u1 bytes[];//bytes[length];
}utf8_info;

//Representa médoto
typedef struct methodRefInfo{
    u1 tag;
    u2 class_index; // -> utf8_info
    u2 name_and_type_index; // -> nameAndType_info
}methodRef_info;

//Representa informação de um método
typedef struct interfaceMethodRefInfo{
    u1 tag;
    u2 class_index; //-> utf8_info
    u2 name_and_type_index; //->nameAndType_info
}interfaceMethodRef_info;

//Representa Strings constantes
typedef struct stringInfo{
    u1 tag;
    u2 string_index; //-> utf8_info
}string_info;

//Inteiro de 4 bytes (int32)
typedef struct integerInfo{
    u1 tag;
    u4 bytes;
}integer_info;

//Ponto flutuante (float)
typedef struct floatInfo{
    u1 tag;
    u4 bytes;
}float_info;

//Inteiro de 8 bytes (long 64)
typedef struct longInfo{
    u1 tag;
    u4 high_bytes;
    u4 low_bytes;
}long_info;

//Ponto flutuante (double 64)
typedef struct doubleInfo{
    u1 tag;
    u4 high_bytes;
    u4 low_bytes;
}double_info;

//Estrutura do .class
typedef struct javaClass{
    u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
    cp_info *constant_pool;//constant_pool[constant_pool-1];
    u2 access_flags;
    u2 this_class;
    u2 super_class;
    u2 interfaces_count;
    u2 *interfaces;//interfaces[interfaces_count];
    u2 fields_count;
    field_info *fields;//fields[fields_count];
    u2 methods_count;
    method_info *methods;//methods[methods_count];
    u2 attributes_count;
    attribute_info attributes[];//attributes[attributes_count];
} java_class;

/*
 Structs e funções para pilha
 */
//Estrutura de item para ser empilhado
typedef struct stackItem{
    void * stackedItem;
    struct stackItem * previousItem;
}StackItem;
//Estrutura de pilha
typedef struct stack{
    StackItem * topItem;
}Stack;

/*
 Cabeçalhos de métodos públicos
 */
void convertLittleBigEndianu2(u2 * tmp);
void convertLittleBigEndianu4(u4 * tmp);

#endif
