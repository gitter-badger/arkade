#ifndef __TOML_H
#define __TOML_H

#include "lexer.h"
#include "vector.h"

typedef struct {
    lexer_t *lex;
    vector_t *files;
} toml_t;

toml_t *create_toml();

void start_parsing_toml(toml_t *toml, vector_t *files);

void destroy_toml(toml_t *toml);

#endif // __TOML_H