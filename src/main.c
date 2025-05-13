#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/ast.h"
#include "../include/error.h"

int main()
{
    char *bakscript_code = "make num n = 3\n show \"The value of n is\" \n show n";
    printf("Code:\n%s\n\n", bakscript_code);

    printf("Tokens:\n");
    printTokens(bakscript_code);

    Lexer lexer = init_lexer(bakscript_code);
    initErrorModule();

    printf("Parsing Program ... \n");
    ASTNode *programNode = parseProgram(&lexer);

    if (hasErrors())
    {
        printf("\nErrors Found:\n");
        displayErrors();
    }
    else
    {
        printf("\nNo syntax errors found. Parsed AST:\n");
        print_ast(programNode);
    }

    free_ast(programNode);
    clearErrors();

    return 0;
}