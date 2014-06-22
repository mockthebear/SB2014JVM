#include "instructions.hpp"


Instructions::Instructions(){

    OpCodes[0xb2] = OPb2; //getstatic
    OpCodes[0x12] = OP12; //getstatic
}
Instructions& Instructions::GetInstance(){
    static Instructions s;
    return s;
}
