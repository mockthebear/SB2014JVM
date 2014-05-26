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
#define ACCESS_FLAG_PUBLIC    0x0001
#define ACCESS_FLAG_PRIVATE   0x0002
#define ACCESS_FLAG_PROTECTED 0x0004
#define ACCESS_FLAG_STATIC    0x0008
#define ACCESS_FLAG_FINAL     0x0010
#define ACCESS_FLAG_SUPER     0x0020
#define ACCESS_FLAG_BRIDGE    0x0040
#define ACCESS_FLAG_VARARGS   0x0080
#define ACCESS_FLAG_NATUVE    0x0100
#define ACCESS_FLAG_INTERFACE 0x0200
#define ACCESS_FLAG_ABSTRACT  0x0400
#define ACCESS_FLAG_STRICT    0x0800
#define ACCESS_FLAG_SYNTHETIC 0x1000
#define ACCESS_FLAG_ENUM      0x4000

//Tags de tipos constante
#define CONSTANT_UTF8                0x01
#define CONSTANT_INTEGER             0x03
#define CONSTANT_FLOAT               0x04
#define CONSTANT_LONG                0x05
#define CONSTANT_DOUBLE              0x06
#define CONSTANT_CLASS               0x07
#define CONSTANT_STRING              0x08
#define CONSTANT_FIELDREF            0x09
#define CONSTANT_METHODREF           0x0A
#define CONSTANT_INTERFACEMETHODREF  0x0B
#define CONSTANT_NAMEANDTYPE         0x0C
#define CONSTANT_METHODHANDLE        0x0F
#define CONSTANT_METHODTYPE          0x10
#define CONSTANT_INVOKEDYNAMIC       0x12


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
}Class_info;

//Representa field
typedef struct fieldrefInfo{
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
}FieldRef_info;

//Representa field ou método sem indicar de quem
typedef struct nameAndTypeInfo{
    u1 tag;
    u2 name_index;
    u2 descriptor_index;
}NameAndType_info;

//Representa string utf8
typedef struct utf8Info{
    u1 tag;
    u2 length;
    u1 bytes[];//bytes[length];
}Utf8_info;

//Representa médoto
typedef struct methodRefInfo{
    u1 tag;
    u2 class_index; // -> utf8_info
    u2 name_and_type_index; // -> nameAndType_info
}MethodRef_info;

//Representa informação de um método
typedef struct interfaceMethodRefInfo{
    u1 tag;
    u2 class_index; //-> utf8_info
    u2 name_and_type_index; //->nameAndType_info
}InterfaceMethodRef_info;

//Representa Strings constantes
typedef struct stringInfo{
    u1 tag;
    u2 string_index; //-> utf8_info
}String_info;

//Inteiro de 4 bytes (int32)
typedef struct integerInfo{
    u1 tag;
    u4 bytes;
}Integer_info;

//Ponto flutuante (float)
typedef struct floatInfo{
    u1 tag;
    u4 bytes;
}Float_info;

//Inteiro de 8 bytes (long 64)
typedef struct longInfo{
    u1 tag;
    u4 high_bytes;
    u4 low_bytes;
}Long_info;

//Ponto flutuante (double 64)
typedef struct doubleInfo{
    u1 tag;
    u4 high_bytes;
    u4 low_bytes;
}Double_info;

//Handle de método
typedef struct methodHandle{
    u1 tag;
    u1 reference_kind;
    u2 reference_index;
}MethodHandle;

//Tipo de método
typedef struct methodType{
    u1 tag;
    u2 descriptor_index;
}MethodType;

//Invocação dinâmica
typedef struct invokeDynamic{
    u1 tag;
    u2 bootstrap_method_attr_index;
    u2 name_and_type_index;
}InvokeDynamic;

typedef struct constant_union{
    union{
        cp_info cpinfo;
        Utf8_info utf8_;
        Integer_info integer_;
        Float_info float_;
        Long_info long_;
        Double_info double_;
        Class_info class_;
        String_info string_;
        FieldRef_info fieldref_;
        MethodRef_info methodref_;
        InterfaceMethodRef_info interfaceref_;
        NameAndType_info nametype_;
        MethodHandle methodhandle_;
        MethodType methodtype_;
        InvokeDynamic invokedynamic_;
    };
}constantUnion;

//Estrutura do .class
typedef struct javaClass{
    u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
    constantUnion *constant_pool;//constant_pool[constant_pool-1];
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


//Funções
void readConstantPool(constantUnion * constantPool, u2 num_constants, FILE * fp);
#endif
