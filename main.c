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
    
    fread(&jclass->magic,1, sizeof(u4), fp);
    //convertLittleBigEndianu4(&jclass->magic);
    U4_CONVERTION(jclass->magic);
    
    fread(&jclass->minor_version, 1, sizeof(u2), fp);
    fread(&jclass->major_version, 1, sizeof(u2), fp);
    convertLittleBigEndianu2(&jclass->major_version);
    convertLittleBigEndianu2(&jclass->minor_version);
    
    fread(&jclass->constant_pool_count, 1, sizeof(u2), fp);
    convertLittleBigEndianu2(&jclass->constant_pool_count);

    jclass->constant_pool = (cp_info*)calloc(jclass->constant_pool_count+1, sizeof(cp_info));
    fread(&jclass->constant_pool[1], jclass->constant_pool_count,sizeof(cp_info), fp);
    
    fread(&jclass->access_flags, 1, sizeof(u2), fp);
    fread(&jclass->this_class, 1, sizeof(u2), fp);
    fread(&jclass->super_class, 1, sizeof(u2), fp);
    convertLittleBigEndianu2(&jclass->access_flags);
    convertLittleBigEndianu2(&jclass->this_class);
    convertLittleBigEndianu2(&jclass->super_class);
    
    fread(&jclass->interfaces_count,1, sizeof(u2), fp);
    convertLittleBigEndianu2(&jclass->interfaces_count);
    
    jclass->interfaces = (u2*)calloc(jclass->interfaces_count, sizeof(u2));
    fread(jclass->interfaces, jclass->interfaces_count, sizeof(u2), fp);
    for(int i=0;i<jclass->interfaces_count;i++){
        convertLittleBigEndianu2(&jclass->interfaces[i]);
    }
    
    fread(&jclass->fields_count, 1, sizeof(u2), fp);
    convertLittleBigEndianu2(&jclass->fields_count);
    
    jclass->fields = (field_info*)calloc(jclass->fields_count, sizeof(field_info));
    fread(jclass->fields, jclass->fields_count, sizeof(field_info), fp);
    for(int i=0;i<jclass->fields_count;i++){
        
    }
    
    fread(&jclass->methods_count, 1, sizeof(u2), fp);
    convertLittleBigEndianu2(&jclass->methods_count);
    
    jclass->methods = (method_info*)calloc(jclass->methods_count, sizeof(method_info));
    fread(jclass->methods, jclass->methods_count, sizeof(method_info), fp);
    for(int i=0;i<jclass->methods_count;i++){
        
    }
    
    fread(&jclass->attributes_count, 1, sizeof(u2), fp);
    convertLittleBigEndianu2(&jclass->attributes_count);
    
    fread(jclass->attributes, jclass->attributes_count, sizeof(attribute_info), fp);
    for(int i=0;i<jclass->attributes_count;i++){
        
    }
    
    fclose(fp);
    return jclass;
}

//Impressão de cp_info (constantes)
char * printConstant(cp_info constant){
    char * buffer = (char*)calloc(100,sizeof(char));
    sprintf("Tag:%"PRIu8" Info:%s \n", &constant.tag, constant.info);
    return buffer;
}
//Impressão de interfaces
/*char * printInterface(u2 interface){
    char * buffer = (char*)calloc(100,sizeof(char));
    sprintf("Tag:%"PRIu8" Indice da Classe:%"PRIu16" Indice Nome e Tipo:%"PRIu16"\n", interface.tag,interface.class_index, interface.name_and_type_index);
    return buffer;
}*/
//Impressão de campos
char * printField(field_info field){
    char * buffer = (char*)calloc(100,sizeof(char));
    sprintf("Tag:%"PRIu16" Indice da Classe:%"PRIu16" Indice Nome e Tipo:%"PRIu16"\n", field.access_flags, field.attributes_count, field.descriptor_index);
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
    jclass = readClassFile("/Users/--------/Desktop/jvm/jvm/HelloWorld.class");
    #endif
    
    printClassFileContent(jclass);
    freeJClass(jclass);
    return 0;
}

