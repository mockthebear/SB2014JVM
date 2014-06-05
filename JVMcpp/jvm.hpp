#ifndef JVMH
#define JVMH
#include "jclass.hpp"
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

class JVM{
    public:
        JVM();
        ~JVM();
        void LoadClass(std::string name);
    private:
        std::unordered_map<std::string,std::unique_ptr<JClass>> Classes;
        //Memory
        //Stack
        //bla


};


#endif // JVMH
