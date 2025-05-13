#ifndef AST_H
#define AST_H

typedef enum
{
    astNode_PROGRAM,
    astNode_STATEMENT,
    astNode_ASSIGNMENT,
    astNode_PRINT,
    astNode_EXPRESSION,
    astNode_NUMBER
} astNodeType;

typedef struct ASTNode
{
    astNodeType type;
    union
    {
        struct
        {
            struct ASTNode *left;
            struct ASTNode *right;
        } binary;
        int number;
        char *variable;
    };
    struct ASTNode *next;
} ASTNode;

ASTNode *create_ast_node(astNodeType type);
void print_ast(ASTNode *node);
void free_ast(ASTNode *node);

#endif