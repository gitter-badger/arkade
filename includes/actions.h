#ifndef __ACTIONS_H
#define __ACTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "vector.h"

#define CONFIG_NAME "Ark.toml"
#define DEPENDENCY_FOLDER_NAME "_deps"
#define SRC_FOLDER_NAME "src"

void help_action(vector *arguments);
void new_action(vector *arguments);
void publish_action(vector *arguments);

#endif // __ACTIONS_H