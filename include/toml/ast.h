#ifndef __AST_H
#define __AST_H

#include <stdlib.h>

#include "hashmap.h"
#include "vector.h"

// LITERAL

typedef enum {
    NUMBER_LITERAL,
    STRING_LITERAL,
    CHARACTER_LITERAL,
    BOOLEAN_TRUE_LITERAL,
    BOOLEAN_FALSE_LITERAL
} literal_type;

typedef struct {
    literal_type kind;
    char *value;
} literal_t;

// EXPRESSIONS

typedef struct {
    vector_t *values;
} array_t;

typedef struct {
    char *name;
    vector_t *values;
} inline_table_t;

typedef enum {
    LITERAL_EXPR,
    ARRAY_EXPR,
    TABLE_EXPR,
} expr_type;

typedef struct {
    expr_type kind;
    literal_t *literal_expr;
    array_t *array_expr;
    inline_table_t *table_expr;
} expr_t;

// TOP LEVEL NODES

/*
    This represents a key/value in TOML, e.g:
    key = "value"
*/
typedef struct {
    char *name;
    expr_t *value;
} bare_key_t;

/*
    This represents a table in TOML, e.g:

    [table]
    key = "my value"
    a = 123
*/
typedef struct {
    char *name;
    map_t *nodes;
} table_t;

/*
    This represents an array of tables in TOML, e.g:

    [[table]]
    a = 1

    [[table]]
    a = 2

    [[table]]
    a = 3
*/
typedef struct {
    char *name;
    vector_t *nodes;
} array_table_t;

typedef enum {
    TABLE_NODE = 0,
    ARRAY_TABLE_NODE,
    BARE_KEY_NODE
} node_type;

/*
    This is a top level node, it can either be
    a table, array of tables, or a key
*/
typedef struct {
    node_type kind;
    array_table_t *array_table;
    table_t *table;
    bare_key_t *bare_key;
} node_t;

// NODE UTIL

literal_t *create_literal(literal_type kind, char *value);

void destroy_literal(literal_t *lit);

array_t *create_array(vector_t *values);

void destroy_array(array_t *array);

inline_table_t *create_inline_table(char *name, vector_t *values);

void destroy_inline_table(inline_table_t *table);

expr_t *create_expr(expr_type kind);

void destroy_expr(expr_t *expr);

bare_key_t *create_key(char *name, expr_t *value);

void destroy_key(bare_key_t *key);

table_t *create_table(char *name);

void destroy_table(table_t *table);

array_table_t *create_array_table(char *name, vector_t *nodes);

void destroy_array_table(array_table_t *array);

node_t *create_node();

void destroy_node(node_t *node);

#endif // __AST_H