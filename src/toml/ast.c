#include "ast.h"

literal_t *create_literal(literal_type kind, char *value) {
    literal_t *lit = malloc(sizeof(*lit));
    lit->kind = kind;
    lit->value = value;
    return lit;
}

void destroy_literal(literal_t *lit) {
    free(lit);
}

array_t *create_array(vector_t *values) {
    array_t *array = malloc(sizeof(*array));
    array->values = values;
    return array;
}

void destroy_array(array_t *array) {
    for (int i = 0; i < array->values->size; i++) {
        destroy_expr(get_vector_item(array->values, i));
    }
    destroy_vector(array->values);
    free(array);
}

inline_table_t *create_inline_table(char *name, vector_t *values) {
    inline_table_t *table = malloc(sizeof(*table));
    table->name = name;
    table->values = values;
    return table;
}

void destroy_inline_table(inline_table_t *table) {
    for (int i = 0; i < table->values->size; i++) {
        destroy_expr(get_vector_item(table->values, i));
    }
    destroy_vector(table->values);
    free(table);
}

expr_t *create_expr(expr_type kind) {
    expr_t *expr = malloc(sizeof(*expr));
    expr->kind = kind;
    return expr;
}

void destroy_expr(expr_t *expr) {
    switch (expr->kind) {
        case LITERAL_EXPR: destroy_literal(expr->literal_expr); break;
        case ARRAY_EXPR: destroy_array(expr->array_expr); break;
        case TABLE_EXPR: destroy_inline_table(expr->table_expr); break;
        default: printf("error: attempting to destroy unknown expression\n"); break;
    }
    free(expr);
}

bare_key_t *create_key(char *name, expr_t *value) {
    bare_key_t *key = malloc(sizeof(*key));
    key->name = name;
    key->value = value;
    return key;
}

void destroy_key(bare_key_t *key) {
    destroy_expr(key->value);
    free(key);
}

table_t *create_table(char *name) {
    table_t *table = malloc(sizeof(*table));
    table->name = name;
    table->nodes = hashmap_new();
    return table;
}

int destroy_table_nodes(any_t data, any_t item) {
    destroy_node(item);
    return MAP_OK;
}

void destroy_table(table_t *table) {
    hashmap_iterate(table->nodes, destroy_table_nodes, NULL);
    hashmap_free(table->nodes);
    free(table);
}

array_table_t *create_array_table(char *name, vector_t *nodes) {
    array_table_t *array = malloc(sizeof(*array));
    array->name = name;
    array->nodes = nodes;
    return array;
}

void destroy_array_table(array_table_t *array) {
    for (int i = 0; i < array->nodes->size; i++) {
        destroy_node(get_vector_item(array->nodes, i));
    }
    free(array);
}

node_t *create_node() {
    return malloc(sizeof(node_t));
}

void destroy_node(node_t *node) {
    switch (node->kind) {
        case TABLE_NODE: destroy_table(node->table); break;
        case ARRAY_TABLE_NODE: destroy_array_table(node->array_table); break;
        case BARE_KEY_NODE: destroy_key(node->bare_key); break;
    }
    free(node);
}
