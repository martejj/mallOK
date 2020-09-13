#include <stdlib.h>
#include <stdio.h>
#include "mallok.h"


int main(void) {
    
    void *something = malloc(10);
    mallok();
    free(something);
    mallok();
    return 0;
}