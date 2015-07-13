#include "parser.h"

parser_t *create_parser(vector_t *files) {
    parser_t *parser = malloc(sizeof(*parser));
    parser->files = files;
    return parser;
}

static token_t *consume(parser_t *parser) {
    token_t *current = peek_ahead(parser, 0);
    parser->token_index++;
    return current;
}

void start_parsing(parser_t *parser) {
    for (int i = 0; i < parser->files->size; i++) {
        parser->current_sourcefile = get_vector_item(parser->files, i);

        // reset everything
        parser->tokens = parser->current_sourcefile->tokens;
        parser->ast = parser->current_sourcefile->ast;
        parser->running = true;
        parser->token_index = 0;

        // parse the file tokens to an ast!
        // keep going till we hit EOF token
        while (!match_token(parser, "", TOKEN_EOF, 0) && parser->running) {
            consume(parser);
        }
    }
}

token_t *peek_ahead(parser_t *parser, int offset) {
    if (parser->token_index > parser->token_index + offset) {
        printf("error: peeking to far %d > %d + %d\n", parser->token_index, parser->token_index, offset);
        return false;
    }
    return get_vector_item(parser->tokens, parser->token_index + offset);
}

bool match_token(parser_t *parser, char *contents, int type, int offset) {
    token_t *peeked_token = peek_ahead(parser, offset);
    if (!strcmp(contents, "")) {
        return type == peeked_token->type;
    }
    return type == peeked_token->type && !strcmp(peeked_token->contents, contents);
}

void destroy_parser(parser_t *parser) {
    free(parser);
}