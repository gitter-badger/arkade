#include "arguments.h"

static const char *help = {
    "Ark's package manager\n"
    "\n"
    "Usage: \n"
    "\tarkade <command> [<args>...]\n"
    "\tarkage [options]\n"
    "\n"
    "Some common arkade commands are:\n"
    "\tbuild\tCompile the current project\n"
    "\tnew\tCreate a new Ark project\n"
    "\n"
};

static map_t *commands;

command *create_command(char *name, char *desc, void (*action)(void), size_t arg_count) {
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

void help_action() {
    // todo we can iterate through our
    // command/args list?
    printf("%s", help);
}

void parse_arguments(int argc, char** argv) {
    if (argc <= 1) {
        help_action();
        return;
    }

    commands = hashmap_new();
    hashmap_put(commands, "help", create_command("help", "shows this help menu", &help_action, 0));
    char *command_arg = argv[1];

    command *cmd = NULL;
    if (hashmap_get(commands, command_arg, (void**) &cmd) == MAP_OK) {
        cmd->action();
    }
    else {
        printf("error: no such subcommand `%s`\n", command_arg);
    }

    hashmap_free(commands);
}