#include <stdio.h>

#include "util.h"
#include "json_builder.h"
#include "arguments.h"
#include "json_builder.h"
#include "process_handler.h"
#include "load.h"

/*
    Just leave this in because I'm lazy,
    this is for when I want to test the TOML
    parser.
*/
void toml_test() {
    vector_t *files = create_vector();
    push_back_item(files, create_sourcefile("toml_test/realistic_test.toml"));

    toml_t *toml = create_toml();
    start_parsing_toml(toml, files);
    destroy_toml(toml);

    destroy_vector(files);
}

int main(int argc, char **argv) {
    parse_arguments(argc, argv);
    return 0;
}
