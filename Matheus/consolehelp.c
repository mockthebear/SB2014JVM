
#include "consolehelp.h"


Console *Start(){
    Console *c = calloc(1,sizeof(Console));
    c->hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(c->hConsole, &c->consoleInfo);
    c->saved_attributes = c->consoleInfo.wAttributes;
    return c;
}
void SetColor(Console *c,int n){
    SetConsoleTextAttribute(c->hConsole, n);
}
void SetPos(Console *c,int x,int y){
    COORD pos = {x, y};
    SetConsoleCursorPosition(c->hConsole, pos);
}
void Close(Console *c){
    SetConsoleTextAttribute(c->hConsole, c->saved_attributes);
    free(c);
}
