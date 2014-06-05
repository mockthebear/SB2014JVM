#include <string.h>
#include "jclass.hpp"


JClass::JClass(std::string name){
    file = new FileHandler(name);
    magic                        = file->ReadBigEndian(4);
    //ASSERT(magic == 0xcafebabe,"Cafebabe not found!!!");
    minor                        = file->ReadBigEndian(2);
    major                        = file->ReadBigEndian(2);
    constant_pull_count          = file->ReadBigEndian(2);
    constant_pool = new contstant_method*[constant_pull_count];
    //ASSERT(constant_pool,"Cannot allocate constant_pool");
    parseConstantPool();
    access_flags                  = file->ReadBigEndian(2);
    this_class                    = file->ReadBigEndian(2);
    super_class                   = file->ReadBigEndian(2);
    interfaces_count              = file->ReadBigEndian(2);
    fields_count                  = file->ReadBigEndian(2);
    methods_count                 = file->ReadBigEndian(2);
    methods                       = new Method*[methods_count];
    //ASSERT(methods,"Cannot allocate methods");
    //JAVA_parseMethods(f,j);
    ParseMethods();
    attributes_count              = file->ReadBigEndian(2);
    FAttr                         = new FileAttr*[attributes_count];
    //ASSERT(FAttr,"Cannot allocate FAttr");
    //JAVA_parseFileAttributes(f,j);
    ParseFileAttributes();
    delete file;
    c_name = name.substr(0,name.size()-6);
}

const unsigned char* JClass::GetUTF8(int i){
    static unsigned char buff[] = "???";
    if (i > 0 && i < constant_pull_count){
        contstant_method *t = constant_pool[i-1];
        if (t->tag == 1){
            return (const unsigned char*)t->bytes;
        }else{
            return buff;
        }

    }
    return buff;
}



void JClass::ParseFileAttributes(){
    for (int i=0;i<attributes_count;i++){
        FAttr[i]                         =   new FileAttr;
        //ASSERT(FAttr[i],"Cannot allocate FAttr[i]");
        FAttr[i]->attribute_name_index   =   file->ReadBigEndian(2);
        FAttr[i]->attribute_lenght       =   file->ReadBigEndian(4);
        FAttr[i]->sourcefile_index       =   file->ReadBigEndian(2);
    }
}
void JClass::ParseMethods(){
    for (int i=0;i<methods_count ;i++){
        methods[i] = new Method;
        //ASSERT(methods[i],"Cannot allocate methods[i]");
        methods[i]->acess_flags      = file->ReadBigEndian(2);
        methods[i]->name_index       = file->ReadBigEndian(2);
        methods[i]->descriptor_index = file->ReadBigEndian(2);
        methods[i]->attributes_count = file->ReadBigEndian(2);

        //Attributtes

        methods[i]->Attributes       = new Attribute*[methods[i]->attributes_count];
        //ASSERT(methods[i]->Attributes,"Cannot allocate methods[i]->Attributes");

        //Load Attr

        for (int k=0;k<methods[i]->attributes_count;k++){
            methods[i]->Attributes[k]=new Attribute;
            //ASSERT(methods[i]->Attributes[k],"Cannot allocate methods[i]->Attributes[k]");
            methods[i]->Attributes[k]->attribute_name_index          =   file->ReadBigEndian(2);
            methods[i]->Attributes[k]->attribute_lenght              =   file->ReadBigEndian(4);//32
            methods[i]->Attributes[k]->max_stack                     =   file->ReadBigEndian(2);
            methods[i]->Attributes[k]->max_locals                    =   file->ReadBigEndian(2);
            methods[i]->Attributes[k]->code_lenght                   =   file->ReadBigEndian(4);//32
            methods[i]->Attributes[k]->code                          =   new unsigned char[methods[i]->Attributes[k]->code_lenght+1];
            //ASSERT(methods[i]->Attributes[k]->code,"Cannot allocate methods[i]->Attributes[k]->code");
            //printf("Code for attr %d ",k+1);

            for (int r=0;r<methods[i]->Attributes[k]->code_lenght;r++){
                methods[i]->Attributes[k]->code[r]                   =   file->Read();
            }
            methods[i]->Attributes[k]->code[methods[i]->Attributes[k]->code_lenght]  = '\0';
            methods[i]->Attributes[k]->exception_table_lenght        =   file->ReadBigEndian(2);
            methods[i]->Attributes[k]->attributes_count              =   file->ReadBigEndian(2);
            methods[i]->Attributes[k]->Attrs                         =   new AttrOfAttr*[methods[i]->Attributes[k]->attributes_count];
            //ASSERT(methods[i]->Attributes[k]->Attrs,"Cannot allocate methods[i]->Attributes[k]->Attrs");
            for (int g=0;g<methods[i]->Attributes[k]->attributes_count;g++){
                methods[i]->Attributes[k]->Attrs[g] = new AttrOfAttr;
                //ASSERT(methods[i]->Attributes[k]->Attrs[g],"Cannot allocate methods[i]->Attributes[k]->Attrs[g]");
                AttrOfAttr *aux = methods[i]->Attributes[k]->Attrs[g];
                //Ok
                aux->attribute_name_index                               =   file->ReadBigEndian(2);
                aux->attribute_lenght                                   =   file->ReadBigEndian(4);
                aux->LNTs = NULL;
                aux->raw = NULL;
                if (strcmp((const char*)GetUTF8(aux->attribute_name_index) ,"LineNumberTable" ) == 0  ){
                    aux->line_number_table_lenght                           =   file->ReadBigEndian(2);
                    //VÉI. CHEGA =/
                    aux->LNTs                                               = new LNT*[aux->line_number_table_lenght];
                    //ASSERT(methods[i]->Attributes[k]->Attrs[g]->LNTs,"Cannot allocate methods[i]->Attributes[k]->Attrs[g]->LNTs");
                    for (int t=0;t<aux->line_number_table_lenght;t++){
                        aux->LNTs[t]                =   new LNT;
                        //ASSERT(methods[i]->Attributes[k]->Attrs[g]->LNTs[t],"Cannot allocate methods[i]->Attributes[k]->Attrs[g]->LNTs[t]");

                        aux->LNTs[t]->start_pc      =   file->ReadBigEndian(2);
                        aux->LNTs[t]->line_number   =   file->ReadBigEndian(2);
                    }
                }else{
                    aux->raw = new unsigned char[aux->attribute_lenght+1];
                    for (int t=0;t<aux->attribute_lenght;t++){
                        aux->raw[t] = file->Read();
                    }
                    aux->raw[aux->attribute_lenght] = '\0';
                }
            }
        }
    }
}


void JClass::parseConstantPool(){
    for (int i=0;i<constant_pull_count-1;i++){
        constant_pool[i] = new contstant_method;
        constant_pool[i]->tag = file->ReadBigEndian(1);
        constant_pool[i]->name = Strings_[constant_pool[i]->tag];
        constant_pool[i]->lengh = 0;
        //printf("%s [%d]",constant_pool[i]->name,constant_pool[i]->tag);

        switch( constant_pool[i]->tag){
            case 1:{
                //UTF8
                constant_pool[i]->lengh                    = file->ReadBigEndian(2);
                constant_pool[i]->bytes                    = new unsigned char[constant_pool[i]->lengh+1];
                for (int k=0;k<constant_pool[i]->lengh;k++){
                    constant_pool[i]->bytes[k] = file->Read();
                }
                constant_pool[i]->bytes[constant_pool[i]->lengh] = '\0';
                //printf(" [%s]",constant_pool[i]->bytes);
                //FileHandler_Read(f)
                break;
            }
            case 7:{
                //Class
                constant_pool[i]->name_index               = file->ReadBigEndian(2);
                break;
            }
            case 8:{
                //String
                constant_pool[i]->string_index             = file->ReadBigEndian(2);
                break;
            }
            case 9:{
                //Fieldref
                constant_pool[i]->class_index              = file->ReadBigEndian(2);
                constant_pool[i]->name_and_type_index      = file->ReadBigEndian(2);
                break;
            }
            case 10:{
                //Method ref
                constant_pool[i]->class_index              = file->ReadBigEndian(2);
                constant_pool[i]->name_and_type_index      = file->ReadBigEndian(2);
                break;
            }
            case 11:{
                //Interface Method Ref
                constant_pool[i]->class_index              = file->ReadBigEndian(2);
                constant_pool[i]->name_and_type_index      = file->ReadBigEndian(2);
                break;
            }
            case 12:{
                //NameAndType
                constant_pool[i]->name_index               = file->ReadBigEndian(2);
                constant_pool[i]->descriptor_index         = file->ReadBigEndian(2);

                break;
            }
            default:{
                printf("Error: Unknow tag [%d]->%d\n",constant_pool[i]->tag,i);
            }
        }
    }
}

JClass::~JClass(){
    std::cout << "Closing [" << c_name << "]\n";
    for (int i=0;i<methods_count ;i++){
        for (int k=0;k<methods[i]->attributes_count;k++){
            delete[] methods[i]->Attributes[k]->code; //Libera code
            for (int g=0;g<methods[i]->Attributes[k]->attributes_count;g++){
                AttrOfAttr *aux = methods[i]->Attributes[k]->Attrs[g];
                if ( strcmp((const char*)GetUTF8(aux->attribute_name_index) ,(const char*)"LineNumberTable" ) == 0 ) {
                    for (int t=0;t<aux->line_number_table_lenght;t++){
                        delete(aux->LNTs[t]);
                    }
                    delete(aux->LNTs);
                }else{
                    delete(aux->raw);
                }
                delete(methods[i]->Attributes[k]->Attrs[g]);
            }
            delete(methods[i]->Attributes[k]->Attrs);
            delete(methods[i]->Attributes[k]);
        }
        delete(methods[i]->Attributes);
        delete(methods[i]);
    }
    delete(methods);
    //Clearing constant pool
    for (int i=0;i<constant_pull_count-1;i++){
        if (constant_pool[i]->tag == 1){
            delete(constant_pool[i]->bytes);
        }
        delete(constant_pool[i]);
    }
    delete(constant_pool);
    //Clearing attrs
    for (int i=0;i<attributes_count;i++){
        delete(FAttr[i]);
    }
    delete(FAttr);

}
