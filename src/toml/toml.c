#include "toml.h"

toml_t *create_toml() {
    return malloc(sizeof(toml_t));
}

void start_parsing_toml(toml_t *toml, vector_t *files) {
    toml->files = files;

    toml->lex = create_lexer(toml->files);
    toml->parser = create_parser(toml->files);
    
    start_lexing(toml->lex);
    start_parsing(toml->parser);
}

void destroy_toml(toml_t *toml) {
    destroy_lexer(toml->lex);
    destroy_parser(toml->parser);
    free(toml);
}