#include <stdio.h>

#include "arguments.h"
#include "toml.h"

static const char* TOKEN_TYPE[] = {
    "TOKEN_IDENTIFIER",
    "TOKEN_WHOLE",
    "TOKEN_FLOATING",
    "TOKEN_OPERATOR",
    "TOKEN_SEPARATOR",
    "TOKEN_STRING",
    "TOKEN_EOF"
};

int main(int argc, char **argv) {
    parse_arguments(argc, argv);

    // make some files to test
    vector_t *files = create_vector();
    push_back_item(files, create_sourcefile("toml_test/test.toml"));

    // parse that shit
    toml_t* toml = create_toml();
    start_parsing_toml(toml, files);
    destroy_toml(toml);

    // cleanup files
    for (int i = 0; i < files->size; i++) {
        // print tokens to test
        sourcefile_t *file = get_vector_item(files, i);
        for (int i = 0; i < file->tokens->size; i++) {
            token_t *tok = get_vector_item(file->tokens, i);
            printf("%s: %s\n", TOKEN_TYPE[tok->type], tok->contents);
        }

        destroy_sourcefile(file);
    }
    destroy_vector(files);

    return 0;
}