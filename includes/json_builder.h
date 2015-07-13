#ifndef _ARKADE_JSON_BUILDER_H
#define _ARKADE_JSON_BUILDER_H

#include "sds.h"
#include "util.h"

#define TAB "    "

char* build_root_element(char* name, char* value);
char* end_root_element(char* final);
char* build_new_argument(char* name, char* value);

#endif