#include "token.h"

token *create_token(char *contents, sourcefile *owner, int start, int end, int type) {
    token *self = malloc(sizeof(*self));
    self->contents = contents;
    self->owner = owner;
    self->start = start;
    self->end = end;
    self->type = type;
    return self;
}

void destroy_token(token *self) {
    free(self);
}