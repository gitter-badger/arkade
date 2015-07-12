#include "vector.h"

vector_t *create_vector() {
    vector_t *vec = malloc(sizeof(*vec));
    vec->size = 0;
    vec->max_size = 2;
    vec->items = malloc(sizeof(*vec->items) * vec->max_size);
    return vec;
}

void push_back_item(vector_t *vec, vector_item item) {
    if (vec) {
        // much more efficient to reallocate exponentially,
        // instead of reallocating after adding an item
        if (vec->size >= vec->max_size) {
            vec->max_size = vec->max_size + 1;
            vec->items = realloc(vec->items, sizeof(*vec->items) * vec->max_size);
            if (!vec->items) {
                printf("error: failed to allocate memory for vector contents\n");
                return;
            }
        }
        vec->items[vec->size++] = item;
    }
    else {
        printf("error: cannot push item to a null vector\n");
        return;
    }
}

vector_item get_vector_item(vector_t *vec, int index) {
    if (index > vec->size) {
        printf("error: index out of vector bounds, index: %d, size: %d\n", index, vec->size);
        return false;
    }
    return vec->items[index];
}

vector_item getVectorTop(vector_t *vec) {
    return get_vector_item(vec, vec->size - 1);
}

void destroy_vector(vector_t *vec) {
    if (!vec) return;
    free(vec->items);
    free(vec);
}