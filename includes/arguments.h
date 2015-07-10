#ifndef __ARGUMENTS_H
#define __ARGUMENTS_H

#include <stdio.h>
#include <stdlib.h>

#include "hashmap.h"
#include "actions.h"
#include "vector.h"

typedef struct {
    char *name;
    char *desc;
    void (*action)(vector*);
    vector *arguments;
    size_t arg_count;
} command;

typedef struct {
    command *parent;
    char *name;
    char *desc;
    void (*action)(void);
} flag;

command *create_command(char *name, char *desc, void (*action)(vector*), size_t arg_count);

void destroy_command(command *cmd);

int destroy_commands(any_t __attribute__((unused)) passed_data, any_t item);

void parse_arguments(int argc, char **argv);

#endif // __ARGUMENTS_H