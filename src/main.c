#include <stdio.h>

#include "arguments.h"
#include "toml.h"

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
        destroy_sourcefile(get_vector_item(files, i));
    }
    destroy_vector(files);

    return 0;
}