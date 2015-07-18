#include "actions.h"

int dependencies_iterate(any_t data, any_t item_p) {
	bare_key_t *item = item_p;

	array_t *stuff = item->value->array_expr;

	char *url = get_array_value(stuff, 0);
    char *version = get_array_value(stuff, 1);
    char *folder = item->name;
    if (chdir("_deps") == -1) {
        printf("error: are you in the Ark project directory?\n");
        return -1;
    }

    DIR *dir = opendir(folder);
    if (dir) {
        printf("error: clone already exists. Please delete it before retrying.\n");
        closedir(dir);
        return -1;
    }
    // TODO check git tag version and handle appropriately

    // TODO fix this, for some reason concat
    // crashes and burns if you give it more
    // than 5 arguments, so we concat twice
	char *clone_temp = concat("git clone -b ", version, " --depth 1 ", url, " ");
    char *clone_process = concat(clone_temp, folder);

	exec_process(clone_process);

	sdsfree(clone_process);
    sdsfree(clone_temp);

	return MAP_OK;
}

void fetch_action(vector_t *arguments) {
	load_t *project_config_loader = load_project_config();
	if (!project_config_loader) {
		printf("error: are you sure the current directory contains an Ark project?\n");
        return;
	}
    table_t *deps = get_table(project_config_loader, "dependencies");
    if (!deps) {
 		printf("error: [dependencies] was not found in the config file!\n");
 		return;
    }
    hashmap_iterate(deps->nodes, dependencies_iterate, false);
}