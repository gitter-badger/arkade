#ifndef _ARKADE_JSON_BUILDER_H
#define _ARKADE_JSON_BUILDER_H

#include "sds.h"
#include "util.h"

sds build_root_element(sds value);
sds end_root_element(sds final);
sds build_new_argument(sds name, sds value);

#endif