#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// TODO: Include local header files

// TODO: Use all unused parameters and remove this temporary definition
// Helps eliminating warning C4100: 'error': unreferenced formal parameter

//////////////////////////////////////////////////////////////////////////////
// Dummy calc module

// TODO: Move to a separate module 'calc'
typedef enum
{
    ERR_OK,
    ERR_NOT_ENOUGH_MEMORY,
    ERR_BRACKET,
    ERR_WRONG_EXPRESSION,
  // TODO: Add your own error codes
} error_t;
error_t ReportError(error_t error);
// TODO: Move to a separate module 'calc'
char const* GetErrorString(error_t error)
{
    // TODO: Find the corresponding error description
    switch (error) {
        default:
            return "UNDEFINED";
    }
}

// TODO: Move to a separate module 'calc'
double Calculate(char const* expression, error_t* lastError)
{
    double result;
    result = 4.0;
    return result;
}

//////////////////////////////////////////////////////////////////////////////
// UI functions
int NeedCalculate(char const*);

//TODO: Move code to functions
char* ReadLine(FILE* in, error_t* lastError)
{
    char* buffer = NULL;
    char* line = (char*) malloc(sizeof(char));
    int i = 0;
    line[i] = (char)fgetc(in);
    if (line[i] == EOF)
    {
        free(line);
        return NULL;
    }
    while ((line[i] != '\n'))
    {
        if (line[i] == EOF) break;
        i++;
        buffer = (char*) realloc(line, sizeof(char) * (i + 1));
        if (buffer == NULL)
        {
            *lastError = ERR_NOT_ENOUGH_MEMORY;
            return line;
        }
        else line = buffer;
        line[i] = (char)fgetc(in);
    }
    line[i] = '\0';
    if ((NeedCalculate(line)) && ((line[i-1] == '+' || line[i-1] == '-') || (line[i-1] == '*' || line[i-1] == '/') || (line[i-1] == '(' || line[i-1] == ')')) && (line[i - 1]!=')'))
            *lastError = ERR_WRONG_EXPRESSION;
    return line;
}


int NeedCalculate(char const *line) {
    int i = 0;
    for(i; ((line[i] != '\0') && !(((line[i] == '+' || line[i] == '-') || (line[i] == '*' || line[i] == '/') || (line[i] == '(' || line[i] == ')'))) && !(isalnum(line[i]))); i++);
    if (line[i] == '\0') return 0;
    if (line[i] == '/' && line[i + 1] == '/') return 0;
    for (i; line[i] != '\0'; i++) if (((line[i] == '+' || line[i] == '-') || (line[i] == '*' || line[i] == '/') || (line[i] == '(' || line[i] == ')'))||isalnum(line[i])) return 1;
    return 0;
}

error_t ReportError(error_t error)
{
    printf("ERROR: %s\n", GetErrorString(error));
    return error;
}

void ProcessLine(char const* line, error_t *lastError)
{
    if (!NeedCalculate(line))
    {
        puts(line);
        return;
    }
    printf("%s == ", line);
    double result = Calculate(line, lastError);
    if (*lastError == ERR_OK) printf("%lg\n", result);
    else{
        ReportError(*lastError);
        *lastError = ERR_OK;
    }
    *lastError = ERR_OK;
}

int main(int argc, char const* argv[])
{
    FILE* in = stdin;
    char* line = NULL;
    error_t lastError = ERR_OK;
    // Choose an input source
    if (argc > 1 && (in = fopen(argv[1], "r")) == NULL || argc > 2)
    {
        printf("ERROR: Cannot open file '%s'", argv[1]);
        return -1;
    }
    else if (argc == 2) {
        in = freopen(argv[1], "r", stdin);
        if (in == NULL) {
            printf("ERROR: Cannot open file");
            return -1;
        }
    }
    // Process the data line by line
    while ((line = ReadLine(in, &lastError)) != NULL)
    {
        ProcessLine(line, &lastError);
        free(line);
    }

    // Clean up
    if (in != stdin) fclose(in);
    return 0;
}
