#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>


/*  To use this exported function of dll, include this header
 *  in your project.
 */

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif
#include "stack.h"
int DLL_EXPORT check(stack_t self, char* str);
void DLL_EXPORT reaction(stack_t self, char* str);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
