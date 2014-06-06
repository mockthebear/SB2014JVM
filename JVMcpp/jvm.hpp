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

        Method *GetMethodByConstantPool(uint16_t,uint16_t);
        Method *GetMethodByName(uint16_t,std::string);
    private:
        int mainclass;
        std::map<uint16_t,std::unique_ptr<JClass>> Classes;
        //Memory
        //Stack
        //bla


};


#endif // JVMH
