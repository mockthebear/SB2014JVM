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
#include <string.h>
#include "jclass.h"

/*
 Funções de leitura do .class
 */
//Le .class
java_class * readClassFile(char * fileAddress, java_class * jclass){
    //java_class * jclass = (java_class*)calloc(1, sizeof(java_class));
    FILE * fp = fopen(fileAddress, "rb");
    
    jclass->magic = readu4(fp);
    jclass->minor_version = readu2(fp);
    jclass->major_version = readu2(fp);
    
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
    readFields(jclass->fields, jclass->fields_count, fp);
    
    jclass->methods_count = readu2(fp);
    jclass->methods = (method_info*)calloc(jclass->methods_count, sizeof(method_info));
    readMethods(jclass->methods, jclass->methods_count, fp);
    
    jclass->attributes_count = readu2(fp);
    jclass->attributes = (attribute_info*)calloc(jclass->attributes_count, sizeof(attribute_info));
    readAttributes(jclass->attributes, jclass->attributes_count, fp);
    
    fclose(fp);
    return jclass;
}
//Leitura de métodos
void readMethods(method_info * methods, u2 num_methods, FILE * fp){
    u2 k = 0;
    for(int i=0;i<num_methods;i++,k=0){
        methods[i].access_flags = readu2(fp);
        methods[i].name_index = readu2(fp);
        methods[i].descriptor_index = readu2(fp);
        k = readu2(fp);
        methods[i].attributes_count = k;
        methods[i].attributes = (attribute_info*)calloc(k, sizeof(attribute_info));
        readAttributes(methods[i].attributes, k, fp);
    }
    return;
}
//Leitura de campos
void readAttributes(attribute_info * attributes, u2 num_attributes, FILE * fp){
    u4 k = 0;
    for(int i=0;i<num_attributes;i++,k=0){
        attributes[i].attribute_name_index = readu2(fp);
        k = readu4(fp);
        attributes[i].attribute_length = k;
        attributes[i].info = (u1*)calloc(k, sizeof(u1));
        for(int j=0;j<k;j++){
            attributes[i].info[j] = readu1(fp);
        }
    }
    return;
}
//Leitura de campos
void readFields(field_info * fields, u2 num_fields, FILE * fp){
    u2 k = 0;
    for(int i=0;i<num_fields;i++, k=0){
        fields[i].access_flags = readu2(fp);
        fields[i].name_index = readu2(fp);
        fields[i].descriptor_index = readu2(fp);
        k = readu2(fp);
        fields[i].attributes_count = k;
        *fields[i].attributes = *(attribute_info*)calloc(k, sizeof(attribute_info));
        readAttributes(fields[i].attributes, k, fp);
    }
    return;
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
                constantPool[i].utf8_.bytes = (u1*)calloc(k,sizeof(u1));
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

/*
 Funções de Impressão do conteúdo do .class
 */
//Impressão de cp_info (constantes)
char * printConstant(constantUnion *constant,int i){
    char * buffer = (char*)calloc(300,sizeof(char));
    char * temp1 = NULL;
    char * temp2 = NULL;
    int64_t tempLong=0;
    switch (constant[i].cpinfo.tag) {
        case CONSTANT_UTF8:
            sprintf(buffer, "%s", constant[i].utf8_.bytes);
            //free(buffer);
            //buffer = (char*)convertFromutf8(constant->utf8_.bytes, constant->utf8_.length);

            break;
        case CONSTANT_INTEGER:
            sprintf(buffer, "Integer: %"PRId32"\n",(int32_t)constant[i].integer_.bytes);
            break;
        case CONSTANT_FLOAT:
            sprintf(buffer, "Float: %.5f\n",(float)constant[i].float_.bytes);
            break;
        case CONSTANT_LONG:
            tempLong = (int64_t)(((uint64_t)constant[i].long_.high_bytes<<32)|constant[i].long_.low_bytes);
            sprintf(buffer, "Long: %"PRId64"\n",(int64_t)tempLong);
            break;
        case CONSTANT_DOUBLE:
            tempLong = constant[i].double_.high_bytes;
            tempLong = tempLong<<32;
            tempLong += constant[i].double_.low_bytes;
            sprintf(buffer, "Double: %lf\n", (double)tempLong);
            break;
        case CONSTANT_CLASS:
            sprintf(buffer, "Classe(%"PRIu16"): %s\n", constant[i].class_.name_index, temp1 = printConstant(constant,constant[i].class_.name_index));
            free(temp1);
            break;
        case CONSTANT_STRING:
            sprintf(buffer, "String(%"PRIu16") com conteudo: \"%s\"\n", constant[i].string_.string_index, temp1 = printConstant(constant, constant[i].string_.string_index));
            free(temp1);
            break;
        case CONSTANT_FIELDREF:
            sprintf(buffer, "Campo(%"PRIu16") \"%s\" da classe(%"PRIu16") \"%s\"\n", constant[i].fieldref_.name_and_type_index,  temp1 = printConstant(constant, constant[i].fieldref_.name_and_type_index),constant[i].fieldref_.class_index, temp2 = printConstant(constant, constant[i].fieldref_.class_index));
            free(temp1);
            free(temp2);
            break;
        case CONSTANT_METHODREF:
            sprintf(buffer, "Metodo(%"PRIu16") \"%s\" da classe(%"PRIu16") \"%s\"\n", constant[i].methodref_.name_and_type_index, temp1 = printConstant(constant, constant[i].methodref_.name_and_type_index), constant[i].methodref_.class_index, temp2 = printConstant(constant, constant[i].methodref_.class_index));
            free(temp1);
            break;
        case CONSTANT_INTERFACEMETHODREF:
            
            break;
        case CONSTANT_NAMEANDTYPE:
            sprintf(buffer, "nome \"%s\" e descritor \"%s\"", temp1 = printConstant(constant, constant[i].nametype_.name_index), temp2 = printConstant(constant, constant[i].nametype_.descriptor_index));
            free(temp1);
            free(temp2);
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
char * printAccessFlag(u2 flag){
    char * buffer = (char*)calloc(100, sizeof(char));
    strcat(buffer, "Flags: ");
    if(flag&ACCESS_FLAG_ABSTRACT){
        strcat(buffer, "abstract ");
    }
    if(flag&ACCESS_FLAG_FINAL){
        strcat(buffer, "final ");
    }
    if(flag&ACCESS_FLAG_PUBLIC){
        strcat(buffer, "public ");
    }
    if(flag&ACCESS_FLAG_SUPER){
        strcat(buffer, "super ");
    }
    if(flag&ACCESS_FLAG_INTERFACE){
        strcat(buffer, "interface ");
    }
    return buffer;
}
char * getTypeOfConst(u1 tag){
    switch(tag){
        case CONSTANT_UTF8:
            return "UTF-8";
        case CONSTANT_INTEGER:
            return "INTEGER";
        case CONSTANT_FLOAT:
            return "FLOAT";
        case CONSTANT_LONG:
            return "LONG";
        case CONSTANT_DOUBLE:
            return "DOUBLE";
        case CONSTANT_CLASS:
            return "CLASS";
        case CONSTANT_STRING:
            return "STRING";
        case CONSTANT_FIELDREF:
            return "FIELDREF";
        case CONSTANT_METHODREF:
            return "METHODREF";
        case CONSTANT_INTERFACEMETHODREF:
            return "INTERFACEMETHODREF";
        case CONSTANT_NAMEANDTYPE:
            return "NAME_AND_TYPE";
        case CONSTANT_METHODHANDLE:
            return "METHODHANDLE";
        case CONSTANT_METHODTYPE:
            return "METHODTYPE";
        case CONSTANT_INVOKEDYNAMIC:
            return "INVOKEDYNAMIC";
            break;
        default:
            break;
            
    }
    return "";
}
void printClassFileContent(java_class * jclass){
    int i=0;
    char * temp = NULL;
    
    //Ponteiros para reduzir comprimento das funções
    constantUnion * cpool = jclass->constant_pool;
    method_info * methods = jclass->methods;
    attribute_info * attributes = jclass->attributes;
    field_info * fields = jclass->fields;
    
    //Impressão do código mágico, versão e numero de constantes
    printf("Magic: %"PRIx32" \n", jclass->magic);
    printf("Version: %"PRIu16".%"PRIu16" \n", jclass->major_version, jclass->minor_version);
    printf("# of constants: %"PRIu16" \n", jclass->constant_pool_count);
    
    //Impressão do pool de constantes
    for(int i=1;i<jclass->constant_pool_count; i++){
        printf("\tConstant%d:Tipo %s: %s\n", i,getTypeOfConst(cpool[i].cpinfo.tag),temp = printConstant(cpool, i));
        free(temp);
    }
    
    //Impressão do flag de acesso, nome da classe e super classe
    printf("Access Flags: %"PRIu16" - %s\n", jclass->access_flags,temp = printAccessFlag(jclass->access_flags));
    free(temp);
    printf("This Class: %"PRIu16" - %s\n",jclass->this_class, temp = printConstant(cpool, jclass->this_class));
    free(temp);
    printf("Super Class: %"PRIu16" - %s\n",jclass->super_class, temp = printConstant(cpool, jclass->super_class));
    free(temp);
    
    //Impressão das interfaces
    printf("# of interfaces: %"PRIu16" \n", jclass->interfaces_count);
    for(i=0;i<jclass->interfaces_count;i++){
        printf("\tInterface%d: %s \n",i,temp = printConstant(cpool,i));
        free(temp);
    }
    
    //Impressão dos campos
    printf("# of fields: %"PRIu16" \n",jclass->fields_count);
    for(i=0;i<jclass->fields_count; i++){
        printf("\tField%d: (%"PRId16")%s %s %s\n",i, fields[i].descriptor_index, printConstant(cpool, fields[i].name_index),printConstant(cpool, fields[i].descriptor_index), printConstant(cpool, fields[i].access_flags));
    }
    
    //Impressão dos métodos
    printf("# of methods: %"PRIu16" \n",jclass->methods_count);
    for(i=0;i<jclass->methods_count;i++){
       // printf("\tMethod%d: %s %s %s %s \n", i, printConstant(cpool, methods[i].name_index, printConstant(cpool, methods[i].descriptor_index), printAccessFlag(methods[i].access_flags), printConstant(cpool, methods[i].attributes));
    }
    
    //Impressão dos atributos
    printf("# of attributes: %"PRIu16"\n", jclass->attributes_count);
    for(i=0;i<jclass->attributes_count; i++){
        printf("\tAttribute%d: %"PRId16" \n",i ,cpool[attributes[i].attribute_name_index].fieldref_.name_and_type_index);
    }
    
}
/*
 Funções para liberar memória alocada durante a leitura do .class
 */
void freeConstantPoolUTF8(constantUnion * cpool, u2 num_constants){
    for(int i=1; i<num_constants;i++){
        if(cpool[i].cpinfo.tag==CONSTANT_UTF8){
            free(cpool[i].utf8_.bytes);
        }
    }
    return;
}
void freeFieldsInfo(field_info * finfo, u2 num_fields){
    for(int i=0; i<num_fields;i++){
        freeAttributeInfo(&(finfo[i].attributes[0]),finfo[i].attributes_count);
    }
    return;
}
void freeAttributeInfo(attribute_info * attinfo, u2 num_att){
    for(int i=0; i<num_att;i++){
        free(&attinfo[i].info[0]);
    }
    return;
}
void freeMethodsInfo(method_info * methinfo, u2 num_meth){
    for(int i=0; i<num_meth;i++){
        freeAttributeInfo(methinfo[i].attributes, methinfo[i].attributes_count);
    }
    return;
}

//Desaloca estruturas alocadas da classe durante a leitura dos dados do arquivo
void freeJClass(java_class *jclass){
    freeConstantPoolUTF8(jclass->constant_pool,jclass->constant_pool_count);
    free(jclass->constant_pool);
    free(jclass->interfaces);
    freeFieldsInfo(jclass->fields, jclass->fields_count);
    free(jclass->fields);
    freeAttributeInfo(jclass->attributes, jclass->attributes_count);
    free(jclass->attributes);
    freeMethodsInfo(jclass->methods, jclass->methods_count);
    free(jclass->methods);
}

/*
 Programa principal
 */
int main(int argc, char** argv) {

    java_class jclass;
    
    //Lê arquivo .class para memória
    jclass = *readClassFile("/Users/gabriel/Desktop/jvm/jvm/HelloWorld.class", &jclass);

    //Impressão dos dados do arquivo .class
    printClassFileContent(&jclass);
    
    //Libera .class da memória
    freeJClass(&jclass);
    return 0;
}

