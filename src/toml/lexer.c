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
    }
}

static void consume(lexer_t *self) {
    if ((self->current_position > self->input_length) 
        || is_eoi(self->current_character)) {
        printf("EOI `%d`\n", self->current_character);
        return;
    }

    self->current_character = self->input[++self->current_position];
}

void eat_layout(lexer_t *self) {
    while ((self->current_character <= ' ' 
        || self->current_character == '\n'
        || self->current_character == '\t')
        && self->current_character != '\0') {
        consume(self);
    }
}

void push_token(lexer_t *self, int type) {
    sds contents = NULL;
    if (type != TOKEN_EOF) {
        int length = self->current_position - self->initial_position;
        contents = sdsnewlen(&self->input[self->initial_position], length);
    }
    else {
        contents = sdsnew("lol this is eof");
    }

    token_t *tok = create_token(contents, self->current_sourcefile, 
        self->initial_position, self->current_position, type);
    push_back_item(self->tokens, tok);

    printf("current: %s\n", contents);
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
        if (is_eoi(self->current_character)) {
            break;
        }
        consume(self);
    }
}

void recognize_string(lexer_t *self) {
    consume(self); // eat opening quote
    while (true) {
        char previous_char = self->current_character;
        consume(self); // eat contents of quote
        if (self->current_character == '"' && previous_char != '\\') break;
        if (is_eoi(self->current_character)) {
            printf("error: yo, unterminated string literal!\n");
        }
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
            consume(self);
            push_token(self, TOKEN_EOF);
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