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
    if (strcmp(license_option, "agpl-3.0") == 0) {
        license = 0;
    }
    else if (strcmp(license_option, "apache-2.0") == 0) {
        license = 1;
    }
    else if (strcmp(license_option, "artistic-2.0") == 0) {
        license = 2;
    }
    else if (strcmp(license_option, "bsd-2-clause") == 0) {
        license = 3;
    }
    else if (strcmp(license_option, "bsd-3-clause") == 0) {
        license = 4;
    }
    else if (strcmp(license_option, "cc0-1.0") == 0) {
        license = 5;
    }
    else if (strcmp(license_option, "epl-1.0") == 0) {
        license = 6;
    }
    else if (strcmp(license_option, "gpl-2.0") == 0) {
        license = 7;
    }
    else if (strcmp(license_option, "gpl-3.0") == 0) {
        license = 8;
    }
    else if (strcmp(license_option, "isc") == 0) {
        license = 9;
    }
    else if (strcmp(license_option, "lgpl-2.1") == 0) {
        license = 10;
    }
    else if (strcmp(license_option, "lgpl-3.0") == 0) {
        license = 11;
    }
    else if (strcmp(license_option, "mit") == 0) {
        license = 12;
    }
    else if (strcmp(license_option, "mpl-2.0") == 0) {
        license = 13;
    }
    else if (strcmp(license_option, "no-license") == 0) {
        license = 14;
    }
    else if (strcmp(license_option, "unlicense") == 0) {
        license = 15;
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

        if (license > -1) {
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