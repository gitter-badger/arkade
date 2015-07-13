#include "json_builder.h"

sds build_root_element(sds value) {
	sds final = sdsnew("");
	sds const_name = "\"name\"";

	// series of ugly string concatenations
	sdscat(final, "{ ");
	sdscat(final, const_name);
	sdscat(final, ": \"");
	sdscat(final, value);
	sdscat(final, "\"");

	// debugging
	printf("%s", final);
	return final;
}

sds end_root_element(sds final) {
	sds final_result = sdsnew("");
	final_result = sdscat(final, "\n}");
	return final_result;
}

sds build_new_argument(sds name, sds value) {
	sds final = sdsnew("");
	sdscat(final, "\"");
	sdscat(final, name);
	sdscat(final, "\": \"");
	sdscat(final, value);
	sdscat(final, "\",\n");

	// debugging
	printf("%s", final);
	return final;
}