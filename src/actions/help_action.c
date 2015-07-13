#include "actions.h"

static const char* help_template = {
    "usage: ark <command> [<args> ...]"
    "\n"
    "\n"
    "commands:"
    "\n"
};

int print_command(any_t data, any_t item) {
    command_t *command = item;
    #ifdef _WIN32
    printf("    %-10s %s\n", command->name, command->desc);
    #else
    printf("    \033[1m%-10s\033[0m %s\n", command->name, command->desc);
    #endif

    return MAP_OK;
}

void help_action(vector_t *arguments) {
    printf("%s\n", help_template);
    map_t *commands = get_vector_item(arguments, 0);
    hashmap_iterate(commands, print_command, NULL);
    printf("\n");
}