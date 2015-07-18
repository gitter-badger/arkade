#ifndef __VECTOR_H
#define __VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef void* vector_item;

typedef struct {
    vector_item *items;
    int max_size;
    int size;
} vector_t;

vector_t *create_vector();

void push_back_item(vector_t *vec, vector_item item);

vector_item get_vector_item(vector_t *vec, int index);

vector_item get_vector_top(vector_t *vec);

void destroy_vector(vector_t *vec);

#endif // __VECTOR_H
