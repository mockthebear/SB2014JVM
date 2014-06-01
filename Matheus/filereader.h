#include <stdbool.h>
#include "errors.h"

#ifndef FILEHANDLERH
#define FILEHANDLERH

typedef struct{
    int size;
    int pointer;
    unsigned char *stream;
    char *name;
} FileHandler;


FileHandler* FileHandler_LoadFile(const char *s);
void FileHandler_free(FileHandler *s);
unsigned char FileHandler_Read(FileHandler *s);
#endif // FILEHANDLERH
