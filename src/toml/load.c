#include "load.h"

load_t *create_loader(sourcefile_t *file) {
    load_t *loader = malloc(sizeof(*loader));
    loader->file = file;
    loader->files = create_vector();

    loader->toml = create_toml();
    push_back_item(loader->files, file);
    start_parsing_toml(loader->toml, loader->files);

    return loader;
}

table_t *get_table(load_t *loader, char *name) {
    table_t *table = NULL;
    if (hashmap_get(loader->file->ast, name, (void**) &table) == MAP_OK) {
        return table;
    }
    return false;
}

array_t *get_array(char *name, table_t *table) {
    array_t *array = NULL;
    if (hashmap_get(table->nodes, name, (void**) &array) == MAP_OK) {
        return array;
    }
    return false;
}

expr_t *get_array_value_expr(int index, array_t *array) {
    if (index >= array->values->size || index < 0) {
        printf("error: array value out of bounds, %d (cap is %d)\n", index, array->values->size);
        return false;
    }

    expr_t *expr = get_vector_item(array->values, index);
    if (expr) {
        return expr;
    }

    printf("error: no value at %d\n", index);
    return false;
}

char *get_array_value(int index, array_t *array) {
    expr_t *expr = get_array_value_expr(index, array);
    if (expr->kind == LITERAL_EXPR) {
        return expr->literal_expr->value;
    }

    printf("error: fuck you\n");
    return false;
}

char *get_string(char *name, table_t *table) {
    bare_key_t *bare_key = NULL;
    if (hashmap_get(table->nodes, name, (void**) &bare_key) == MAP_OK) {
        return bare_key->value->literal_expr->value;
    }
    return false;
}

// TODO better name?
// this differs from get_string as it returns the string
// without the quotes surrounding it
// IT MUST BE FREED! this is kind of nasty but it works for now
char *get_string_contents(char *name, table_t *table) {
    bare_key_t *bare_key = NULL;
    if (hashmap_get(table->nodes, name, (void**) &bare_key) == MAP_OK) {
        char *value = bare_key->value->literal_expr->value;
        int length = sdslen(value) - 2;
        char *result = sdsnewlen(&value[1], length);
        return result;
    }
    return false;
}

void destroy_loader(load_t *loader) {
    destroy_toml(loader->toml);
    destroy_sourcefile(loader->file);
    destroy_vector(loader->files);
    free(loader); // haha get it?
}
