#ifndef __PROCESS_HANDLER
#define __PROCESS_HANDLER

#include <stdio.h>
#include <stdarg.h>

#include "vector.h"

#define create_process(...) (__create_process(__VA_ARGS__, false))

typedef struct {
    char *output;
    bool failed;
} process_t;

bool __create_process(char *command, char *input, ...);

#endif // __PROCESS_HANDLER