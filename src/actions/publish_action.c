#include "actions.h"
#include "json_builder.h"

void publish_action(vector_t *arguments) {
    // load the auth token from configuration
    load_t *token_loader = load_arkade_config();
    table_t *config = get_table(token_loader, "config");
    char *auth_token = get_string_contents("token", config);

    // load the project configuration file
    load_t *loader = load_project_config();
    if (!loader) {
        printf("error: are you sure the current directory contains an Ark project?\n");
        return;
    }

    table_t *package = get_table(loader, "package");

    // todo, we should really check 
    // these exist in the config file
    char *project_name = get_string_contents("name", package);
    if (!project_name) {
        printf("error: project name undefined in configuration file\n");
        goto cleanup;
    }

    char *github_username = get_string_contents("username", package);
    if (!github_username) {
        printf("error: project requires a github username in the configuration file\n");
        goto cleanup;
    }

    char *curl_auth = concat(github_username, ":", auth_token, false);
    char *repo_url = concat("http://www.github.com/", github_username, "/", project_name, false);

    // create repo with curl!
    // this is where it gets messy

    CURL *curl = curl_easy_init();
    if (!curl) {
        printf("error: could not do my shit with curl\n");
    }
    else {
        json_builder_t *json = create_json_builder();

        json_open_object(json);
        json_pair(json, "name");
        json_string(json, project_name);

        // description for that shit
        char *description = get_string_contents("desc", package);
        if (description) {
            json_pair(json, "desc");
            json_string(json, description);
        }

        json_close_object(json);

        char *repo_create_request = get_json_buffer(json);

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "User-Agent: arkade");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_USERPWD, curl_auth);
        // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/user/repos");
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, repo_create_request);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        char *remote_cmd = concat("git remote add ark_remote ", repo_url, false);
        system(remote_cmd);
        sdsfree(remote_cmd);

        system("git add --all");
        system("git commit -m 'initial commit'");
        system("git push -u ark_remote master");

        destroy_json_builder(json);
    }

    // jesus...

    sdsfree(curl_auth);
    sdsfree(repo_url);

    cleanup:
    destroy_loader(token_loader);
    destroy_loader(loader);
}