#include "sourcefile.h"
#include "token.h"

__attribute__((unused)) static const char* TOKEN_TYPE[] = {
    "token_identifier",
    "token_whole",
    "token_floating",
    "token_operator",
    "token_separator",
    "token_string",
    "token_eof"
};

__attribute__((unused)) static const char* NODE_TYPE[] = {
    "table_node",
    "array_table_node",
    "key_node"
};

sourcefile_t *create_sourcefile(char *location) {
    sourcefile_t *self = malloc(sizeof(*self));
    self->location = location;
    self->name = basename(location);
    self->tokens = create_vector();
    self->ast = hashmap_new();
    self->contents = read_file(self);
    if (!self->contents) {
        return false;
    }
    return self;
}

char *read_file(sourcefile_t *file) {
    FILE *file_handle = fopen(file->location, "r");
    if (!file_handle) {
        perror("fopen: could not read file");
        return false;
    }

    if (fseek(file_handle, 0, SEEK_END)) {
        perror("fseek: could not set file index");
        return false;
    }

    long file_size = ftell(file_handle);
    if (file_size == -1) {
        perror("ftell: could not read filesize");
        return false;
    }

    char *contents = malloc(sizeof(*contents) * (file_size + 1));
    if (!contents) {
        perror("malloc: could not allocate memory for file contents");
        return false;
    }

    if (fseek(file_handle, 0, SEEK_SET)) {
        perror("fseek: could not reset file index");
        return false;
    }

    size_t file_length = fread(contents, sizeof(char), file_size, file_handle);
    if (!file_length) {
        printf("file `%s` is empty\n", file->location);
        free(contents);
        return false;
    }

    contents[file_length] = '\0';

    fclose(file_handle);
    return contents;
}

int destroy_nodes(any_t passed_data, any_t item) {
    destroy_node(item);
    return MAP_OK;
}

void destroy_sourcefile(sourcefile_t *self) {
    free(self->contents);

    for (int i = 0; i < self->tokens->size; i++) {
        token_t *token = get_vector_item(self->tokens, i);
        destroy_token(token);
    }
    destroy_vector(self->tokens);

    hashmap_iterate(self->ast, destroy_nodes, NULL);
    hashmap_free(self->ast);

    free(self);
}
