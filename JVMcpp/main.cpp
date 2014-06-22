#include <stdint.h>
#include <iostream>
#include "jvm.hpp"

int main(){

    JVM *j = new JVM("Bubblesort.class");
    j->Run();
    delete j;
    return 0;
}
