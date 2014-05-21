/*
 * File:   main.c
 * Author: gabriel
 *
 * Created on May 6, 2014, 4:59 PM
 */
/*
 Macros
 */
#define VALID_MAGIC_SIGNATURE 0xCAFEBABE
#define LSBY_MASK(x)  (x&0x000000FF)
#define MLSBY_MASK(x) (x&0x0000FF00)
#define MHSBY_MASK(x) (x&0x00FF0000)
#define HSBY_MASK(x)  (x&0xFF000000)

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
 Includes
 */
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
/*
 Typedefs JVM
 */
//Tipos JVM
typedef uint8_t  u1;
typedef uint16_t u2;
typedef uint32_t u4;
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
}class_info;
//Representa field
typedef struct fieldrefInfo{
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
}fieldRef_info;
//Representa field ou método sem indicar de quem
typedef struct nameAndTypeInfo{
    u1 tag;
    u2 name_index;
    u2 descriptor_index;
}nameAndType_info;
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

//Empilha dado
void push(StackItem * pushedItem, Stack * operationalStack){
    pushedItem->previousItem = operationalStack->topItem;
    operationalStack->topItem = pushedItem;
}

//Desempilha dado
StackItem * pop(Stack * operationalStack){
    StackItem *temp = operationalStack->topItem;
    operationalStack->topItem = temp->previousItem;
    temp->previousItem = NULL;
    return temp;
}
void littleToBigEndianu2(u2 * tmp){
    u2 final = LSBY_MASK(*tmp)<<8 | MLSBY_MASK(*tmp)>>8;
    *tmp = final;
}
void littleToBigEndianu4(u4 * tmp){
    u4 final = LSBY_MASK(*tmp)<<24 | MLSBY_MASK(*tmp)<<8 | MHSBY_MASK(*tmp)>>8 | HSBY_MASK(*tmp)>>24;
    *tmp = final;
}
//Le .class
java_class * readClassFile(char * fileAddress){
    java_class * jclass = (java_class*)calloc(1, sizeof(java_class));
    FILE * fp = fopen(fileAddress, "rb");
    
    fread(&jclass->magic,1, sizeof(u4), fp);
    littleToBigEndianu4(&jclass->magic);
    
    fread(&jclass->minor_version, 1, sizeof(u2), fp);
    fread(&jclass->major_version, 1, sizeof(u2), fp);
    littleToBigEndianu2(&jclass->major_version);
    littleToBigEndianu2(&jclass->minor_version);
    
    fread(&jclass->constant_pool_count, 1, sizeof(u2), fp);
    littleToBigEndianu2(&jclass->constant_pool_count);

    jclass->constant_pool = (cp_info*)calloc(jclass->constant_pool_count+1, sizeof(cp_info));
    fread(&jclass->constant_pool[1], jclass->constant_pool_count,sizeof(cp_info), fp);
    
    fread(&jclass->access_flags, 1, sizeof(u2), fp);
    fread(&jclass->this_class, 1, sizeof(u2), fp);
    fread(&jclass->super_class, 1, sizeof(u2), fp);
    littleToBigEndianu2(&jclass->access_flags);
    littleToBigEndianu2(&jclass->this_class);
    littleToBigEndianu2(&jclass->super_class);
    
    fread(&jclass->interfaces_count,1, sizeof(u2), fp);
    jclass->interfaces = (u2*)calloc(jclass->interfaces_count, sizeof(u2));
    fread(jclass->interfaces, jclass->interfaces_count, sizeof(u2), fp);
    
    fread(&jclass->fields_count, 1, sizeof(u2), fp);
    jclass->fields = (field_info*)calloc(jclass->fields_count, sizeof(field_info));
    fread(jclass->fields, jclass->fields_count, sizeof(field_info), fp);
    
    fread(&jclass->methods_count, 1, sizeof(u2), fp);
    jclass->methods = (method_info*)calloc(jclass->methods_count, sizeof(method_info));
    fread(jclass->methods, jclass->methods_count, sizeof(method_info), fp);
    
    fread(&jclass->attributes_count, 1, sizeof(u2), fp);
    fread(jclass->attributes, jclass->attributes_count, sizeof(attribute_info), fp);
    
    fclose(fp);
    return jclass;
}

/*void writeClassFile(char * fileAddress, java_class * jclass){
    FILE * fp = fopen(fileAddress, "wb");
    
    fwrite(&jclass->magic,4, sizeof(u1), fp);
    fwrite(&jclass->minor_version, 1, sizeof(u2), fp);
    fwrite(&jclass->major_version, 1, sizeof(u2), fp);
    fwrite(&jclass->constant_pool_count, 1, sizeof(u2), fp);
    fwrite(jclass->constant_pool, jclass->constant_pool_count,sizeof(cp_info), fp);
    fwrite(&jclass->access_flags, 1, sizeof(u2), fp);
    fwrite(&jclass->this_class, 1, sizeof(u2), fp);
    fwrite(&jclass->super_class, 1, sizeof(u2), fp);
    fwrite(&jclass->interfaces_count,1, sizeof(u2), fp);
    fwrite(jclass->interfaces, jclass->interfaces_count, sizeof(u2), fp);
    fwrite(&jclass->fields_count, 1, sizeof(u2), fp);
    fwrite(jclass->fields, jclass->fields_count, sizeof(field_info), fp);
    fwrite(&jclass->methods_count, 1, sizeof(u2), fp);
    fwrite(jclass->methods, jclass->methods_count, sizeof(method_info), fp);
    fwrite(&jclass->attributes_count, 1, sizeof(u2), fp);
    fwrite(jclass->attributes, jclass->attributes_count, sizeof(attribute_info), fp);
    
    fclose(fp);
}*/

//Impressão de cp_info (constantes)
char * printConstant(cp_info constant){
    char * buffer = (char*)calloc(100,sizeof(char));
    sprintf("Tag:%"PRIu8" Info:%s \n", constant.tag, constant.info);
    return buffer;
}
//Impressão de interfaces
/*char * printInterface(u2 interface){
    char * buffer = (char*)calloc(100,sizeof(char));
    sprintf("Tag:%"PRIu8" Indice da Classe:%"PRIu16" Indice Nome e Tipo:%"PRIu16"\n", interface.tag,interface.class_index, interface.name_and_type_index);
    return buffer;
}*/
//Impressão de campos
char * printField(fieldRef_info field){
    char * buffer = (char*)calloc(100,sizeof(char));
    sprintf("Tag:%"PRIu8" Indice da Classe:%"PRIu16" Indice Nome e Tipo:%"PRIu16"\n", field.tag, field.class_index, field.name_and_type_index);
    return buffer;
}
void printClassFileContent(java_class * jclass){
    int i=0;
    printf("Magic: %X \n", jclass->magic);
    printf("Version: %X.%X \n", jclass->major_version, jclass->minor_version);
    printf("# of constants: %u \n", jclass->constant_pool_count);
    for(int i=1;i<jclass->constant_pool_count; i++){
        char * temp = NULL;
        printf("\tConstant%d: %s\n", i,temp = printConstant(jclass->constant_pool[i]));
        free(temp);
    }
    printf("Access Flags: %u \n", jclass->access_flags);
    printf("This Class: %"PRIu16" \n",jclass->this_class);
    printf("Super Class: %"PRIu16" \n",jclass->super_class);
    
    printf("# of interfaces: %u \n", jclass->interfaces_count);
    for(i=0;i<jclass->interfaces_count;i++){
        char * temp = NULL;
        printf("\tInterface%u: %s \n",i,temp = printConstant(jclass->constant_pool[jclass->interfaces[i]]));
        free(temp);
    }
    printf("# of fields: %u \n",jclass->fields_count);
    for(i=0;i<jclass->fields_count; i++){
        char *temp = NULL;
        printf("\tField%d: %s \n",i, jclass->constant_pool[jclass->fields[i].descriptor_index].info);
        free(temp);
    }
    
    printf("# of methods: %u \n",jclass->methods_count);
    for(i=0;i<jclass->methods_count;i++){
        printf("\tMethod%d: %s \n", i, jclass->constant_pool[jclass->methods[i].descriptor_index].info);
    }
    
    printf("# of attributes: %u\n", jclass->attributes_count);
    for(i=0;i<jclass->attributes_count; i++){
        printf("\tAttribute%d: %s \n",i ,jclass->constant_pool[jclass->attributes[i].attribute_name_index].info);
    }
    
}
void freeJClass(java_class *jclass){
    free(jclass->constant_pool);
    free(jclass->interfaces);
    free(jclass->fields);
    free(jclass->methods);
    free(jclass);
}
//JVM
/*
 *
 */
int main(int argc, char** argv) {
    java_class * jclass;
    jclass = readClassFile("/Users/gabriel/Desktop/HelloWorld.class");
    printClassFileContent(jclass);
    freeJClass(jclass);
    return 0;
}

