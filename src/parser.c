#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/ast.h"
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
    Token token = getNextToken(lexer);
    if (token.type == expectedType)
    {
        advanceParser(lexer);
        return 1;
    }
    else
    {
        char errorMsg[128];
        snprintf(errorMsg, sizeof(errorMsg), "Expected token of type %d but found %d.", expectedType, token.type);
        reportError(ERROR_UNEXPECTED_TOKEN, lexer->pos, errorMsg);
        synchronize(lexer);
        return 0;
    }
}

void expect(Lexer *lexer, TK_TYPE expectedType, const char *errorMessage)
{
    Token token = getNextToken(lexer);
    if (token.type != expectedType)
    {
        reportError(ERROR_UNEXPECTED_TOKEN, lexer->pos, errorMessage);
        synchronize(lexer);
    }
    else
    {
        advanceParser(lexer);
    }
}

ASTNode *parseProgram(Lexer *lexer)
{
    initErrorModule();
    ASTNode *programNode = create_ast_node(astNode_PROGRAM);
    ASTNode *currentStatement = NULL;
    ASTNode *lastStatement = NULL;

    while (lexer->pos < strlen(lexer->source))
    {
        ASTNode *statement = parseStatement(lexer);
        if (statement == NULL)
        {
            reportError(ERROR_SYNTAX, lexer->pos, "Invalid statement syntax.");
            synchronize(lexer);
            continue;
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
    Token token = advanceParser(lexer);
    if (token.type == TOKEN_IDENTIFIER)
    {
        if (match(lexer, TOKEN_EQUAL))
        {
            return parseAssignment(lexer);
        }
        else
        {
            reportError(ERROR_UNEXPECTED_TOKEN, lexer->pos, "Expected '=' after identifier.");
            return NULL;
        }
    }
    else if (token.type == TOKEN_SHOW)
    {
        return parsePrintStatement(lexer);
    }
    else if (token.type == TOKEN_MAKE)
    {
        return parseVariableDeclaration(lexer);
    }
    reportError(ERROR_SYNTAX, lexer->pos, "Unexpected token in statement.");
    return NULL;
}

ASTNode *parseVariableDeclaration(Lexer *lexer)
{
    Token token = advanceParser(lexer);
    if (token.type != TOKEN_IDENTIFIER)
    {
        reportError(ERROR_UNEXPECTED_TOKEN, lexer->pos, "Expected [num,decimal,text] after make.");
        synchronize(lexer);
        return NULL;
    }
    token = advanceParser(lexer);
    if (token.type != TOKEN_IDENTIFIER)
    {
        reportError(ERROR_UNEXPECTED_TOKEN, lexer->pos, "Expected variable name after type.");
        synchronize(lexer);
        return NULL;
    }

    ASTNode *varNode = create_ast_node(astNode_ASSIGNMENT);
    varNode->variable = strdup(token.lexeme);

    expect(lexer, TOKEN_EQUAL, "Expected '=' after variable name.");

    ASTNode *valueNode = parseExpression(lexer);
    if (valueNode != NULL)
    {
        varNode->binary.right = valueNode;
    }
    return varNode;
}

ASTNode *parsePrintStatement(Lexer *lexer)
{
    ASTNode *printNode = create_ast_node(astNode_PRINT);
    Token token = advanceParser(lexer);

    if (token.type == TOKEN_STRING)
    {
        ASTNode *stringNode = create_ast_node(astNode_STRING);
        stringNode->stringValue = strdup(token.lexeme);
        printNode->binary.left = stringNode;
    }
    else if (token.type == TOKEN_IDENTIFIER)
    {
        ASTNode *variableNode = create_ast_node(astNode_IDENTIFIER);
        variableNode->variable = strdup(token.lexeme);
        printNode->binary.left = variableNode;
    }
    else
    {
        reportError(ERROR_SYNTAX, lexer->pos, "Expected a string or variable after 'show'.");
        synchronize(lexer);
    }

    return printNode;
}

ASTNode *parseAssignment(Lexer *lexer)
{
    Token variableToken = advanceParser(lexer);
    expect(lexer, TOKEN_EQUAL, "Expected '=' in assignment.");
    ASTNode *expressionNode = parseExpression(lexer);
    if (!expressionNode)
    {
        reportError(ERROR_SYNTAX, lexer->pos, "Invalid expression in assignment.");
        return NULL;
    }
    return expressionNode;
}

ASTNode *parseExpression(Lexer *lexer)
{
    Token token = advanceParser(lexer);

    if (token.type == TOKEN_NUMBER)
    {
        return parseNumber(lexer);
    }
    else if (token.type == TOKEN_IDENTIFIER)
    {
        ASTNode *identifierNode = create_ast_node(astNode_VARIABLE);
        identifierNode->variable = strdup(token.lexeme);
        return identifierNode;
    }
    else if (token.type == TOKEN_STRING)
    {
        ASTNode *stringNode = create_ast_node(astNode_STRING);
        stringNode->variable = strdup(token.lexeme);
        return stringNode;
    }
    else
    {
        reportError(ERROR_SYNTAX, lexer->pos, "Invalid expression.");
        synchronize(lexer);
        return NULL;
    }
}

ASTNode *parseNumber(Lexer *lexer)
{
    Token token = advanceParser(lexer);
    if (token.type == TOKEN_NUMBER)
    {
        ASTNode *numberNode = create_ast_node(astNode_NUMBER);
        numberNode->number = atoi(token.lexeme);
        return numberNode;
    }
    else
    {
        reportError(ERROR_SYNTAX, lexer->pos, "Expect a number.");
        synchronize(lexer);
        return NULL;
    }
}