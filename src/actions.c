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

static FILE *create_file(const char *name) {
    FILE *handle = fopen(name, "rb+");
    if (!handle) {
        handle = fopen(name, "wb");
        if (!handle) {
            printf("error: could not create file `%s`\n", name);
            return false;
        }
    } 
    else {
        printf("error: could not create file `%s`\n", name);
        return false;
    }
    return handle;
}

void help_action(command *cmd, vector *arguments) {
    // todo we can iterate through our
    // command/args list?
    printf("%s", help);
}

void new_action(command *cmd, vector *arguments) {
    const char *package_name = "Onion Man";
    const char *package_author = "John Terry";
    const char *package_version = "0.0.1";
    const char *package_author_email = "terry@terry.cat";

    // create our deps folder
    create_directory(DEPENDENCY_FOLDER_NAME, 0700);
    create_directory(SRC_FOLDER_NAME, 0700);

    // create basic config file
    FILE *config_file = create_file(CONFIG_NAME);
    fprintf(config_file, "[package]\n");
    fprintf(config_file, "name = %s\n", package_name);
    fprintf(config_file, "version = %s\n", package_version);
    fprintf(config_file, "authors = [\n");
    fprintf(config_file, "\t\"%s <%s>\"\n", package_author, package_author_email);
    fprintf(config_file, "]\n");
    fclose(config_file);

    FILE *gitignore = create_file(".gitignore");
    fprintf(gitignore, "_deps/\n");     // dependencies
    fprintf(gitignore, "*.s/\n");       // asm
    fprintf(gitignore, "*.ll/\n");      // llvm-ir
    fprintf(gitignore, "*.o/\n");       // objects
    fprintf(gitignore, "*.bc/\n");      // llvm bitcode
    fclose(gitignore);

    // setup git repository
    // TODO dont use system calls
    // but for now it works
    system("git init");
    system("git add --all");
    system("git commit -m \"created new project with arkade!\"");
}

void publish_action(command *cmd, vector *arguments) {
    // create repository on github
    // push repository
    // TODO fuck with curl to send create repo request
    // add a remote, maybe diff name than origin
    // push to remote
}