#include "c-mem.h"

int main()
{
    START;
    void * hello = malloc(100);
    //Needs to be more clear
    void * moi = realloc(hello, 120);
    printf("Hello World\n");
    END_PRINT_ALL;
    return 0;
}