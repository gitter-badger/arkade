#include "lexer.h"

toml_lexer *create_lexer(vector *files) {
    toml_lexer *self = malloc(sizeof(*self));
    self->sourcefiles = files;
    return self;   
}

static void consume(toml_lexer *self) {
    // prepare yourself for the end...
    if (self->current_position + 1 >= self->input_length) {
        self->running = false;
    }

    self->current_character = self->input[++self->current_position];
}

void start_lexing(toml_lexer *self) {
    for (int i = 0; i < self->sourcefiles->size; i++) {
        sourcefile *file = get_vector_item(self->sourcefiles, i);
        
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

void eat_layout(toml_lexer *self) {
    while (self->current_character <= ' ' 
        || self->current_character == '\n'
        || self->current_character == '\t') {
        consume(self);
    }
}

void push_token(toml_lexer *self, int type) {
    int token_length = (self->current_position - self->initial_position) + 1;

    char *contents = malloc(sizeof(char) * token_length);
    if (type != TOKEN_EOF) {
        memcpy(contents, &self->input[self->initial_position], token_length);
        contents[token_length - 1] = 0;
    }

    token *tok = create_token(contents, self->current_sourcefile, 
        self->initial_position, self->current_position, type);
    push_back_item(self->tokens, tok);
}

void recognize_identifier(toml_lexer *self) {
    while (is_identifier(self->current_character)) {
        consume(self);
    }

    push_token(self, TOKEN_IDENTIFIER);
}

void recognize_digit(toml_lexer *self) {
    while (is_digit(self->current_character)) {
        consume(self);
    }

    if (self->current_character == '.') {
        while (is_digit(self->current_character)) {
            consume(self);
        }
        push_token(self, TOKEN_FLOATING);
    }
    else {
        push_token(self, TOKEN_WHOLE);
    }
}

void recognize_operator(toml_lexer *self) {
    consume(self);
    push_token(self, TOKEN_OPERATOR);
}

void recognize_separator(toml_lexer *self) {
    consume(self);
    push_token(self, TOKEN_SEPARATOR);
}

void get_next_token(toml_lexer *self) {
    eat_layout(self);
    self->initial_position = self->current_position;

    if (self->current_character == '\0') {
        self->running = false;
        return;
    }
    else if (is_identifier(self->current_character)) {
        recognize_identifier(self);
    }
    else if (is_digit(self->current_character)) {
        recognize_digit(self);
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
}

void destroy_lexer(toml_lexer *self) {
    free(self);
}