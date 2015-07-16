#include "actions.h"
#include "json_builder.h"

// so what if this is O(n) over hashmap
// being O(1), this is a tad cleaner imo
const char *licenses[] = {
    "mit", "agpl-3.0", "apache-2.0", "artistic-2.0",
    "bsd-2-clause", "bsd-3-clause", "cc0-1.0", "epl-1.0", 
    "gpl-2.0", "gpl-3.0", "isc", "lgpl-2.1", 
    "lgpl-3.0", "mpl-2.0", "no-license", "unlicense"
};

bool license_exists(const char *license) {
    int num_of_licenses = sizeof(licenses) / sizeof(licenses[0]);
    for (int i = 0; i < num_of_licenses; i++) {
        if (!strcmp(license, licenses[i])) {
            return true;
        }
    }

    printf("error: invalid license %s\n", license);
    return false;
}

void publish_action(vector_t *arguments) {
    // load the auth token from configuration
    load_t *arkade_config_loader = load_arkade_config();
    table_t *config = get_table(arkade_config_loader, "config");
    
    char *auth_token = get_string_contents("token", config);
    if (!auth_token) {
        printf("error: it appears you haven't setup your GitHub auth key"
            "with Arkade, please generate an auth key and run:\n"
            "    arkade login <key>\n"
            "\n");
        destroy_loader(arkade_config_loader);
        return;
    }

    char *github_username = get_string_contents("github_username", config);
    if (!github_username) {
        printf("error: project requires a github username in the arkade configuration file\n"
            "    Please add your `github_username` to %s\n", arkade_config_loader->file->location);
        destroy_loader(arkade_config_loader);
        return;
    }

    // load the project configuration file
    load_t *project_config_loader = load_project_config();
    if (!project_config_loader) {
        printf("error: are you sure the current directory contains an Ark project?\n");
        return;
    }

    table_t *package = get_table(project_config_loader, "package");

    // todo, we should really check 
    // these exist in the config file
    char *project_name = get_string_contents("name", package);
    if (!project_name) {
        printf("error: project name undefined in configuration file\n");
        destroy_loader(arkade_config_loader);
        destroy_loader(project_config_loader);
        return;
    }

    // check the config file to see if the specified
    // repository is private
    bool private = true;
    if (!get_string_contents("private", package)) {
        private = false;
    }

    char *license_option = get_string_contents("license", package);
    char *curl_auth = concat(github_username, ":", auth_token);
    char *repo_url = concat("http://www.github.com/", github_username, "/", project_name);

    // create repo with curl!
    // this is where it gets messy

    CURL *curl = curl_easy_init();
    if (!curl) {
        printf("error: could not do my shit with curl\n");
    }
    else {
        // we need to use this twice, so verify
        // the license exists and what not.
        bool has_license = license_option && license_exists(license_option);

        json_builder_t *json = create_json_builder();

        json_open_object(json);

        // name is the minimum requirement for a project
        json_pair(json, "name");
        json_string(json, project_name);

        if (private) {
            json_pair(json, "private");
            json_boolean(json, true);
        }

        if (has_license) {
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

        char *remote_cmd = concat("git remote add ark_remote ", repo_url);
        create_process(remote_cmd);
        sdsfree(remote_cmd);

        if (has_license) {
            create_process("git pull ark_remote master --force");
        }
        create_process("git add --all");
        create_process("git commit -m 'initial commit'");

        char *push_command = concat(
            "git push https://",
            curl_auth,
            "@github.com/",
            github_username, 
            "/", 
            project_name,
            ".git --all"
        );
        create_process(push_command);
        sdsfree(push_command);

        destroy_json_builder(json);
    }

    sdsfree(curl_auth);
    sdsfree(repo_url);

    destroy_loader(arkade_config_loader);
    destroy_loader(project_config_loader);
}