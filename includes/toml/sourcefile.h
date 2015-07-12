#ifndef __SOURCEFILE_H
#define __SOURCEFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>

#include "vector.h"

typedef struct {
    char *name;
    char *location;
    char *contents;
    vector *tokens;
    vector *ast;
} sourcefile;

sourcefile *create_sourcefile(char *location);

char *read_file(sourcefile *file);

void destroy_sourcefile(sourcefile *self);

#endif // __SOURCEFILE_H