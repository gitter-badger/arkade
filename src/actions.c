#include "actions.h"

static const char *help = {
    "Ark's package manager\n"
    "\n"
    "Usage: \n"
    "\tarkade <command> [<args>...]\n"
    "\tarkade [options]\n"
    "\n"
    "Some common arkade commands are:\n"
    "\tbuild\tCompile the current project\n"
    "\tnew\tCreate a new Ark project\n"
    "\tpublish\tPublish project\n"
    "\n"
};

static void create_directory(const char *path, int mode) {
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

    FILE *handle = fopen(CONFIG_NAME, "rb+");
    if (!handle) {
        handle = fopen(CONFIG_NAME, "wb");
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

void publish_action() {
    
}