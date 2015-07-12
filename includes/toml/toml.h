#ifndef __TOML_H
#define __TOML_H

#include "lexer.h"
#include "vector.h"

typedef struct {
    toml_lexer *lex;
    vector *files;
} toml;

toml *parse_toml(vector *files);

void destroy_toml(toml *toml);

#endif // __TOML_H