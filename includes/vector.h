#ifndef __VECTOR_H
#define __VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "util.h"

typedef void* vector_item;

typedef struct {
    vector_item *items;
    int max_size;
    int size;
} vector;

vector *create_vector();

void push_back_item(vector *vec, vector_item item);

vector_item get_vector_item(vector *vec, int index);

vector_item get_vector_top(vector *vec);

void destroy_vector(vector *vec);

#endif // __VECTOR_H