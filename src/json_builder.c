#include "json_builder.h"

char* build_root_element(char* name, char* value) {
	char* final = sdsempty();

	final = sdscat(final, "{\n" TAB "\"");
	final = sdscat(final, name);
	final = sdscat(final, "\": \"");
	final = sdscat(final, value);
	final = sdscat(final, "\",\n");
	return final;
}

char* end_root_element(char* final) {
	char* final_result = sdsempty();
	final_result = sdscat(final_result, final);
	final_result = sdscat(final_result, "\n}");
	return final_result;
}

char* build_new_argument(char* name, char* value) {
	char* final = sdsempty();
	final = sdscat(final, "\"");
	final = sdscat(final, name);
	final = sdscat(final, "\": \"");
	final = sdscat(final, value);
	final = sdscat(final, "\",\n");
	return final;
}

char* build_new_array(char *name, ...) {
	char *final = sdsempty();
	final = sdscat(final, TAB "\"");
	final = sdscat(final, name);
	final = sdscat(final, "\": [");
	char* str;

	va_list arg;
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
	}
	va_end(arg);

	final = sdscat(final, "],\n");
	return final;
}



