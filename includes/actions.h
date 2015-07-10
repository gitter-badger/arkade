#ifndef __ACTIONS_H
#define __ACTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define CONFIG_NAME ("Ark.toml")

void help_action();
void new_action();
void publish_action();

#endif // __ACTIONS_H