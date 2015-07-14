#include "actions.h"

void build_action(vector_t *arguments) {
    load_t *loader = load_ark_config();
    table_t *package = get_table(loader, "package");

    // check for a custom build method and use it if it
    // exists.
    char *build_method = get_string_contents("build", package);
    if (build_method) {
        // note we're using system calls, this isn't a good idea
        // at all, we're also just throwing in some random variable
        // that should probably be sanitized?
        // same applies for the one below
        system(build_method);
        sdsfree(build_method);
    }
    else {
        system("ark build src/*.ark");
    }

    destroy_loader(loader);
}