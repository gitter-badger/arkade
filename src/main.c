#include <stdio.h>

#include "util.h"
#include "json_builder.h"
#include "arguments.h"
#include "load.h"

int main(int argc, char **argv) {
    parse_arguments(argc, argv);
    sds hi = build_root_element("apple", "mango");
    sds fruit_array = build_new_array("fruits", "apple", "mango", "plum", false);
    hi = sdscat(hi, fruit_array);
    sds fin = end_root_element(hi);

    printf("%s\n", fin);
    // printf("%s\n", fruit_array);
    sdsfree(hi);
    sdsfree(fin);
    sdsfree(fruit_array);
    return 0;
}
