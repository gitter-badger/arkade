#include "actions.h"

int dependencies_iterate(any_t data, any_t item_p) {
	bare_key_t *item = item_p;

	array_t *depedency_data = item->value->array_expr;

	char *url = get_array_value(0, depedency_data);
    char *version = get_array_value(1, depedency_data);
    char *folder = item->name;

    // TODO fix this, for some reason concat
    // crashes and burns if you give it more
    // than 5 arguments, so we concat twice
	char *clone_temp = concat("git clone -b ", version, " --depth 1 ", url, " _deps/");
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
