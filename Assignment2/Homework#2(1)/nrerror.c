#include <stdio.h>
#include <stdlib.h>

void nrerror(char error_text[])
{
    fprintf(stderr, "nrerror: %s\n", error_text);
    exit(EXIT_FAILURE);
}
