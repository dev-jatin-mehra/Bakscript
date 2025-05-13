#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "../include/token.h"
#include "../include/lexer.h"

Lexer init_lexer(char *source) /*Lexer Init*/
{
    Lexer lexer;
    lexer.source = source;
    lexer.pos = 0;
    return lexer;
}

char peek(Lexer *lexer)
{
    return lexer->source[lexer->pos];
}

char advance(Lexer *lexer)
{
    return lexer->source[lexer->pos++];
}

void skipWhiteSpace(Lexer *lexer)
{
    while (isspace(peek(lexer)))
    {
        advance(lexer);
    }
}

Token scanIdentifier(Lexer *lexer)
{
    char buffer[MAX_TOKEN_LENGTH];
    int length = 0;

    while (isalpha(peek(lexer)) && length < MAX_TOKEN_LENGTH - 1)
    {
        buffer[length++] = advance(lexer);
    }
    buffer[length] = '\0';

    // Check for Keyword
    if (strcmp(buffer, "when") == 0)
        return (Token){TOKEN_WHEN, strdup(buffer)};
    if (strcmp(buffer, "otherwise") == 0)
        return (Token){TOKEN_OTHERWISE, strdup(buffer)};
    if (strcmp(buffer, "repeat") == 0)
        return (Token){TOKEN_REPEAT, strdup(buffer)};
    if (strcmp(buffer, "aslong") == 0)
        return (Token){TOKEN_ASLONG, strdup(buffer)};
    if (strcmp(buffer, "make") == 0)
        return (Token){TOKEN_MAKE, strdup(buffer)};
    if (strcmp(buffer, "show") == 0)
        return (Token){TOKEN_SHOW, strdup(buffer)};
    if (strcmp(buffer, "num") == 0) // defining Number
        return (Token){TOKEN_NUM, strdup(buffer)};
    if (strcmp(buffer, "decimal") == 0) // defining float
        return (Token){TOKEN_DECIMAL, strdup(buffer)};
    if (strcmp(buffer, "text") == 0) // defining string
        return (Token){TOKEN_TEXT, strdup(buffer)};

    // Identifier
    return (Token){TOKEN_IDENTIFIER, strdup(buffer)};
}

Token scanNumber(Lexer *lexer)
{
    char buffer[MAX_TOKEN_LENGTH];
    int length = 0;

    while (isdigit(peek(lexer)) && length < MAX_TOKEN_LENGTH - 1)
    {
        buffer[length++] = advance(lexer);
    }

    if (peek(lexer) == '.')
    {
        buffer[length++] = advance(lexer);
        while (isdigit(peek(lexer)) && length < MAX_TOKEN_LENGTH - 1)
        {
            buffer[length++] = advance(lexer);
        }
        buffer[length] = '\0';
        return (Token){TOKEN_DECIMAL, strdup(buffer)};
    }
    buffer[length] = '\0';
    return (Token){TOKEN_NUMBER, strdup(buffer)};
}

Token scanString(Lexer *lexer)
{
    advance(lexer);
    char buffer[MAX_TOKEN_LENGTH];
    int length = 0;

    while (peek(lexer) != '"' && peek(lexer) != '\0' && length < MAX_TOKEN_LENGTH - 1)
    {
        buffer[length++] = advance(lexer);
    }

    advance(lexer);
    buffer[length] = '\0';
    return (Token){TOKEN_STRING, strdup(buffer)};
}

// Next Token
Token getNextToken(Lexer *lexer)
{
    skipWhiteSpace(lexer);

    char c = peek(lexer);
    if (isalpha(c))
        return scanIdentifier(lexer);
    if (isdigit(c))
        return scanNumber(lexer);
    if (c == '"')
        return scanString(lexer);

    switch (c)
    {
    case '=':
        advance(lexer);
        return (Token){TOKEN_EQUAL, "="};
    case '+':
        advance(lexer);
        return (Token){TOKEN_PLUS, "+"};
    case '-':
        advance(lexer);
        return (Token){TOKEN_MINUS, "-"};
    case '*':
        advance(lexer);
        return (Token){TOKEN_STAR, "*"};
    case '/':
        advance(lexer);
        return (Token){TOKEN_SLASH, "/"};
    case '>':
        advance(lexer);
        return (Token){TOKEN_GREATER, ">"};
    case '<':
        advance(lexer);
        return (Token){TOKEN_LESS, "<"};
    case ':':
        advance(lexer);
        return (Token){TOKEN_COLON, ":"};
    case '\0':
        return (Token){TOKEN_EOF, "EOF"};
    default:
        printf("Unexpected Chracter:%c\n", c);
        exit(1);
    }
}

void printTokens(char *source)
{
    Lexer lexer = init_lexer(source);
    Token token;

    do
    {
        token = getNextToken(&lexer);
        printf("Token: %d, Lexeme: %s\n", token.type, token.lexeme);
    } while (token.type != TOKEN_EOF);
}