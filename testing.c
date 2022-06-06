#include "c-mem.h"

int main()
{
    START;
    void * hello = malloc(100);
    void * moi = realloc(hello, 120);
    free(moi);
    printf("Hello World\n");
    return 0;
}