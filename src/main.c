#include <stdio.h>

#include "arguments.h"
#include "load.h"

int main(int argc, char **argv) {
    parse_arguments(argc, argv);

    load_t *loader = create_loader(create_sourcefile("toml_test/test.toml"));

    table_t *package = get_table(loader, "package");

    char *name = get_string("name", package);
    printf("package name %s\n", name);

    destroy_loader(loader);

    return 0;
}