#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "../include/ast.h"

ASTNode *create_ast_node(astNodeType type)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = type;
    node->next = NULL;
    return node;
}

void print_ast(ASTNode *node)
{

    if (node == NULL)
        return;

    switch (node->type)
    {
    case astNode_PROGRAM:
        printf("Program:\n");
        print_ast(node->next);
        break;

    case astNode_ASSIGNMENT:
        printf("Assignments : %s = ", node->variable);
        print_ast(node->binary.left);
        break;

    case astNode_PRINT:
        printf("Print :\n");
        print_ast(node->binary.left);
        break;

    case astNode_NUMBER:
        printf("Number:%d\n", node->number);
        break;

    default:
        printf("Unknown AST Node\n");
        break;
    }

    print_ast(node->next);
}

void free_ast(ASTNode *node)
{
    if (node == NULL)
        return;
    if (node->type == astNode_ASSIGNMENT || node->type == astNode_PRINT)
    {
        free_ast(node->binary.left);
    }
    free_ast(node->next);

    if (node->type == astNode_ASSIGNMENT)
    {
        free(node->variable);
    }
    free(node);
}