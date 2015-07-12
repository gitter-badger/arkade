#ifndef __TOKEN_H
#define __TOKEN_H

#include <stdlib.h>

#include "sourcefile.h"

typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_WHOLE,
    TOKEN_FLOATING,
    TOKEN_OPERATOR,
    TOKEN_SEPARATOR,
    TOKEN_STRING,
    TOKEN_EOF
} token_type;

typedef struct {
    char *contents;
    sourcefile *owner;
    int start, end;
    int type;
} token;

token *create_token(char *contents, sourcefile *owner, int start, int end, int token_type);

void destroy_token(token *self);

#endif // __TOKEN_H