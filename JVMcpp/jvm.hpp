#ifndef JVMH
#define JVMH
#include "jclass.hpp"
#include <iostream>
#include <string>
#include <map>
#include <memory>



class JVM{
    public:
        JVM(std::string);
        ~JVM();
        uint16_t LoadClass(std::string name);

        bool Run();

        Method *GetMethodByConstantPool(uint16_t,uint16_t);
        Attribute *GetMethodByName(uint16_t,std::string);
    private:
        int mainclass;
        std::map<uint16_t,std::unique_ptr<JClass>> Classes;

        void RunCode(Attribute *a);

        //Memory
        //Stack
        //bla


};


#endif // JVMH
