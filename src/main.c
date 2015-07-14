#include <stdio.h>

#include "util.h"
#include "json_builder.h"
#include "arguments.h"
#include "json_builder.h"
#include "load.h"

int main(int argc, char **argv) {
    // parse_arguments(argc, argv);

    json_builder_t *builder = create_json_builder();
    
    json_open_object(builder);
    
    json_pair(builder, "name");
    json_string(builder, "arkade-test");

    json_pair(builder, "desc");
    json_boolean(builder, "the greatest repository ever");

    json_pair(builder, "private");
    json_boolean(builder, true);

    json_pair(builder, "stars");
    json_number(builder, "380");

    json_pair(builder, "authors");
    json_array(builder, "\"felix angell\"", false);

    json_close_object(builder);

    destroy_json_builder(builder);

    return 0;
}
