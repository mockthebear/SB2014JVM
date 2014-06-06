#include "jvm.hpp"


JVM::JVM(std::string mainclass_str){
    //Start stuff
    mainclass = LoadClass(mainclass_str);
    //GetMethodByConstantPool(mainclass,1);
    Method *m = GetMethodByName(mainclass,"<init>");
    for (int i=0;i<m->Attributes[0]->code_lenght;i++){
        printf("%X ",m->Attributes[0]->code[i] );
    }
    //std::cout << m->Attributes[0]->code << "\n";
}

JVM::~JVM(){
    //close stuff
    Classes.clear();
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
Method *JVM::GetMethodByName(uint16_t index ,std::string search_name){
    if (Classes[index]){
        for (int i=1;i<Classes[index]->getMethodsCount();i++){
            std::string name((const char*)Classes[index]->GetUTF8(Classes[index]->methods[i]->name_index));
            if (name == search_name){
                return Classes[index]->methods[i];
            }
        }
        std::cout << "Method " << search_name << " not found." << std::endl;
    }else{
        std::cout << "Class index "<<index << " not found" << '\n';
    }
    return NULL;
}
