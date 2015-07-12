#include <stdio.h>

#include "arguments.h"
#include "toml.h"

int main(int argc, char **argv) {
    parse_arguments(argc, argv);

    // make some files to test
    vector *files = create_vector();
    push_back_item(files, create_sourcefile("toml_test/test.toml"));

    // parse that shit
    toml* toml = parse_toml();
    start_parsing_toml(toml, files);
    destroy_toml(toml);

    // cleanup files
    for (int i = 0; i < files->size; i++) {
        // print tokens to test
        sourcefile *file = get_vector_item(files, i);
        for (int i = 0; i < file->tokens->size; i++) {
            token *tok = get_vector_item(file->tokens, i);
            printf("%d: %s\n", tok->type, tok->contents);
        }

        destroy_sourcefile(file);
    }
    destroy_vector(files);

    return 0;
}