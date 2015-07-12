#include "toml.h"

toml *parse_toml() {
    return malloc(sizeof(toml));
}

void start_parsing_toml(toml *toml, vector *files) {
    toml->files = files;
    toml->lex = create_lexer(toml->files);
    start_lexing(toml->lex);
}

void destroy_toml(toml *toml) {
    destroy_lexer(toml->lex);
    free(toml);
}