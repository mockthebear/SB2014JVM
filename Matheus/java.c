#include "java.h"
#include "filereader.h"
#include "data_control.h"

char Strings_[30][50] = {
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
    "11",
    "NameAndType",
    "13",
    "14",

    };
char Flags[30][50] = {
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

    };

Java *JAVA_createJava(FileHandler *f){
    Java *j = calloc(1,sizeof(Java));

    j->magic                        = DATAC_BigendianConv(f,4);

    ASSERT(j->magic == 0xcafebabe,"Cafebabe not found!!!");
    j->minor                        = DATAC_BigendianConv(f,2);
    j->major                        = DATAC_BigendianConv(f,2);
    j->constant_pull_count          = DATAC_BigendianConv(f,2);
    j->constant_pool = calloc(j->constant_pull_count,sizeof(contstant_method*));
    ASSERT(j->constant_pool,"Cannot allocate constant_pool");
    JAVA_parseConstantPool(f,j);
    j->access_flags                  = DATAC_BigendianConv(f,2);
    j->this_class                    = DATAC_BigendianConv(f,2);
    j->super_class                   = DATAC_BigendianConv(f,2);
    j->interfaces_count              = DATAC_BigendianConv(f,2);
    j->fields_count                  = DATAC_BigendianConv(f,2);
    j->methods_count                 = DATAC_BigendianConv(f,2);
    j->methods                       = calloc(j->methods_count,sizeof(Method*));
    ASSERT(j->methods,"Cannot allocate j->methods");
    JAVA_parseMethods(f,j);
    j->attributes_count              = DATAC_BigendianConv(f,2);
    j->FAttr                         = calloc(j->attributes_count,sizeof(FileAttr*));
    ASSERT(j->FAttr,"Cannot allocate j->FAttr");
    JAVA_parseFileAttributes(f,j);
    return j;
}

const unsigned char* JAVA_GetUTF8(Java *j,int i){
    if (i > 0 && i < j->constant_pull_count){
        contstant_method *t = j->constant_pool[i-1];
        if (t->tag == 1){
            return (const unsigned char*)t->bytes;
        }else{
            return "???";
        }

    }
    return "???2";
}



int JAVA_parseFileAttributes(FileHandler *f,Java *j){
    for (int i=0;i<j->attributes_count;i++){
        j->FAttr[i]                         =   calloc(1,sizeof(FileAttr));
        ASSERT(j->FAttr[i],"Cannot allocate j->FAttr[i]");
        j->FAttr[i]->attribute_name_index   =   DATAC_BigendianConv(f,2);
        j->FAttr[i]->attribute_lenght       =   DATAC_BigendianConv(f,4);
        j->FAttr[i]->sourcefile_index       =   DATAC_BigendianConv(f,2);
    }
}
int JAVA_parseMethods(FileHandler *f,Java *j){
    for (int i=0;i<j->methods_count ;i++){
        j->methods[i] = calloc(1,sizeof(Method));
        ASSERT(j->methods[i],"Cannot allocate j->methods[i]");
        j->methods[i]->acess_flags      = DATAC_BigendianConv(f,2);
        j->methods[i]->name_index       = DATAC_BigendianConv(f,2);
        j->methods[i]->descriptor_index = DATAC_BigendianConv(f,2);
        j->methods[i]->attributes_count = DATAC_BigendianConv(f,2);

        //Attributtes

        j->methods[i]->Attributes       = calloc(j->methods[i]->attributes_count,sizeof(Attribute*));
        ASSERT(j->methods[i]->Attributes,"Cannot allocate j->methods[i]->Attributes");

        //Load Attr

        for (int k=0;k<j->methods[i]->attributes_count;k++){

            j->methods[i]->Attributes[k]=calloc(1,sizeof(Attribute));
            ASSERT(j->methods[i]->Attributes[k],"Cannot allocate j->methods[i]->Attributes[k]");
            j->methods[i]->Attributes[k]->attribute_name_index          =   DATAC_BigendianConv(f,2);
            j->methods[i]->Attributes[k]->attribute_lenght              =   DATAC_BigendianConv(f,4);//32
            j->methods[i]->Attributes[k]->max_stack                     =   DATAC_BigendianConv(f,2);
            j->methods[i]->Attributes[k]->max_locals                    =   DATAC_BigendianConv(f,2);
            j->methods[i]->Attributes[k]->code_lenght                   =   DATAC_BigendianConv(f,4);//32
            j->methods[i]->Attributes[k]->code                          =   calloc(j->methods[i]->Attributes[k]->code_lenght+1,sizeof(char));
            ASSERT(j->methods[i]->Attributes[k]->code,"Cannot allocate j->methods[i]->Attributes[k]->code");
            //printf("Code for attr %d ",k+1);
            for (int r=0;r<j->methods[i]->Attributes[k]->code_lenght;r++){
                j->methods[i]->Attributes[k]->code[r]                   =   FileHandler_Read(f);
                //printf("%X ",j->methods[i]->Attributes[k]->code[r]);

            }
            //printf("\n");
            j->methods[i]->Attributes[k]->code[j->methods[i]->Attributes[k]->code_lenght]  = '\0';
            j->methods[i]->Attributes[k]->exception_table_lenght        =   DATAC_BigendianConv(f,2);
            j->methods[i]->Attributes[k]->attributes_count              =   DATAC_BigendianConv(f,2);
            //Attr of attr
            //C*****O CHEGA DE ATTR -.-
            j->methods[i]->Attributes[k]->Attrs                         =   calloc(j->methods[i]->Attributes[k]->attributes_count,sizeof(AttrOfAttr*));
            ASSERT(j->methods[i]->Attributes[k]->Attrs,"Cannot allocate j->methods[i]->Attributes[k]->Attrs");

            for (int g=0;g<j->methods[i]->Attributes[k]->attributes_count;g++){
                j->methods[i]->Attributes[k]->Attrs[g] = calloc(1,sizeof(AttrOfAttr));
                ASSERT(j->methods[i]->Attributes[k]->Attrs[g],"Cannot allocate j->methods[i]->Attributes[k]->Attrs[g]");

                AttrOfAttr *aux = j->methods[i]->Attributes[k]->Attrs[g];
                //Ok
                aux->attribute_name_index                               =   DATAC_BigendianConv(f,2);
                aux->attribute_lenght                                   =   DATAC_BigendianConv(f,4);
                aux->line_number_table_lenght                           =   DATAC_BigendianConv(f,2);

                //VÉI. CHEGA =/
                aux->LNTs                                               = calloc(aux->line_number_table_lenght,sizeof(LNT*));
                ASSERT(j->methods[i]->Attributes[k]->Attrs[g]->LNTs,"Cannot allocate j->methods[i]->Attributes[k]->Attrs[g]->LNTs");
                for (int t=0;t<aux->line_number_table_lenght;t++){
                    aux->LNTs[t]                =   calloc(1,sizeof(LNT));
                    ASSERT(j->methods[i]->Attributes[k]->Attrs[g]->LNTs[t],"Cannot allocate j->methods[i]->Attributes[k]->Attrs[g]->LNTs[t]");

                    aux->LNTs[t]->start_pc      =   DATAC_BigendianConv(f,2);
                    aux->LNTs[t]->line_number   =   DATAC_BigendianConv(f,2);
                }
            }
        }
    }

}


int JAVA_parseConstantPool(FileHandler *f,Java *j){
    for (int i=0;i<j->constant_pull_count-1;i++){
        j->constant_pool[i] = calloc(1,sizeof(contstant_method));
        ASSERT(j->constant_pool[i],"Cannot allocate j->constant_pool[i]");
        j->constant_pool[i]->tag = DATAC_BigendianConv(f,1);
        j->constant_pool[i]->name = Strings_[j->constant_pool[i]->tag];
        j->constant_pool[i]->lengh = 0;
        //printf("%s [%d]",j->constant_pool[i]->name,j->constant_pool[i]->tag);

        switch( j->constant_pool[i]->tag){
            case 1:{
                //UTF8
                j->constant_pool[i]->lengh                    = DATAC_BigendianConv(f,2);
                j->constant_pool[i]->bytes                    = calloc(j->constant_pool[i]->lengh+1,sizeof(char));
                ASSERT(j->constant_pool[i]->bytes,"Cannot allocate j->constant_pool[i]->bytes");
                for (int k=0;k<j->constant_pool[i]->lengh;k++){
                    j->constant_pool[i]->bytes[k] = FileHandler_Read(f);
                }
                j->constant_pool[i]->bytes[j->constant_pool[i]->lengh] = '\0';
                //printf(" [%s]",j->constant_pool[i]->bytes);
                //FileHandler_Read(f)
                break;
            }
            case 7:{
                //Class
                j->constant_pool[i]->name_index               = DATAC_BigendianConv(f,2);
                break;
            }
            case 8:{
                //String
                j->constant_pool[i]->string_index             = DATAC_BigendianConv(f,2);
                break;
            }
            case 9:{
                //Fieldref
                j->constant_pool[i]->class_index              = DATAC_BigendianConv(f,2);
                j->constant_pool[i]->name_and_type_index      = DATAC_BigendianConv(f,2);
                break;
            }
            case 10:{
                //Method ref
                j->constant_pool[i]->class_index              = DATAC_BigendianConv(f,2);
                j->constant_pool[i]->name_and_type_index      = DATAC_BigendianConv(f,2);
                break;
            }
            case 12:{
                //NameAndType
                j->constant_pool[i]->name_index               = DATAC_BigendianConv(f,2);
                j->constant_pool[i]->descriptor_index         = DATAC_BigendianConv(f,2);

                break;
            }
            default:{
                printf("Error: Unknow tag [%d]\n",j->constant_pool[i]->tag);
            }
        }
        //printf("\n");
    }
}



void JAVA_freeJava(Java *j){
    for (int i=0;i<j->constant_pull_count-1;i++){
        if (j->constant_pool[i]->tag == 1){
            free(j->constant_pool[i]->bytes);
        }
        free(j->constant_pool[i]);
    }
    free(j->constant_pool);
    for (int i=0;i<j->methods_count ;i++){
        for (int k=0;k<j->methods[i]->attributes_count;k++){
            free(j->methods[i]->Attributes[k]->code); //Libera code
            for (int g=0;g<j->methods[i]->Attributes[k]->attributes_count;g++){
                AttrOfAttr *aux = j->methods[i]->Attributes[k]->Attrs[g];
                for (int t=0;t<aux->line_number_table_lenght;t++){
                    free(aux->LNTs[t]);
                }
                free(aux->LNTs);
                free(j->methods[i]->Attributes[k]->Attrs[g]);
            }
            free(j->methods[i]->Attributes[k]->Attrs);
            free(j->methods[i]->Attributes[k]);
        }
        free(j->methods[i]->Attributes);
        free(j->methods[i]);
    }
    free(j->methods);
    for (int i=0;i<j->attributes_count;i++){
        free(j->FAttr[i]);
    }
    free(j->FAttr);
    free(j);
}

