#include "actions.h"

void login_action(vector_t *arguments) {
    char *config_dir = concat(getenv("HOME"), "/.arkade/");
    char *config_path = concat(config_dir, "config.toml");
    if (dir_exists(config_path)) {
        printf("error: it appears you already have arkade configured.\n"
            "If you believe this is an error, you can manually edit the configuration "
            "file located here: TODO -f flag`%s`.\n", config_path);
        sdsfree(config_path);
        sdsfree(config_dir);
        return;
    }

    create_directory(config_dir, 0700);

    char *auth_token = sdsnew(get_vector_item(arguments, 0));
    
    FILE *config_file = fopen(config_path, "w");
    if (config_file) {
        fprintf(config_file, "[config]\ntoken = \"%s\"\n", auth_token);
    } else {
        printf("error: could not write arkade config file at `%s`\n", config_path);
    }
    fclose(config_file);

    sdsfree(auth_token);
    sdsfree(config_path);
    sdsfree(config_dir);
}