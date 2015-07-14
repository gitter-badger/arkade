#ifndef __UTIL_H
#define __UTIL_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "load.h"
#include "sds.h"

bool dir_exists(const char *path);

void create_directory(const char *path, int mode);

FILE *create_file(const char *name);

char *concat(char *initial, ...);

load_t *load_ark_config();

#endif // __UTIL_H