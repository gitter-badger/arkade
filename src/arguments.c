#include "arguments.h"

static map_t *commands;

command *create_command(char *name, char *desc, void (*action)(vector*), size_t arg_count) {
    command *cmd = malloc(sizeof(*cmd));
    cmd->name = name;
    cmd->desc = desc;
    cmd->action = action;
    cmd->arg_count = arg_count;
    return cmd;
}

void destroy_command(command *cmd) {
    free(cmd);
}

int destroy_commands(any_t __attribute__((unused)) passed_data, any_t item) {
    destroy_command(item);
    return MAP_OK;
}

void parse_arguments(int argc, char** argv) {
    if (argc <= 1) {
        help_action(NULL);
        return;
    }

    // populate hashmap
    commands = hashmap_new();
    hashmap_put(commands, "help", create_command("help", "shows this help menu", &help_action, 0));
    hashmap_put(commands, "new", create_command("new", "Create a new Ark project", &new_action, 1));
    hashmap_put(commands, "publish", create_command("publish", "Publishes the project", &publish_action, 0));

    char *command_arg = argv[1];
    command *cmd = NULL;
    if (hashmap_get(commands, command_arg, (void**) &cmd) == MAP_OK) {
        // check we have enough shit
        size_t start = 2;
        
        // note the 1 + is to account
        // for the arkade executable name
        if ((start + cmd->arg_count) > (size_t) argc) {
            printf("error: too many arguments for subcommand `%s`, \n", cmd->name);
            return;
        }

        // eat all the arguments
        // todo, handle flags too
        vector *arguments = create_vector();
        for (size_t i = start; i <= start + cmd->arg_count; i++) {
            push_back_item(arguments, argv[i]);
        }
        cmd->action(arguments);
        destroy_vector(arguments);
    }
    else {
        printf("error: no such subcommand `%s`\n", command_arg);
    }

    // cleanup our hashmap and its contents
    hashmap_iterate(commands, destroy_commands, NULL);
    hashmap_free(commands);
}