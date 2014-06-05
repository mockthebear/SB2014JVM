#include "filereader.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>


FileHandler::FileHandler(std::string name_){
    FILE *fp = fopen(name_.c_str(),"rb");
    //ASSERT(fp,"Error! Cannot load file.");
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    stream = new unsigned char[size+1]; //calloc(size+1,sizeof(char));
    //ASSERT(stream,"Cannot alloc file->stream");
    name = new char[strlen(name_.c_str())+1];//,sizeof(char));
    //ASSERT(name ,"Cannot alloc file->name");
    fread(stream, 1, size, fp);
    fclose(fp);
    strcpy(name,name_.c_str());
    pointer = 0;
}

unsigned char FileHandler::Read(){
    if (!pointer < size){
        char buff[50];
        sprintf(buff,"File end. Trying to read %d to %d",pointer,size);
        //ASSERT(pointer < size,buff);

    }
    return stream[pointer++];
}

uint32_t FileHandler::ReadBigEndian(int n){
    uint32_t ret = 0;
    for (int i=0;i<n;i++){
        ret |= Read() << ((n-i-1)*8);
    }
    return ret;
}


FileHandler::~FileHandler(){
    free(stream);
    free(name);
}
