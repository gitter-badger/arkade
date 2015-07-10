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

void help_action(vector *arguments) {
    // todo we can iterate through our
    // command/args list?
    printf("%s", help);
}

void new_action(vector *arguments) {
    const char *package_name = get_vector_item(arguments, 0);
    const char *package_author = "John Terry";
    const char *package_version = "0.0.1";
    const char *package_author_email = "terry@terry.cat";

    // this is the parent directory for the project
    create_directory(package_name, 0700);

    // create our deps folder
    char *deps_folder = sdsnew(package_name);
    deps_folder = sdscat(deps_folder, "/" DEPENDENCY_FOLDER_NAME);
    create_directory(deps_folder, 0700);
    sdsfree(deps_folder);

    // and the source folder
    char *src_folder = sdsnew(package_name);
    src_folder = sdscat(src_folder, "/" SRC_FOLDER_NAME);
    create_directory(src_folder, 0700);
    sdsfree(src_folder);

    // and the files that go inside...
    create_config_file(package_name, package_author, package_version, package_author_email);
    create_gitignore_file(package_name);

    // setup git repository
    // TODO dont use system calls
    // but for now it works
    system("git init");
    system("git add --all");
    system("git commit -m \"created new project with arkade!\"");
}

void publish_action(vector *arguments) {
    // create repository on github
    // push repository
    // TODO fuck with curl to send create repo request
    // add a remote, maybe diff name than origin
    // push to remote
}

// WHY IS THIS SO UGLY?
void create_config_file(const char *package_name, const char *package_version, const char *package_author, const char *package_author_email) {
    char *config_file_name = sdsnew(package_name);
    config_file_name = sdscat(config_file_name, "/" CONFIG_NAME);
    
    FILE *config_file = create_file(config_file_name);
    fprintf(config_file, "[package]\n");
    fprintf(config_file, "name = %s\n", package_name);
    fprintf(config_file, "version = %s\n", package_version);
    fprintf(config_file, "authors = [\n");
    fprintf(config_file, "\t\"%s <%s>\"\n", package_author, package_author_email);
    fprintf(config_file, "]\n");
    fclose(config_file);
    
    sdsfree(config_file_name);
}

// WHY IS THIS SO UGLY?
void create_gitignore_file(const char *package_name) {
    char *gitignore_name = sdsnew(package_name);
    gitignore_name = sdscat(gitignore_name, "/" CONFIG_NAME);

    FILE *gitignore = create_file(gitignore_name);
    fprintf(gitignore, "_deps/\n");     // dependencies
    fprintf(gitignore, "*.s/\n");       // asm
    fprintf(gitignore, "*.ll/\n");      // llvm-ir
    fprintf(gitignore, "*.o/\n");       // objects
    fprintf(gitignore, "*.bc/\n");      // llvm bitcode
    fclose(gitignore);

    sdsfree(gitignore_name);
}