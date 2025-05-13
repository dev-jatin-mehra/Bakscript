<<<<<<< HEAD
#include "../include/parser.h"
#include "../include/error.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

static void error(const char *msg);

int isKeyword(TK_TYPE type)
{
    return (type == TOKEN_WHEN || type == TOKEN_OTHERWISE ||
            type == TOKEN_REPEAT || type == TOKEN_ASLONG ||
            type == TOKEN_MAKE || type == TOKEN_SHOW ||
            type == TOKEN_TEXT || type == TOKEN_NUM ||
            type == TOKEN_DECIMAL);
}

void synchronize(Lexer *lexer)
{
    Token token;
    do
    {
        token = getNextToken(lexer);
    } while (token.type != TOKEN_EOF && !isKeyword(token.type));
}

Token advanceParser(Lexer *lexer)
{
    if (lexer->pos < strlen(lexer->source))
    {
        return getNextToken(lexer);
    }
    else
    {
        reportError(ERROR_UNEXPECTED_TOKEN, lexer->pos, "Unexpected end of input.");
        return (Token){.type = TOKEN_EOF, .lexeme = "EOF"};
    }
}

int match(Lexer *lexer, TK_TYPE expectedType)
{
    return 1;
}

ASTNode *parseProgram(Lexer *lexer)
{
    ASTNode *programNode = create_ast_node(astNode_PROGRAM);
    ASTNode *currentStatement = NULL;
    ASTNode *lastStatement = NULL;

    while (lexer->pos < strlen(lexer->source))
    {
        ASTNode *statement = parseStatement(lexer);
        if (statement == NULL)
        {
            break;
        }
        if (lastStatement == NULL)
        {
            programNode->next = statement;
        }
        else
        {
            lastStatement->next = statement;
        }
        lastStatement = statement;
    }
    return programNode;
}

ASTNode *parseStatement(Lexer *lexer)
{
    Token token = getNextToken(lexer);
    if (token.type == TOKEN_IDENTIFIER)
    {
        if (peek(lexer) == '=')
        {
            return parseAssignment(lexer);
        }
    }
    else if (isKeyword(token.type) && strcmp(token.lexeme, "show") == 0)
    {
        return parsePrintStatement(lexer);
    }

    return NULL;
}

ASTNode *parseAssignment(Lexer *lexer)
{
    Token variableToken = getNextToken(lexer);
    match(lexer, '=');

    ASTNode *expressionNode = parseExpression(lexer);
    return;
}

ASTNode *parsePrintStatement(Lexer *lexer)
{
    return;
}

ASTNode *parseExpression(Lexer *lexer)
{
    return;
}

ASTNode *parseNumber(Lexer *lexer)
{
    return;
}

void advanceParser(Lexer *lexer)
{
    lexer->pos++;
}

int match(Lexer *lexer, TK_TYPE type)
{
    return 0;
}

int expect(Lexer *lexer, TK_TYPE type)
{
    return 0;
}
=======
#include "../include/parser.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

static void error(const char *msg);

int isKeyword(TK_TYPE type) {
    return (type == TOKEN_WHEN || type == TOKEN_OTHERWISE || 
            type == TOKEN_REPEAT || type == TOKEN_ASLONG || 
            type == TOKEN_MAKE || type == TOKEN_SHOW || 
            type == TOKEN_TEXT || type == TOKEN_NUM || 
            type == TOKEN_DECIMAL);
}

ASTNode *parseProgram(Lexer *lexer)
{
    ASTNode *programNode = create_ast_node(astNode_PROGRAM);
    ASTNode *currentStatement = NULL;
    ASTNode *lastStatement = NULL;

    while (lexer->pos < strlen(lexer->source))
    {
        ASTNode *statement = parseStatement(lexer);
        if (statement == NULL)
        {
            break;
        }
        if (lastStatement == NULL)
        {
            programNode->next = statement;
        }
        else
        {
            lastStatement->next = statement;
        }
        lastStatement = statement;
    }
    return programNode;
}

ASTNode *parseStatement(Lexer *lexer)
{
    Token token = getNextToken(lexer);
    if (token.type == TOKEN_IDENTIFIER)
    {
        if (peek(lexer) == '=')
        {
            return parseAssignment(lexer);
        }
    }
    else if (isKeyword(token.type) && strcmp(token.lexeme, "show") == 0)
    {
        return parsePrintStatement(lexer);
    }

    return NULL;
}

ASTNode *parseAssignment(Lexer *lexer)
{
    Token variableToken = getNextToken(lexer);
    match(lexer, '=');

    ASTNode *expressionNode = parseExpression(lexer);
    return;
}

ASTNode *parsePrintStatement(Lexer *lexer)
{
    return;
}

ASTNode *parseExpression(Lexer *lexer)
{
    return;
}

ASTNode *parseNumber(Lexer *lexer)
{
    return;
}

void advanceParser(Lexer *lexer)
{
    lexer->pos++;
}

int match(Lexer *lexer, TK_TYPE type)
{
    return 0;
}

int expect(Lexer *lexer, TK_TYPE type)
{
    return 0;
}
>>>>>>> 81ea01b72b5b3723a66137b6bd85795578402968
