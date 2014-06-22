#ifndef INSTRUCTIONSH
#define INSTRUCTIONSH

#include <map>
#include <functional>
#include <iostream>

class Instructions{ //Singleton
    public:
        Instructions();
        ~Instructions(){};
        static Instructions& GetInstance();

    std::function<int(unsigned char*)> GetFunction(unsigned char OP){ return OpCodes[OP];};


    static uint32_t ReadBigEndian(unsigned char *s,int start,int n){
        uint32_t ret = 0;
        for (int i=0;i<n;i++){
            ret |= s[start+i] << ((n-i-1)*8);
        }
        return ret;
    }

    private:

        std::map<unsigned char, std::function<int(unsigned char*)> > OpCodes;


        //Funções
        static int OP12(unsigned char*s){
            std::cout << "Chamou a LDC com o parametro " << (int)s[1] << '\n';
            return 1;
        }

        static int OPb2(unsigned char*s){
            std::cout << "Chamou a getstatic com parametros [1] = " << (int)s[1] << " e [2] = " << (int)s[2] <<  '\n';
            return 2;
        }



} ;

#endif // INSTRUCTIONSH
