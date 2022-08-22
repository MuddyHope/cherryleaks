#include "cherry_leaks.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

typedef struct vector{
    int x;
    int y;
}VEC;

int main (void)
{
    VEC v1;
    v1.x = 15;
    v1.y = 14;
    void * h = malloc(100);
    void * bar = malloc(300);

    bar = realloc(bar, 400);

    free(h);

    C_MEM_END_PRINT_ALL
    return 0;
}
