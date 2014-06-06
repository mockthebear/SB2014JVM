#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>




#ifndef JAVAH
#define JAVAH
#include "java_structs.hpp"
#include "filereader.hpp"

class  JClass{
    public:
    JClass(std::string name);
    ~JClass();
    const unsigned char* GetUTF8(int i);


    std::string GetClassName(){return c_name;};
    contstant_method    **constant_pool;
    Method              **methods;
    FileAttr            **FAttr;
    Field               **fields;
    uint16_t getConstantPoolCount()         { return constant_pull_count;};
    uint16_t getMethodsCount()              { return methods_count;};
    uint16_t getAttributesCount()           { return attributes_count;};
    private:
        std::string c_name;

        uint32_t            magic;
        uint16_t            minor;
        uint16_t            major;
        uint16_t            constant_pull_count;
        uint16_t            access_flags;
        uint16_t            this_class;
        uint16_t            super_class;
        uint16_t            interfaces_count;
        uint16_t            fields_count;
        uint16_t            methods_count;
        uint16_t            attributes_count;


        //Para uso interno
        void parseConstantPool();
        void ParseMethods();
        void ParseFileAttributes();
        void ParseFields();
        FileHandler *file;
};



/*
Java *JAVA_createJava(FileHandler *f);
const unsigned char* JAVA_GetUTF8(Java *j,int i);
int JAVA_(FileHandler *f,Java *j);
int JAVA_parseConstantPool(FileHandler *f,Java *j);
int JAVA_(FileHandler *f,Java *j);
*/

#endif // JAVAH
