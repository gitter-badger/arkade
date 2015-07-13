#include <stdio.h>

#include "util.h"
#include "json_builder.h"
#include "arguments.h"
#include "load.h"

int main(int argc, char **argv) {
    parse_arguments(argc, argv);
    sds hi = sdsnew("");
    hi = build_root_element("negro");
    hi = end_root_element(hi);

    printf("%s\n", hi);
    sdsfree(hi);
    return 0;
}
