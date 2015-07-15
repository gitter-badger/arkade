#include "actions.h"

static const char* help_template = {
    "usage: arkade <command> [<args> ...]"
    "\n"
    "\n"
    "commands:"
    "\n"
};

int print_command(any_t data, any_t item) {
    command_t *command = item;

    // windows is shit and doesn't
    // support magical bolding
    #ifdef _WIN32
    printf("    %-10s %s\n", command->name, command->desc);
    #else
    printf("    \033[1m%-10s\033[0m %s\n", command->name, command->desc);
    #endif

    return MAP_OK;
}

void help_action(vector_t *arguments) {
    // basically I did a little hack where the hashmap
    // is the first argument on here
    map_t *commands = get_vector_item(arguments, 0);

    printf("%s\n", help_template);
    hashmap_iterate(commands, print_command, NULL);
    printf("\n");
}