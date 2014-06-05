#include <stdbool.h>
#include <iostream>
#include <string>

#ifndef FILEHANDLERH
#define FILEHANDLERH

class FileHandler{
    public:
        FileHandler(std::string name);
        ~FileHandler();
        unsigned char Read();
        uint32_t ReadBigEndian(int n);
    private:
        int size;
        int pointer;
        unsigned char *stream;
        char *name;
};


#endif // FILEHANDLERH
