#include "process_handler.h"

static int max_process_count = 10;
static int num_of_processes = 0;

bool __create_process(char *command, char *input, ...) {
    if (num_of_processes >= max_process_count) {
        printf("yo, wait the fuck up\n");
        return false;
    }
    process_t proc;
    proc.output = NULL;
    proc.failed = false;

    FILE *process = popen(command, "w");
    if (!process) {
        printf("could not run proccess `%s`\n", command);
        return proc.failed = true;
    }
    
    if (input) {
        printf("running this shit nigga\n");

        va_list arg;
        va_start(arg, input);
        char *str = NULL;

        fputs(input, process);
        while ((str = va_arg(arg, char*)) != NULL) {
            fputs(str, process);
        }
        va_end(arg);
    }

    return proc.failed;
}