#ifndef __SOURCEFILE_H
#define __SOURCEFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>

#include "hashmap.h"
#include "vector.h"
#include "ast.h"

typedef struct {
    char *name;
    char *location;
    char *contents;
    vector_t *tokens;
    map_t *ast;
} sourcefile_t;

sourcefile_t *create_sourcefile(char *location);

char *read_file(sourcefile_t *file);

void destroy_sourcefile(sourcefile_t *self);

#endif // __SOURCEFILE_H
