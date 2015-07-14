#ifndef __LOAD_H
#define __LOAD_H

#include "sourcefile.h"
#include "toml.h"
#include "vector.h"

/*
    this is for loading values
    from a toml file.
*/
typedef struct {
    toml_t *toml;
    sourcefile_t *file;
    vector_t *files;
} load_t;

load_t *create_loader(sourcefile_t *file);

table_t *get_table(load_t *loader, char *name);

array_t *get_array(char *name, table_t *table);

expr_t *get_array_value_expr(int index, array_t *array);

char *get_array_value(int index, array_t *array);

char *get_string(char *name, table_t *table);

char *get_string_contents(char *name, table_t *table);

void destroy_loader(load_t *loader);

#endif // __LOAD_H