#ifndef __AST_H
#define __AST_H

// LITERAL

typedef enum {
    INTEGER_LITERAL,
    DOUBLE_LITERAL,
    STRING_LITERAL,
    CHARACTER_LITERAL,
    BOOLEAN_LITERAL
} literal_type;

typedef struct {
    literal_type kind;
    char *value;
} literal_t;

// EXPRESSIONS

typedef struct {
    vector_t *values;
    int value_count;
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
    void *data;
} expr_t;

// TOP LEVEL NODES

/*
    This represents a key/value in TOML, e.g:
    key = "value"
*/
typedef struct {
    char *key;
    value_t *value;
} key_t;

/*
    This represents a table in TOML, e.g:

    [table]
    key = "my value"
    a = 123
*/
typedef struct {
    char *name;
    vector_t *keys;
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
    TABLE_NODE,
    ARRAY_TABLE_NODE,
    KEY_NODE
} node_type;

/*
    This is a top level node, it can either be
    a table, array of tables, or a key
*/
typedef struct {
    node_type kind;
    void *data;
} node_t;

#endif // __AST_H