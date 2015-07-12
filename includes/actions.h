#ifndef __ACTIONS_H
#define __ACTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <curl/curl.h>
#include <unistd.h>

#include "vector.h"
#include "sds.h"

#define CONFIG_NAME "Ark.toml"
#define DEPENDENCY_FOLDER_NAME "_deps"
#define SRC_FOLDER_NAME "src"
#define GITIGNORE_NAME ".gitignore"

void help_action(vector_t *arguments);
void new_action(vector_t *arguments);
void publish_action(vector_t *arguments);
void build_action(vector_t *arguments);
void create_config_file(const char *package_name, const char *package_version, const char *package_author, const char *package_author_email);
void create_gitignore_file(const char *package_name);

#endif // __ACTIONS_H