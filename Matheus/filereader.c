#include "filereader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


FileHandler *FileHandler_LoadFile(const char *s){
    FileHandler *file = calloc(1,sizeof(FileHandler));
    FILE *fp = fopen(s,"rb");
    if (fp == NULL){
        free(file);
        return NULL;
    }
    fseek(fp, 0L, SEEK_END);
    file->size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    file->stream = calloc(file->size+1,sizeof(char));
    ASSERT(file->stream,"Cannot alloc file->stream");
    file->name = calloc(strlen(s)+1,sizeof(char));
    ASSERT(file->name ,"Cannot alloc file->name");
    fread(file->stream, 1, file->size, fp);
    //printf("Loaded %s [%d]\n",s,file->size);
    fclose(fp);
    strcpy(file->name,s);
    file->pointer = 0;
    return file;
}

unsigned char FileHandler_Read(FileHandler *s){
    ASSERT(s->pointer < s->size,"File end. Trying to read");
    return s->stream[s->pointer++];
}


void FileHandler_free(FileHandler *s){
    //printf("Closing file %s\n",s->name);
    free(s->stream);
    free(s->name);
    free(s);
}
