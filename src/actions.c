#include "actions.h"
#include "json_builder.h"

static const char *help = {
    "Ark's package manager\n"
    "\n"
    "Usage: \n"
    "\tarkade <command> [<args>...]\n"
    "\tarkade [options]\n"
    "\n"
    "Some common arkade commands are:\n"
    "\tbuild\tCompile the current project\n"
    "\tnew\tCreate a new Ark project\n"
    "\tpublish\tPublish project\n"
    "\n"
};

void help_action(vector_t *arguments) {
    // todo we can iterate through our
    // command/args list?
    printf("%s", help);
}

void new_action(vector_t *arguments) {
    // some default information
    const char *package_name = get_vector_item(arguments, 0);
    const char *package_author = "John Terry";
    const char *package_version = "0.0.1";
    const char *package_author_email = "terry@terry.cat";

    // add the forward slash to the package name
    char *package_name_dir = sdsempty();
    package_name_dir = sdscat(package_name_dir, package_name);
    package_name_dir = sdscat(package_name_dir, "/");

    // this is the parent directory for the project
    if (dir_exists(package_name_dir)) {
        printf("error: the directory `%s` already exists\n", package_name_dir);
        sdsfree(package_name_dir);
        return;
    }

    // create package directory
    create_directory(package_name_dir, 0700);

    // create our deps folder
    char *deps_folder = sdsnew(package_name_dir);
    deps_folder = sdscat(deps_folder, DEPENDENCY_FOLDER_NAME);
    create_directory(deps_folder, 0700);
    sdsfree(deps_folder);

    // and the source folder
    char *src_folder = sdsnew(package_name_dir);
    src_folder = sdscat(src_folder, SRC_FOLDER_NAME);
    create_directory(src_folder, 0700);
    sdsfree(src_folder);

    // and the files that go inside...
    create_config_file(package_name, package_author, package_version, package_author_email);
    create_gitignore_file(package_name);

    // init git repo

    sdsfree(package_name_dir);
}

void publish_action(vector_t *arguments) {
    CURL *curl;
    curl = curl_easy_init();
    if (!curl) {
        printf("error: could not fuck with curl\n");
        return;
    }

    load_t *token_loader = create_loader(create_sourcefile("~/.arkade/config.toml"));
    table_t *config = get_table(token_loader, "config");

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd))) {
        printf("current directory is %s\n", cwd);
    }

    load_t *config_loader = create_loader(create_sourcefile("Ark.toml"));
    table_t *package = get_table(config_loader, "package");

    char *username = get_string("user", package);
    char *reponame = get_string("name", package);
    char *token = get_string("token", config);
    char *auth_user = sdsnew(username);
    auth_user = sdscat(auth_user, ":");
    auth_user = sdscat(auth_user, token);

    // TODO JSON builder, then we can easily
    // add properties from the TOML file too.

    // TODO change name to something else at a later point
    char* request = build_root_element("name", reponame);
    request = end_root_element(request);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "User-Agent: arkade");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/user/repos");
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request);
    curl_easy_setopt(curl, CURLOPT_USERPWD, auth_user);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    char *repo_url = sdsnew("https://github.com/");
    repo_url = sdscat(repo_url, username);
    repo_url = sdscat(repo_url, "/");
    repo_url = sdscat(repo_url, reponame);

    char *add_remote = sdsnew("git remote add ark_origin ");
    add_remote = sdscat(add_remote, repo_url);

    // system(add_remote);
    // system("git add --all");
    // system("git commit -m \"publish\"");
    // system("git push -u ark_origin master");

    sdsfree(request);
    sdsfree(repo_url);
    sdsfree(add_remote);
}

void build_action(vector_t *arguments) {
    // lol
    // todo make this nicer
    system("mkdir -p bin/");
    system("ark build src/*.ark -o bin/main");
}

void login_action(vector_t *arguments) {
    char *token = get_vector_item(arguments, 0);

    sds path = sdsnew(getenv("HOME"));
    path = sdscat(path, "/.arkade");

    if (!dir_exists(path)) {
        create_directory(path, 0700);
    }

    sds config_file_path = sdsnew(path);
    config_file_path = sdscat(config_file_path, "/config.toml");
    if (dir_exists(config_file_path)) {
        printf("woah buddy, looks like you've already setup your token!\n");
    }
    else {
        FILE *config = create_file(config_file_path);
        fprintf(config, "[config]\n"
                        "token = \"%s\"\n", token);
        fclose(config);
    }

    sdsfree(config_file_path);
    sdsfree(path);
}

void create_config_file(const char *package_name, const char *package_version, const char *package_author, const char *package_author_email) {
    char *config_file_name = sdsnew(package_name);
    config_file_name = sdscat(config_file_name, "/" CONFIG_NAME);

    FILE *config_file = create_file(config_file_name);
    fprintf(config_file, "[package]\n"
        "name = \"%s\"\n"
        "version = \"%s\"\n"
        "authors = [\n"
        "\t\"%s <%s>\"\n"
        "]\n", package_name, package_version, package_author, package_author_email);
    fclose(config_file);

    sdsfree(config_file_name);
}

void create_gitignore_file(const char *package_name) {
    char *gitignore_name = sdsnew(package_name);
    gitignore_name = sdscat(gitignore_name, "/" GITIGNORE_NAME);

    FILE *gitignore = create_file(gitignore_name);
    fprintf(gitignore, 
        "_deps/\n"       // dependencies
        "*.s/\n"        // assembly
        "*.ll/\n"       // llvm-ir
        "*.o/\n"        // objects
        "*.bc/\n");     // llvm bitcode
    fclose(gitignore);

    sdsfree(gitignore_name);
}