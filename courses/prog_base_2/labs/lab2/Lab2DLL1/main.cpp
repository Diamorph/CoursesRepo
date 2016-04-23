#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check(stack_t self, char* str) {
    int num;
    int numOfScanned = sscanf(str, "pop %i", &num);
    char numAsStr[20];
    itoa(num, numAsStr, 10);
    if (numOfScanned == 1 && num > 0 && strlen("pop ") + strlen(numAsStr) == strlen(str)) return 1;
    return 0;
}

void reaction(stack_t self, char* str){
    int numToDelete;
    sscanf(str, "pop %i", &numToDelete);
    for (int i = 0; i<numToDelete; i++){
        printf("Popped: %s\n", stack_pop(self));
    }
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
