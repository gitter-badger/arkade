#ifndef __LEXER_H
#define __LEXER_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "vector.h"
#include "sourcefile.h"
#include "token.h"
#include "sds.h"

typedef struct {
    vector_t *sourcefiles;
    vector_t *tokens;
    void *current_sourcefile;

    char *input;
    bool running;
    int input_length;
    int initial_position;
    int current_position;
    char current_character;
} lexer_t;

lexer_t *create_lexer(vector_t *files);

void start_lexing(lexer_t *self);

void eat_layout(lexer_t *self);

void push_token(lexer_t *self, int type);

void recognize_identifier(lexer_t *self);

void recognize_digit(lexer_t *self);

void recognize_operator(lexer_t *self);

void recognize_separator(lexer_t *self);

void get_next_token(lexer_t *self);

void destroy_lexer(lexer_t *lexer);

static inline bool is_eoi(char c) {
    return c == '\0';
}

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
    return (is_letter_or_digit(c) || c == '_' || c == '.' || c == '-');
}

static inline bool is_operator(char c) {
    return (strchr("+-*/=><!~?:|&%^\"'", c) != 0); 
}

static inline bool is_separator(char c) {
    return (strchr(" ;,.`@(){}[] ", c) != 0); 
}

#endif // __LEXER_H