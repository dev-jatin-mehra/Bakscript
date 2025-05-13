#ifndef ERROR_H
#define ERROR_H

#include "lexer.h"

typedef enum
{
    ERROR_SYNTAX,
    ERROR_UNEXPECTED_TOKEN,
    ERROR_UNDEFINED_VARIBLE,
    ERROR_TYPE_MISMATCH
} ErrorType;

typedef struct
{
    ErrorType type;
    int position;
    char message[256];
} ParserError;

void initErrorModule();
void reportError(ErrorType type, int position, const char *message);
void displayErrors();
int hasErrors();
void clearErrors();

#endif