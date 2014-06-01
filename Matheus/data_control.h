#include <stdint.h>
#include "filereader.h"
#ifndef DATACONTROLH
#define DATACONTROLH

uint32_t DATAC_BigendianConv(FileHandler *f,int n);
uint32_t DATAC_BigendianConvp(unsigned char *s,int p,int n);

#endif // DATACONTROLH
