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

int destroy_commands(any_t __attribute__((unused)) passed_data, any_t item) {
    destroy_command(item);
    return MAP_OK;
}

void create_directory(const char *path, int mode) {
    struct stat st;
    if (stat(path, &st) == -1) {
        mkdir(path, mode);
    } else {
        printf("error: `%s` directory already exists\n", path);
        return;
    }
}

void help_action() {
    // todo we can iterate through our
    // command/args list?
    printf("%s", help);
}

void new_action() {
    // create our deps folder
    create_directory("_deps", 0700);
    create_directory("src", 0700);

    FILE *handle = fopen("ark.toml", "rb+");
    if (!handle) {
        handle = fopen("ark.toml", "wb");
        if (!handle) {
            printf("error: could not create config file\n");
            return;
        }

        // todo load stuff from git/read or just read??
        const char *package_name = "Onion Man";
        const char *package_author = "John Terry";
        const char *package_version = "0.0.1";
        const char *package_author_email = "terry@terry.cat";

        fprintf(handle, "[package]\n");
        fprintf(handle, "name = %s\n", package_name);
        fprintf(handle, "version = %s\n", package_version);
        fprintf(handle, "authors = [\n");
        fprintf(handle, "\t\"%s <%s>\"\n", package_author, package_author_email);
        fprintf(handle, "]\n");
        fclose(handle);
    } 
    else {
        printf("error: could not create config file\n");
    }
}

void parse_arguments(int argc, char** argv) {
    if (argc <= 1) {
        help_action();
        return;
    }

    // populate hashmap
    commands = hashmap_new();
    hashmap_put(commands, "help", create_command("help", "shows this help menu", &help_action, 0));
    hashmap_put(commands, "new", create_command("new", "Create a new Ark project", &new_action, 0));

    char *command_arg = argv[1];
    command *cmd = NULL;
    if (hashmap_get(commands, command_arg, (void**) &cmd) == MAP_OK) {
        cmd->action();
    }
    else {
        printf("error: no such subcommand `%s`\n", command_arg);
    }

    // cleanup our hashmap and its contents
    hashmap_iterate(commands, destroy_commands, NULL);
    hashmap_free(commands);
}