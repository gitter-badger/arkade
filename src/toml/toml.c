#include "toml.h"

toml_t *create_toml() {
    return malloc(sizeof(toml_t));
}

void start_parsing_toml(toml_t *toml, vector_t *files) {
    toml->files = files;
    toml->lex = create_lexer(toml->files);
    start_lexing(toml->lex);
}

void destroy_toml(toml_t *toml) {
    destroy_lexer(toml->lex);
    free(toml);
}