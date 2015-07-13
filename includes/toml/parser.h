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

void start_parsing(parser_t *parser);

token_t *peek_ahead(parser_t *parser, int offset);

bool match_token(parser_t *parser, char *contents, int type, int offset);

void destroy_parser(parser_t *parser);

#endif // __PARSER_H