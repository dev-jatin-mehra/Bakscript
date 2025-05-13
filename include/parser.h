#ifndef PARSER_H
#define PARSER_H

#include "./lexer.h"
#include "./ast.h"
#include "./token.h"

ASTNode *parseProgram(Lexer *lexer);
ASTNode *parseStatement(Lexer *lexer);
ASTNode *parseAssignment(Lexer *lexer);
ASTNode *parsePrintStatement(Lexer *lexer);
ASTNode *parseExpression(Lexer *lexer);
ASTNode *parseNumber(Lexer *lexer);
ASTNode *parseVariableDeclaration(Lexer *lexer);

Token advanceParser(Lexer *lexer);
int match(Lexer *lexer, TK_TYPE type);
void expect(Lexer *lexer, TK_TYPE type, const char *errorMessage);
int isKeyword(TK_TYPE type);
void synchronize(Lexer *lexer);

#endif