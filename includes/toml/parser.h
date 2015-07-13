#ifndef __PARSER_H
#define __PARSER_H

#include <string.h>

#include "sourcefile.h"
#include "vector.h"
#include "token.h"
#include "ast.h"

typedef struct {
    vector_t *files;
    vector_t *tokens;
    vector_t *ast;
    bool running;   
    int token_index;
    sourcefile_t *current_sourcefile; 
} parser_t;

parser_t *create_parser(vector_t *files);

literal_t *parse_literal(parser_t *parser);

bare_key_t *parse_key(parser_t *parser);

array_table_t *parse_array_table(parser_t *parser);

vector_t *parse_key_block(parser_t *parser);

table_t *parse_table(parser_t *parser);

node_t *parse_node(parser_t *parser);

void start_parsing(parser_t *parser);

token_t *peek_ahead(parser_t *parser, int offset);

bool match_token(parser_t *parser, char *contents, int type, int offset);

void destroy_parser(parser_t *parser);

#endif // __PARSER_H