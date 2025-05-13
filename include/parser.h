<<<<<<< HEAD
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

void advanceParser(Lexer *lexer);
int match(Lexer *lexer, TK_TYPE type);
int expect(Lexer *lexer, TK_TYPE type);
int isKeyword(TK_TYPE type);
void synchronize(Lexer *lexer);

=======
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

void advanceParser(Lexer *lexer);
int match(Lexer *lexer, TK_TYPE type);
int expect(Lexer *lexer, TK_TYPE type);
int isKeyword(TK_TYPE type);

>>>>>>> 81ea01b72b5b3723a66137b6bd85795578402968
#endif