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

char *concat(sds initial, ...) {
    sds result = sdsnew(initial);

    va_list arg;
    va_start(arg, initial);
    result = sdscat(result, arg);
    va_end(arg);

    return result;
}
