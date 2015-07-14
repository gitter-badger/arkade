#include "actions.h"

// perhaps placeholder values some point
static const char* template_project_config = {
    "[package]"
};

static const char* template_gitignore = {
    "_deps/\n"
    "*.DS_Store\n"
    "*.bc\n"
    "*.s\n"
    "*.ll\n"
    "*.o\n"
    "*.toml"
};

void new_action(vector_t *arguments) {
    char *project_directory = sdsnew(get_vector_item(arguments, 0));
    if (dir_exists(project_directory)) {
        printf("error: a directory already exists with the name `%s`\n", project_directory);
        sdsfree(project_directory);
        return;
    }

    char *project_config = concat(project_directory, "/arkade.toml", false);
    create_directory(project_directory, 0700);

    char *project_gitignore = concat(project_directory, "/.gitignore", false);

    char *deps_path = concat(project_directory, "/_deps/", false);
    create_directory(deps_path, 0700);
    sdsfree(deps_path);

    char *src_path = concat(project_directory, "/src/", false);
    create_directory(src_path, 0700);
    sdsfree(src_path);

    // create _really_ simple config file
    FILE *config_file = fopen(project_config, "w");
    if (config_file) {
        fprintf(config_file, "%s\n", template_project_config);
        fclose(config_file);
    } else {
        printf("error: could not write config file `%s`\n", project_config);
        return;
    }

    // initialize git repo
    // this uses system calls, pls change
    // to popen or something
    char *git_init_cmd = concat("cd ", project_directory, " && git init", false);
    system(git_init_cmd);

    // the magical gitignore
    FILE *gitignore_file = fopen(project_gitignore, "w");
    if (gitignore_file) {
        fprintf(gitignore_file, "%s\n", template_gitignore);
        fclose(gitignore_file);
    } else {
        printf("error: could not write config file `%s`\n", project_gitignore);
        return;
    }

    sdsfree(project_gitignore);
    sdsfree(project_config);
    sdsfree(project_directory);
}
