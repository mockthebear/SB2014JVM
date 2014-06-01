#include "data_control.h"


uint32_t DATAC_BigendianConv(FileHandler *f,int n){
    uint32_t ret = 0;
    for (int i=0;i<n;i++){
        ret |= FileHandler_Read(f) << ((n-i-1)*8);
    }
    return ret;
}

uint32_t DATAC_BigendianConvp(unsigned char *s,int p,int n){
    uint32_t ret = 0;
    for (int i=n-1;i>=0;i--){
        ret |= s[p+i] << ((n-i-1)*8);
    }
    return ret;
}
