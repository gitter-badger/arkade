#include "arguments.h"

static map_t *commands;

command_t *create_command(char *name, char *desc, void (*action)(vector_t*), size_t arg_count) {
    command_t *cmd = malloc(sizeof(*cmd));
    cmd->name = name;
    cmd->desc = desc;
    cmd->action = action;
    cmd->arg_count = arg_count;
    return cmd;
}

void destroy_command(command_t *cmd) {
    free(cmd);
}

int destroy_commands(any_t __attribute__((unused)) passed_data, any_t item) {
    destroy_command(item);
    return MAP_OK;
}

void parse_arguments(int argc, char** argv) {
    // populate hashmap
    commands = hashmap_new();
    hashmap_put(commands, "help", create_command("help", "Shows this help menu", &help_action, 0));
    hashmap_put(commands, "new", create_command("new", "Create a new Ark project", &new_action, 1));
    hashmap_put(commands, "publish", create_command("publish", "Publishes the project", &publish_action, 0));
    hashmap_put(commands, "build", create_command("build", "Compiles the current ark project", &build_action, 0));
    hashmap_put(commands, "login", create_command("login", "Setup your GitHub Auth Token", &login_action, 1));
    hashmap_put(commands, "update", create_command("update", "Rebuilds all dependencies", &update_action, 0));

    // not enough arguments given, just show the help
    // menu
    if (argc <= 1) {
        // again we have to do the weird hack
        // where the hashmap of commands is passed
        // as an argument
        vector_t *args = create_vector();
        push_back_item(args, commands);
        help_action(args);
        destroy_vector(args);
        return;
    }

    char *command_arg = argv[1];
    command_t *cmd = NULL;
    if (hashmap_get(commands, command_arg, (void**) &cmd) == MAP_OK) {
        // check we have enough shit
        size_t start = 2;
        
        // note the 1 + is to account
        // for the arkade executable name
        if ((start + cmd->arg_count) > (size_t) argc) {
            printf("error: not enough/too many arguments for subcommand `%s`, \n", cmd->name);
            return;
        }

        // eat all the arguments
        // todo, handle flags too
        vector_t *arguments = create_vector();
        
        // HACK
        // push the commands hashmap as an argument for
        // the help_action!
        if (!strcmp(command_arg, "help")) {
            push_back_item(arguments, commands);
        }

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