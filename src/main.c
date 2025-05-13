#include <stdio.h>
#include <stdlib.h>
#include "../include/lexer.h"

int main()
{
    char *bakscript_code = "make num n = 3 aslong n > 0 : show \"Counting down:\" show n make n = n - 1";

    printTokens(bakscript_code);

    return 0;
}