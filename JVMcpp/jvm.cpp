#include "jvm.hpp"


JVM::JVM(){
    //Start stuff
    LoadClass("HelloWorld.class");
}

JVM::~JVM(){
    //close stuff
}

void JVM::LoadClass(std::string name){
    try{
       //std::unique_ptr<JClass> J(new JClass(name));
       JClass *J = new JClass(name);
       std::cout << "Loaded " <<J->GetClassName() << '\n';
       Classes[J->GetClassName()] = std::unique_ptr<JClass>(J) ;
    }
    catch (int e){

    }
}
