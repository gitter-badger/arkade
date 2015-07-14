#include "json_builder.h"

json_builder_t *create_json_builder() {
	json_builder_t *builder = malloc(sizeof(*builder));
	builder->result = sdsempty();
	builder->item = 0;
	return builder;
}

void json_open_object(json_builder_t *builder) {
	json_raw(builder, "{\n");
}

void json_close_object(json_builder_t *builder) {
	json_raw(builder, "\n}");
}

void json_raw(json_builder_t *builder, char *raw) {
	builder->result = sdscat(builder->result, raw);
}

void json_string(json_builder_t *builder, char *value) {
	json_raw(builder, "\"");
	json_raw(builder, value);
	json_raw(builder, "\"");
}

void json_number(json_builder_t *builder, char *value) {
	json_raw(builder, value);
}

char *get_json_buffer(json_builder_t *builder) {
	return builder->result;
}

void json_array(json_builder_t *builder, char *value, ...) {
	json_raw(builder, "[");
	json_raw(builder, value);

	va_list arg;
<<<<<<< HEAD
	va_start(arg, name);
	int i = 0;
	while((str = va_arg(arg, char*)) != NULL) {
		if (i != 0) {
			final = sdscat(final, ", ");
		}
		final = sdscat(final, "\"");
		final = sdscat(final, str);
		final = sdscat(final, "\"");
		i++;
=======
	va_start(arg, value);
	int count = 0;
	char *str;
	while ((str = va_arg(arg, char*))) {
		json_raw(builder, ", ");
		json_raw(builder, str);
		count++;
>>>>>>> upstream/master
	}
	va_end(arg);

	json_raw(builder, "]");
}

void json_boolean(json_builder_t *builder, bool value) {
	json_raw(builder, value ? "true" : "false");
}

void json_pair(json_builder_t *builder, char *name) {
	if (builder->item != 0) {
		json_raw(builder, ",\n");
	}

	json_raw(builder, TAB "\"");
	json_raw(builder, name);
	json_raw(builder, "\": ");

	builder->item++;
}

void destroy_json_builder(json_builder_t *builder) {
	printf("json dump:\n%s\n", builder->result);

	sdsfree(builder->result);
	free(builder);
}
