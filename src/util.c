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

char* concat(char *name, ...) {
    char *final = sdsnew(name);
    char* str;
    va_list arg;
    va_start(arg, name);
    while((str = va_arg(arg, char*)) != NULL) {
        final = sdscat(final, str);
    }
    va_end(arg);
    return final;
}

load_t *load_ark_config() {
    char current_dir[512];
    if (getcwd(current_dir, sizeof(current_dir))) {
        printf("%s\n", current_dir);
    }

    // this looks for a configuration file to read
    // in the current directory, it will throw an error
    // if it can't find one.
    char *ark_config_path = concat(current_dir, "/Arkade.toml", false);
    if (!dir_exists(ark_config_path)) {
        printf("error: no configuration file exists in the current directory.\n"
            "Arkade is looking for the following configuration file:\n"
            "\n"
            "    `%s`\n"
            "\n", ark_config_path);
        return false;
    }

    load_t *loader = create_loader(create_sourcefile(ark_config_path));
    sdsfree(ark_config_path);
    return loader;
}