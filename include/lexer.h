#ifndef LEXER_H
#include "./token.h"
#define LEXER_H
#define MAX_TOKEN_LENGTH 25
#define strdup _strdup

typedef struct
{
    char *source;
    int pos;
} Lexer;

Lexer init_lexer(char *src);
char peek(Lexer *lexer);
char advance(Lexer *lexer);
void skipWhiteSpace(Lexer *lexer);
Token scanIdentifier(Lexer *lexer);
Token scanNumber(Lexer *lexer);
Token scanString(Lexer *lexer);
Token getNextToken(Lexer *lexer);
void printTokens(char *source);

#endif