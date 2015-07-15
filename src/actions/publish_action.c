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

    // check the config file to see if the specified
    // repository is private
    bool private = true;
    if (!get_string_contents("private", package)) {
        private = false;
    }

    char *license_option = get_string_contents("license", package);
    int license = -1;
    map_t *license_map = hashmap_new();
    hashmap_put(license_map, "mit", "mit");
    hashmap_put(license_map, "agpl-3.0", "agpl-3.0");
    hashmap_put(license_map, "apache-2.0", "apache-2.0");
    hashmap_put(license_map, "artistic-2.0", "artistic-2.0");
    hashmap_put(license_map, "bsd-2-clause", "bsd-2-clause");
    hashmap_put(license_map, "bsd-3-clause", "bsd-3-clause");
    hashmap_put(license_map, "cc0-1.0", "cc0-1.0");
    hashmap_put(license_map, "epl-1.0", "epl-1.0");
    hashmap_put(license_map, "gpl-2.0", "gpl-2.0");
    hashmap_put(license_map, "gpl-3.0", "gpl-3.0");
    hashmap_put(license_map, "isc", "isc");
    hashmap_put(license_map, "lgpl-2.1", "lgpl-2.1");
    hashmap_put(license_map, "lgpl-3.0", "lgpl-3.0");
    hashmap_put(license_map, "mpl-2.0", "mpl-2.0");
    hashmap_put(license_map, "no-license", "no-license");
    hashmap_put(license_map, "unlicense", "unlicense");

    if (hashmap_get(license_map, license_option, (void **) &license_option) == MAP_OK) {
        license = 0;
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
        if (private) {
            json_pair(json, "private");
            json_boolean(json, true);
        }

        if (license == 0) {
            json_pair(json, "license_template");
            json_string(json, license_option);
        }
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

        if (license == 0) {
            system("git pull ark_remote master --force");
        }
        system("git add --all");
        system("git commit -m 'initial commit'");
        system("git push -u ark_remote master");

        destroy_json_builder(json);
    }

    // jesus...

    sdsfree(curl_auth);
    sdsfree(repo_url);
    hashmap_free(license_map);

    cleanup:
        destroy_loader(token_loader);
        destroy_loader(loader);
}