#ifndef __PROCESS_HANDLER
#define __PROCESS_HANDLER

#include <stdio.h>
#include <stdarg.h>

#include "vector.h"

#define exec_process(...) (__exec_process(__VA_ARGS__, false))

typedef struct {
    char *output;
    bool failed;
} process_t;

bool __exec_process(char *command, char *input, ...);

#endif // __PROCESS_HANDLER