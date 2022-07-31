#include "c-mem.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

int main(void)
{
    C_MEM_START
    void* moi = malloc(1000);

    void* cal = calloc(5, sizeof(char));

    free(moi);
    free(cal);

    C_MEM_END_PRINT_LEFT
    return 0;
}
