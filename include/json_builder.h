#ifndef _ARKADE_JSON_BUILDER_H
#define _ARKADE_JSON_BUILDER_H

#include "sds.h"
#include "util.h"

#define TAB "    "

typedef struct {
    char *result;
    int item;
} json_builder_t;

json_builder_t *create_json_builder();

void json_open_object(json_builder_t *builder);

void json_close_object(json_builder_t *builder);

void json_raw(json_builder_t *builder, char *raw);

void json_string(json_builder_t *builder, char *value);

void json_number(json_builder_t *builder, char *value);

char *get_json_buffer(json_builder_t *builder);

void json_array(json_builder_t *builder, char *value, ...);

void json_boolean(json_builder_t *builder, bool value);

void json_pair(json_builder_t *builder, char *name);

void destroy_json_builder(json_builder_t *json_builder);

#endif
