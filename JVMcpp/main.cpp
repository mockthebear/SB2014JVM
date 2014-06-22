#include <stdint.h>
#include <iostream>
#include "jvm.hpp"

int main(){

    JVM *j = new JVM("HelloWorld.class");
    j->Run();
    delete j;
    return 0;
}
