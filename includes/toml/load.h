#ifndef __LOAD_H
#define __LOAD_H

/*
    this is for loading values
    from a toml file.
*/
typedef struct {

} load_t;

load_t *create_loader(sourcefile *file);



void destroy_loader(load_t *loader);

#endif // __LOAD_H