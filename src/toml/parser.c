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

bare_key_t *parse_key(parser_t *parser) {
    return false;
}

array_table_t *parse_array_table(parser_t *parser) {
    if (!match_token(parser, "[", TOKEN_SEPARATOR, 0) &&
        !match_token(parser, "[", TOKEN_SEPARATOR, 1)) {
        return false;
    }

    // we already know what the tokens are
    consume(parser);
    consume(parser);

    if (match_token(parser, "", TOKEN_IDENTIFIER, 0)) {
        char *array_table_name = consume(parser)->contents;
        if (!match_token(parser, "]", TOKEN_SEPARATOR, 0) &&
            !match_token(parser, "]", TOKEN_SEPARATOR, 1)) {
            printf("error: expected closing brackets for `%s`\n", array_table_name);
            return false;    
        }
        consume(parser);
        consume(parser);

        vector_t *nodes = create_vector();
        array_table_t *array_table = create_array_table(array_table_name, nodes);
        return array_table;
    }

    return false;
}

table_t *parse_table(parser_t *parser) {
    // first token isn't a [
    // or the second token is (this means its an array table)
    if (!match_token(parser, "[", TOKEN_SEPARATOR, 0)
        || match_token(parser, "[", TOKEN_SEPARATOR, 1)) {
        return false;
    }

    consume(parser);

    if (match_token(parser, "", TOKEN_IDENTIFIER, 0)) {
        char *table_name = consume(parser)->contents;
        if (match_token(parser, "]", TOKEN_SEPARATOR, 0)) {
            consume(parser);

            vector_t *nodes = create_vector();
            table_t *table = create_table(table_name, nodes);
            return table;
        }
    }

    printf("error: expected closing square bracket\n");
    return false;
}

node_t *parse_node(parser_t *parser) {
    table_t *table = parse_table(parser);
    if (table) {
        return create_node(TABLE_NODE, table);
    }

    array_table_t *array_table = parse_array_table(parser);
    if (array_table) {
        return create_node(ARRAY_TABLE_NODE, array_table);
    }

    return false;
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
            node_t *node = parse_node(parser);
            if (node) {
                push_back_item(parser->ast, node);
                printf("pushed back node!\n");
            }
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