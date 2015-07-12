#include "lexer.h"

lexer_t *create_lexer(vector_t *files) {
    lexer_t *self = malloc(sizeof(*self));
    self->sourcefiles = files;
    return self;   
}

void start_lexing(lexer_t *self) {
    for (int i = 0; i < self->sourcefiles->size; i++) {
        sourcefile_t *file = get_vector_item(self->sourcefiles, i);
        
        // a lot of shit needs to be reset...
        self->tokens = file->tokens;
        self->input = file->contents;
        self->input_length = (int) strlen(self->input);
        self->current_character = self->input[self->current_position];
        self->current_sourcefile = file;
        self->running = true;
        self->initial_position = 0;
        self->current_position = 0;

        while (self->running) {
            get_next_token(self);
        }

        // once we're done, add an EOF token
        push_token(self, TOKEN_EOF);
    }
}

void consume(lexer_t *self) {
    if (self->current_position + 1 >= self->input_length) {
        self->running = false;
    }
    self->current_character = self->input[++self->current_position];
}

void eat_layout(lexer_t *self) {
    while (self->current_character <= ' ' 
        || self->current_character == '\n'
        || self->current_character == '\t') {
        consume(self);
    }
}

void push_token(lexer_t *self, int type) {
    int token_length = (self->current_position - self->initial_position) + 1;

    char *contents = malloc(sizeof(char) * token_length);
    if (type != TOKEN_EOF) {
        memcpy(contents, &self->input[self->initial_position], token_length);
        contents[token_length - 1] = 0;
    }

    token_t *tok = create_token(contents, self->current_sourcefile, 
        self->initial_position, self->current_position, type);
    push_back_item(self->tokens, tok);
}

void recognize_identifier(lexer_t *self) {
    while (is_identifier(self->current_character)) {
        consume(self);
    }

    push_token(self, TOKEN_IDENTIFIER);
}

void recognize_digit(lexer_t *self) {
    while (is_digit(self->current_character)) {
        consume(self);
    }

    if (self->current_character == '.') {
        consume(self);
        while (is_digit(self->current_character)) {
            consume(self);
        }
        push_token(self, TOKEN_FLOATING);
    }
    else {
        push_token(self, TOKEN_WHOLE);
    }
}

void recognize_operator(lexer_t *self) {
    consume(self);
    push_token(self, TOKEN_OPERATOR);
}

void recognize_separator(lexer_t *self) {
    consume(self);
    push_token(self, TOKEN_SEPARATOR);
}

void recognize_comment(lexer_t *self) {
    // eat all characters till the newline
    while (self->current_character != '\n') {
        consume(self);
    }
}

void recognize_string(lexer_t *self) {
    consume(self); // eat opening quote
    while (self->current_character != '"') {
        consume(self); // eat contents of quote
    }
    consume(self); // eat closing quote

    push_token(self, TOKEN_STRING);
}

void get_next_token(lexer_t *self) {
    eat_layout(self);
    self->initial_position = self->current_position;

    switch (self->current_character) {
        case '#': recognize_comment(self); break;
        case '"': recognize_string(self); break;
        case '\0': { // EOF 
            self->running = false;
            return;
        }
        default: {
            if (is_digit(self->current_character)) {
                recognize_digit(self);
            }
            else if (is_identifier(self->current_character)) {
                recognize_identifier(self);
            }
            else if (is_operator(self->current_character)) {
                recognize_operator(self);
            }
            else if (is_separator(self->current_character)) {
                recognize_separator(self);
            }
            else {
                printf("WHAT YEAR IS IT? %c\n", self->current_character);
            }
            break;
        }
    }
}

void destroy_lexer(lexer_t *self) {
    free(self);
}