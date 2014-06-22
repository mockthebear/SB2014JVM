#include "jvm.hpp"
#include "instructions.hpp"

JVM::JVM(std::string mainclass_str){
    //Start stuff
    mainclass = LoadClass(mainclass_str);
    //GetMethodByConstantPool(mainclass,1);
    Attribute *m = GetMethodByName(mainclass,"<init>");
    for (unsigned int i=0;i<m->code_lenght;i++){
        printf("%X ",m->code[i] );
    }
    //TODO
    //Rodar o init.
    //std::cout << m->Attributes[0]->code << "\n";
}

JVM::~JVM(){
    //close stuff
    Classes.clear();
}

//Run!!

bool JVM::Run(){
    Attribute *m = GetMethodByName(mainclass,"main");
    if (!m){
        std::cout << "Cannot find class MAIN!\n";
        return false;
    }
    try{
       RunCode(m);

    }
    catch (int e){
        std::cout << "[ERROR] Exception " << e << " -> ";
        switch (e){
            case 10:{
                std::cout << "Opcode is calling an function that is not registred" << std::endl;
                break;
            }
            case 11:{
                std::cout << "Opcode returned false." << std::endl;
                break;
            }

            default:{
                std::cout << "Regular error" << std::endl;
            }
        }
    }


    delete (m);
    std::cout << "Done\n";
    return true;
}

void JVM::RunCode(Attribute *a){
    Instructions ins = Instructions::GetInstance();
    while (a->thispc != a->code_lenght){
        //Execute!
        unsigned char OPCODE = a->code[a->thispc];

        if (!ins.GetFunction(OPCODE)){
            //Opcode não encontrado!
            throw 10;

        }
        auto F = ins.GetFunction(OPCODE);
        unsigned char *str = new unsigned char[a->code_lenght+1];
        int pos = 0;
        for (int i=a->thispc;i<a->code_lenght;i++){
            str[pos] = a->code[i];
            pos++;
        }

        int ret = F(str);
        delete str;
        if (ret == -1){
           //A função retornou falha!
           throw 11;
        }
        a->thispc += 1+ret;
        std::cout << "Enter para executar [" << a->thispc << "]\n";
        getchar();
    }
}


uint16_t JVM::LoadClass(std::string name){
    static uint16_t class_counter = 0;
    try{
       //std::unique_ptr<JClass> J(new JClass(name));
       JClass *J = new JClass(name);

       Classes[class_counter] = std::unique_ptr<JClass>(J) ;
       std::cout << "Loaded " <<Classes[class_counter]->GetClassName() << " [" << class_counter << "]" << '\n';
       class_counter++;
       return class_counter-1;
    }
    catch (int e){

    }
    return -1;
}

Method *JVM::GetMethodByConstantPool(uint16_t index,uint16_t cpindex){
    if (Classes[index]){
        if (cpindex > Classes[index]->getConstantPoolCount()){
            //  Erro
            std::cout << "Not in the constant pool" << '\n';
        }
        if (Classes[index]->constant_pool[cpindex]->tag != 10 ){
            std::cout << "Not methoed ref [" << (int)Classes[index]->constant_pool[cpindex]->tag << "]" << cpindex << '\n';
            //Erro
        }
        //Busca name and typr
        int NTI = Classes[index]->constant_pool[cpindex]->name_and_type_index;
        if (Classes[index]->constant_pool[NTI]->tag != 12){
            std::cout << "Not NameAndType[" << NTI << "]" << '\n';
        }
        int nameindex   =  Classes[index]->constant_pool[NTI]->name_index;
        int descindex   =  Classes[index]->constant_pool[NTI]->descriptor_index;
        for (int i=1;i<Classes[index]->getMethodsCount();i++){
            if (Classes[index]->methods[i]->name_index == nameindex &&
            Classes[index]->methods[i]->descriptor_index == descindex){
                    return Classes[index]->methods[i];
                 }
        }
        std::cout << "Method not found" << '\n';
    }else{
        std::cout << "Class index "<<index << " not found" << '\n';
    }
    return NULL;
}
Attribute *JVM::GetMethodByName(uint16_t index ,std::string search_name){
    if (Classes[index]){
        for (int i=1;i<Classes[index]->getMethodsCount();i++){
            std::string name((const char*)Classes[index]->GetUTF8(Classes[index]->methods[i]->name_index));
            if (name == search_name){
                Attribute *newat = new Attribute;
                newat->attributes_count          = Classes[index]->methods[i]->Attributes[0]->attributes_count   ;
                newat->attribute_lenght          = Classes[index]->methods[i]->Attributes[0]->attribute_lenght   ;
                newat->attribute_name_index      = Classes[index]->methods[i]->Attributes[0]->attribute_name_index   ;
                newat->Attrs = NULL;
                newat->code                      = Classes[index]->methods[i]->Attributes[0]->code   ;
                newat->code_lenght               = Classes[index]->methods[i]->Attributes[0]->code_lenght   ;
                newat->exception_table_lenght    = Classes[index]->methods[i]->Attributes[0]->exception_table_lenght;
                newat->max_locals                = Classes[index]->methods[i]->Attributes[0]->max_locals;
                newat->max_stack    = Classes[index]->methods[i]->Attributes[0]->max_stack;
                newat->thispc = 0;
                return newat;
            }
        }
        std::cout << "Method " << search_name << " not found." << std::endl;
    }else{
        std::cout << "Class index "<<index << " not found" << '\n';
    }
    return NULL;
}
