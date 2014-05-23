/*
 *
 * Created on May 6, 2014, 4:59 PM
 */
/*
 Includes
 */
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "jclass.h"


#define  UNIX                // WIN para Windows e UNIX para Unix


//Le .class
java_class * readClassFile(char * fileAddress){
    java_class * jclass = (java_class*)calloc(1, sizeof(java_class));
    FILE * fp = fopen(fileAddress, "rb");
    
    jclass->magic = readu4(fp);
    jclass->minor_version = readu1(fp);
    jclass->major_version = readu1(fp);
    
    jclass->constant_pool_count = readu2(fp);

    jclass->constant_pool = (constantUnion*)calloc(jclass->constant_pool_count+1, sizeof(constantUnion));
    readConstantPool(jclass->constant_pool,jclass->constant_pool_count, fp);
    
    jclass->access_flags = readu2(fp);
    jclass->this_class = readu2(fp);
    jclass->super_class = readu2(fp);
    
    jclass->interfaces_count = readu2(fp);
    
    jclass->interfaces = (u2*)calloc(jclass->interfaces_count, sizeof(u2));
    for(int i=0;i<jclass->interfaces_count;i++){
        jclass->interfaces[i] = readu2(fp);
    }
    
    jclass->fields_count = readu2(fp);
    
    jclass->fields = (field_info*)calloc(jclass->fields_count, sizeof(field_info));
    fread(jclass->fields, jclass->fields_count, sizeof(field_info), fp);
    for(int i=0;i<jclass->fields_count;i++){
        
    }
    
    jclass->methods_count = readu2(fp);
    
    jclass->methods = (method_info*)calloc(jclass->methods_count, sizeof(method_info));
    fread(jclass->methods, jclass->methods_count, sizeof(method_info), fp);
    for(int i=0;i<jclass->methods_count;i++){
        
    }
    
    jclass->attributes_count = readu2(fp);
    
    fread(jclass->attributes, jclass->attributes_count, sizeof(attribute_info), fp);
    for(int i=0;i<jclass->attributes_count;i++){
        
    }
    
    fclose(fp);
    return jclass;
}
//Leitura do constant pool
void readConstantPool(constantUnion * constantPool, u2 num_constants, FILE * fp){
    u2 k =0;
    for (int i=1; i < num_constants ; i++) {
		constantPool[i].cpinfo.tag = readu1(fp);
		switch (constantPool[i].cpinfo.tag) {
            case CONSTANT_UTF8:
                k = readu2(fp);
			    constantPool[i].utf8_.length = k;
                *constantPool[i].utf8_.bytes = *(u1*)calloc(k,sizeof(u1));
                for(int j=0;j<k;j++){
                    constantPool[i].utf8_.bytes[j] = readu1(fp);
                }
			    break;
            case CONSTANT_INTEGER:
			    constantPool[i].integer_.bytes = readu4(fp);
			    break;
            case CONSTANT_FLOAT:
			    constantPool[i].float_.bytes = readu4(fp);
			    break;
            case CONSTANT_LONG:
			    constantPool[i].long_.high_bytes = readu4(fp);
                constantPool[i].long_.low_bytes = readu4(fp);
			    break;
            case CONSTANT_DOUBLE:
			    constantPool[i].double_.high_bytes = readu4(fp);
                constantPool[i].double_.low_bytes = readu4(fp);
			    break;
            case CONSTANT_CLASS:
			    constantPool[i].class_.name_index = readu2(fp);
			    break;
            case CONSTANT_STRING:
                constantPool[i].string_.string_index = readu2(fp);
                break;
            case CONSTANT_FIELDREF:
			    constantPool[i].fieldref_.class_index = readu2(fp);
			    constantPool[i].fieldref_.name_and_type_index = readu2(fp);
			    break;
            case CONSTANT_METHODREF:
                constantPool[i].methodref_.class_index = readu2(fp);
                constantPool[i].methodref_.name_and_type_index = readu2(fp);
                break;
            case CONSTANT_INTERFACEMETHODREF:
                constantPool[i].interfaceref_.class_index = readu2(fp);
                constantPool[i].interfaceref_.name_and_type_index = readu2(fp);
                break;
            case CONSTANT_NAMEANDTYPE:
                constantPool[i].nametype_.name_index = readu2(fp);
                constantPool[i].nametype_.descriptor_index = readu2(fp);
                break;
            case CONSTANT_METHODHANDLE:
                constantPool[i].methodhandle_.reference_kind = readu1(fp);
                constantPool[i].methodhandle_.reference_index = readu2(fp);
                break;
            case CONSTANT_METHODTYPE:
                constantPool[i].methodtype_.descriptor_index = readu2(fp);
                break;
            case CONSTANT_INVOKEDYNAMIC:
                constantPool[i].invokedynamic_.bootstrap_method_attr_index = readu2(fp);
                constantPool[i].invokedynamic_.name_and_type_index = readu2(fp);
                break;
            default:
                break;
        }
    }
}

//Impressão de cp_info (constantes)
char * printConstant(constantUnion *constant){
    char * buffer = (char*)calloc(100,sizeof(char));
    uint64_t tempLong;
    switch (constant->cpinfo.tag) {
        case CONSTANT_UTF8:
            buffer = convertToutf8(constant->utf8_.bytes);
            break;
        case CONSTANT_INTEGER:
            sprintf(buffer, "%"PRId32"\n",(int32_t)constant->integer_.bytes);
            break;
        case CONSTANT_FLOAT:
            sprintf(buffer, "%f\n",(float)constant->float_.bytes);
            break;
        case CONSTANT_LONG:
            tempLong = constant->long_.high_bytes;
            tempLong = tempLong<<32;
            tempLong += constant->long_.low_bytes;
            sprintf(buffer, "%"PRId64"\n",(int64_t)tempLong);
            break;
        case CONSTANT_DOUBLE:
            tempLong = constant->double_.high_bytes;
            tempLong = tempLong<<32;
            tempLong += constant->double_.low_bytes;
            sprintf(buffer, "%lf\n", (double)tempLong);
            break;
        case CONSTANT_CLASS:
            sprintf(buffer, "%"PRIu16"\n", constant->class_.name_index);
            break;
        case CONSTANT_STRING:
            sprintf(buffer, "%"PRIu16"\n", constant->string_.string_index);
            break;
        case CONSTANT_FIELDREF:
            sprintf(buffer, "%"PRIu16" %"PRIu16"\n",constant->fieldref_.class_index, constant->fieldref_.name_and_type_index);
            break;
        case CONSTANT_METHODREF:
            
            break;
        case CONSTANT_INTERFACEMETHODREF:
            
            break;
        case CONSTANT_NAMEANDTYPE:
            
            break;
        case CONSTANT_METHODHANDLE:
            
            break;
        case CONSTANT_METHODTYPE:
            
            break;
        case CONSTANT_INVOKEDYNAMIC:
            
            break;
        default:
            break;
    }
    return buffer;
}
//Impressão de interfaces
/*char * printInterface(u2 interface){
    char * buffer = (char*)calloc(100,sizeof(char));
    sprintf("Tag:%"PRIu8" Indice da Classe:%"PRIu16" Indice Nome e Tipo:%"PRIu16"\n", interface.tag,interface.class_index, interface.name_and_type_index);
    return buffer;
}*/
//Impressão de campos
char * printField(field_info *field){
    char * buffer = (char*)calloc(100,sizeof(char));
    sprintf("Tag:%"PRIu16" Indice da Classe:%"PRIu16" Indice Nome e Tipo:%"PRIu16"\n", field->access_flags, field->attributes_count, field->descriptor_index);
    return buffer;
}
void printClassFileContent(java_class * jclass){
    int i=0;
    printf("Magic: %X \n", jclass->magic);
    printf("Version: %X.%X \n", jclass->major_version, jclass->minor_version);
    printf("# of constants: %u \n", jclass->constant_pool_count);
    for(int i=1;i<jclass->constant_pool_count; i++){
        char * temp = NULL;
        printf("\tConstant%d: %s\n", i,temp = printConstant(&jclass->constant_pool[i]));
        free(temp);
    }
    printf("Access Flags: %u \n", jclass->access_flags);
    printf("This Class: %"PRIu16" \n",jclass->this_class);
    printf("Super Class: %"PRIu16" \n",jclass->super_class);
    
    printf("# of interfaces: %u \n", jclass->interfaces_count);
    for(i=0;i<jclass->interfaces_count;i++){
        char * temp = NULL;
        printf("\tInterface%u: %s \n",i,temp = printConstant(&jclass->constant_pool[jclass->interfaces[i]]));
        free(temp);
    }
    printf("# of fields: %u \n",jclass->fields_count);
    for(i=0;i<jclass->fields_count; i++){
        char *temp = NULL;
        printf("\tField%d: %d \n",i, jclass->constant_pool[jclass->fields[i].descriptor_index].fieldref_.name_and_type_index);
        free(temp);
    }
    
    printf("# of methods: %u \n",jclass->methods_count);
    for(i=0;i<jclass->methods_count;i++){
        printf("\tMethod%d: %d \n", i, jclass->constant_pool[jclass->methods[i].descriptor_index].nametype_.name_index);
    }
    
    printf("# of attributes: %u\n", jclass->attributes_count);
    for(i=0;i<jclass->attributes_count; i++){
        printf("\tAttribute%d: %d \n",i ,jclass->constant_pool[jclass->attributes[i].attribute_name_index].fieldref_.name_and_type_index);
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
/*int is_big_endian(void)
{
    union {
        uint32_t i;
        char c[4];
    } e = { 0x01000000 };
    
    return e.c[0];
}*/
int main(int argc, char** argv) {
    //printf("System is %s-endian.\n", is_big_endian() ? "big" : "little");
    java_class * jclass;
    #ifdef WIN
    jclass = readClassFile("\\Users\-----\\Desktop\jvm\jvm\\HelloWorld.class");
    #endif
    #ifdef UNIX
    jclass = readClassFile("/Users/gabriel/Desktop/jvm/jvm/HelloWorld.class");
    #endif
    
    printClassFileContent(jclass);
    freeJClass(jclass);
    return 0;
}

