#include "util.h"

bool dir_exists(const char *path) {
    struct stat st;
    if (stat(path, &st) == -1) {
        return false;
    }
    return true;
}

void create_directory(const char *path, int mode) {
    if (!dir_exists(path)) {
        mkdir(path, mode);
    } else {
        printf("error: `%s` directory already exists\n", path);
        return;
    }
}

FILE *create_file(const char *name) {
    FILE *handle = fopen(name, "rb+");
    if (!handle) {
        handle = fopen(name, "wb");
        if (!handle) {
            printf("error: could not create file `%s`\n", name);
            return false;
        }
        return handle;
    } 

    printf("error: could not create file since it exists `%s`\n", name);
    return false;
}

char *__concat(char *name, ...) {
    char *final = sdsnew(name);
    char* str;
    va_list arg;
    va_start(arg, name);
    while ((str = va_arg(arg, char*))) {
        final = sdscat(final, str);
    }
    va_end(arg);
    return final;
}

load_t *load_arkade_config() {
    // does this work on shitdows?
    char *home_dir = concat(getenv("HOME"), "/.arkade/");
    char *config_path = concat(home_dir, "config.toml");
    if (!dir_exists(config_path)) {
        printf("error: it appears you haven't setup your GitHub auth key"
            "with Arkade, please generate an auth key and run:\n"
            "    arkade login <key>\n"
            "\n");
        sdsfree(home_dir);
        sdsfree(config_path);
        return false;
    }

    // TODO verify sourcefile doesnt fuck up
    load_t *loader = create_loader(create_sourcefile(config_path));
    sdsfree(home_dir);
    sdsfree(config_path);
    return loader;
}

load_t *load_project_config() {
    char current_dir[512];
    if (!getcwd(current_dir, sizeof(current_dir))) {
        printf("error: could not load current working directory\n");
        return false;
    }

    // this looks for a configuration file to read
    // in the current directory, it will throw an error
    // if it can't find one.
    char *ark_config_path = concat(current_dir, "/arkade.toml");
    if (!dir_exists(ark_config_path)) {
        printf("error: no configuration file exists in the current directory.\n"
            "Arkade is looking for the following configuration file:\n"
            "\n"
            "    `%s`\n"
            "\n", ark_config_path);
        sdsfree(ark_config_path);
        return false;
    }

    // TODO verify sourcefile doesnt fuck up
    load_t *loader = create_loader(create_sourcefile(ark_config_path));
    sdsfree(ark_config_path);
    return loader;
}
