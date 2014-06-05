#include <stdint.h>
#include <iostream>
#include "jvm.hpp"

int main(){

    JVM *j = new JVM();

    delete j;
    return 0;
}
