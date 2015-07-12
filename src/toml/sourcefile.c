#include "sourcefile.h"
#include "token.h"

sourcefile_t *create_sourcefile(char *location) {
    sourcefile_t *self = malloc(sizeof(*self));
    self->location = location;
    self->name = basename(location);
    self->tokens = create_vector();
    self->ast = create_vector();
    self->contents = read_file(self);
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

void destroy_sourcefile(sourcefile_t *self) {
    free(self->contents);

    destroy_vector(self->ast);

    for (int i = 0; i < self->tokens->size; i++) {
        token_t *tok = get_vector_item(self->tokens, i);
        free(tok);
    }
    destroy_vector(self->tokens);
    free(self);
}