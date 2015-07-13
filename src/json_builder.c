#include "json_builder.h"

char* build_root_element(char* name, char* value) {
	char* final = sdsempty();

	final = sdscat(final, "{\n" TAB "\"");
	final = sdscat(final, name);
	final = sdscat(final, "\": \"");
	final = sdscat(final, value);
	final = sdscat(final, "\"");
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