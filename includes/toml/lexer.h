#ifndef __LEXER_H
#define __LEXER_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "vector.h"
#include "sourcefile.h"
#include "token.h"

typedef struct {
    vector *sourcefiles;
    vector *tokens;
    void *current_sourcefile;

    char *input;
    bool running;
    int input_length;
    int initial_position;
    int current_position;
    char current_character;
} toml_lexer;

toml_lexer *create_lexer();

void start_lexing(toml_lexer *self);

void eat_layout(toml_lexer *self);

void push_token(toml_lexer *self, int type);

void recognize_identifier(toml_lexer *self);

void recognize_digit(toml_lexer *self);

void recognize_operator(toml_lexer *self);

void recognize_separator(toml_lexer *self);

void get_next_token(toml_lexer *self);

void destroy_lexer(toml_lexer *lexer);

static inline bool is_letter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

static inline bool is_digit(char c) {
    return (c >= '0' && c <= '9');
}

static inline bool is_letter_or_digit(char c) {
    return is_letter(c) || is_digit(c);
}

static inline bool is_identifier(char c) {
    return (is_letter_or_digit(c) || c == '_');
}

static inline bool is_operator(char c) {
    return (strchr("+-*/=><!~?:|&%^\"'", c) != 0); 
}

static inline bool is_separator(char c) {
    return (strchr(" ;,.`@(){}[] ", c) != 0); 
}

#endif // __LEXER_H