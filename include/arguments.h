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
    void (*action)(vector_t*);
    vector_t *arguments;
    size_t arg_count;
} command_t;

typedef struct {
    command_t *parent;
    char *name;
    char *desc;
    void (*action)(void);
} flag_t;

command_t *create_command(char *name, char *desc, void (*action)(vector_t*), size_t arg_count);

void destroy_command(command_t *cmd);

int destroy_commands(any_t __attribute__((unused)) passed_data, any_t item);

void parse_arguments(int argc, char **argv);

#endif // __ARGUMENTS_H
