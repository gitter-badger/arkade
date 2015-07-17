#include "actions.h"

int dependencies_iterate(any_t data, any_t item_p) {
	bare_key_t *item = item_p;
	char *folder = item->name;
	array_t *stuff = item->value->array_expr;
	printf("%d\n", stuff->values->size);
	char *url = get_array_value(stuff, 0);
	char *version = get_array_value(stuff, 1);
	char *clone_process = concat("git clone -b ", version, " --depth 1 ", url, " _deps/", folder);
	printf("%s\n", clone_process);
	exec_process(clone_process);
	sdsfree(clone_process);
	// printf("\n%s %s %s\n\n", folder, url, version);
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