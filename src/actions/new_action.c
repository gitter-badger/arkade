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

static const char* template_helloworld = {
    "// Auto-generated by Arkade\n"
    "\n"
    "[c] func printf(fmt: str): int;\n"
    "\n"
    "func main(): int {\n"
    "\tC::printf(\"Hello world!\\n\");\n"
    "\n"
    "\treturn 0;\n"
    "}\n"
};

void new_action(vector_t *arguments) {
    char *project_directory = sdsnew(get_vector_item(arguments, 0));
    if (dir_exists(project_directory)) {
        printf("error: a directory already exists with the name `%s`\n", project_directory);
        sdsfree(project_directory);
        return;
    }

    char *project_config = concat(project_directory, "/arkade.toml");
    create_directory(project_directory, 0700);

    char *project_gitignore = concat(project_directory, "/.gitignore");

    char *project_helloworld = concat(project_directory, "/src/main.ark");

    char *deps_path = concat(project_directory, "/_deps/");
    create_directory(deps_path, 0700);
    sdsfree(deps_path);

    char *src_path = concat(project_directory, "/src/");
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
    char *git_init_cmd = concat("cd ", project_directory, " && git init");
    create_process(git_init_cmd);

    // the magical gitignore
    FILE *gitignore_file = fopen(project_gitignore, "w");
    if (gitignore_file) {
        fprintf(gitignore_file, "%s\n", template_gitignore);
        fclose(gitignore_file);
    } else {
        printf("error: could not write config file `%s`\n", project_gitignore);
        return;
    }

    // first ark sourcefile
    FILE *helloworld_file = fopen(project_helloworld, "w");
    if (helloworld_file) {
        fprintf(helloworld_file, "%s\n", template_helloworld);
        fclose(helloworld_file);
    } else {
        printf("error: could not write main.ark file `%s`\n", project_helloworld);
        return;
    }

    sdsfree(project_helloworld);
    sdsfree(project_gitignore);
    sdsfree(project_config);
    sdsfree(project_directory);
}
