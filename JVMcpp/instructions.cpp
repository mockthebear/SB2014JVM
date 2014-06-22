#include "instructions.hpp"


Instructions::Instructions(){

    OpCodes[0xb2] = OPb2; //getstatic
    OpCodes[0x12] = OP12; //LDC
}
Instructions& Instructions::GetInstance(){
    static Instructions s;
    return s;
}
