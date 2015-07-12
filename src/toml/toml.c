#include "toml.h"

toml *parse_toml(vector *files) {
    toml *toml = malloc(sizeof(*toml));
    toml->files = files;
    return toml;
}

void destroy_toml(toml *toml) {
    for (int i = 0; i < toml->files->size; i++) {
        destroy_sourcefile(get_vector_item(toml->files, i));
    }
    destroy_vector(toml->files);
    free(toml);
}