#include <windows.h>
#ifndef CONSOLEHELPH
#define CONSOLEHELPH

typedef struct{
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

} Console;


Console *Start();
void Close(Console *);
#endif // CONSOLEHELPH
