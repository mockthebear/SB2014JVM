#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
void ASSERT(bool c,const char *s){
    if (!c){
        printf("FATAL ERROR: [%s]\n",s);
        exit(8);
    }
}
