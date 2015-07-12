#include "token.h"

token_t *create_token(char *contents, sourcefile_t *owner, int start, int end, int type) {
    token_t *self = malloc(sizeof(*self));
    self->contents = contents;
    self->owner = owner;
    self->start = start;
    self->end = end;
    self->type = type;
    return self;
}

void destroy_token(token_t *self) {
    free(self);
}