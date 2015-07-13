#include <stdio.h>

#include "util.h"
#include "json_builder.h"
#include "arguments.h"
#include "load.h"

int main(int argc, char **argv) {
    // parse_arguments(argc, argv);
    sds hi = build_root_element("apple", "mango");
    sds fin = end_root_element(hi);

    printf("%s\n", fin);
    sdsfree(hi);
    sdsfree(fin);
    return 0;
}
