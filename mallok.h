#ifndef MALLOK_H
#define MALLOK_H

#include <stddef.h>
#include <stdlib.h>

// To stop circular calling of the mallok_* functions put #define MALLOK_MACROS at the top
#ifndef MALLOK_MACROS
#define MALLOK_MACROS

#define malloc(size)  mallokMalloc(size, __FILE__, __LINE__)
#define free(pointer) mallokFree(pointer) 

#endif

void *mallokMalloc(size_t size, char *file, int line);
void mallokFree(void *pointer);
void mallok();

#endif