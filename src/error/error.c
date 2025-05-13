#include "../../include/error.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_ERRORS 50

static ParserError errors[MAX_ERRORS];
static int errorCount = 0;

void initErrorModule()
{
    errorCount = 0;
}

void reportError(ErrorType type, int position, const char *message)
{
    if (errorCount < MAX_ERRORS)
    {
        errors[errorCount].type = type;
        errors[errorCount].position = position;
        strncpy(errors[errorCount].message, message, 255);
        errors[errorCount].message[255] = '\0';
        errorCount++;
    }
}

void displayErrors()
{
    printf("\n--- Parser Errors ---\n");
    if (errorCount == 0)
    {
        printf("No errors found!\n");
        return;
    }
    for (int i = 0; i < errorCount; i++)
    {
        printf("[%d] Error at position %d: %s\n", i + 1, errors[i].position, errors[i].message);
    }
    printf("\n Total Errors: %d\n", errorCount);
}

int hasErrors()
{
    return errorCount > 0;
}

void clearErrors()
{
    errorCount = 0;
}