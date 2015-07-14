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
    char *github_username = get_string_contents("username", package);
    char *curl_auth = concat(github_username, ":", auth_token, false);
    char *repo_url = concat("http://www.github.com/", github_username, "/", project_name, false);

    // create repo with curl!
    // this is where it gets messy

    CURL *curl = curl_easy_init();
    if (!curl) {
        printf("error: could not do my shit with curl\n");
    }
    else {
        // the builder should really allow you to join elements normally?
        // e.g.
        // json_builder *builder = create_builder();
        // build_root(builder);
        // append_element(builder, "name", json_str("value"));
        // append_element(builder, "yeah", json_array("a", "b"))
        // end_root(builder)
        // would give us:
        //
        //  { name: "value", "yeah": ["a", "b"] }
        //
        // ??
        char *repo_create_request = "todo";

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

        system("git add --all");
        system("git commit -m 'initial commit'");
        system("git push -u ark_remote master");
    }

    sdsfree(curl_auth);
    sdsfree(repo_url);
    destroy_loader(token_loader);
    destroy_loader(loader);
}