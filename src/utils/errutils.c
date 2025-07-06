#ifndef ERRUTIL
#define ERRUTIL
#define ERROR_PREFIX "...And 🍪Brunch Said: "
#include "strutils.c"

void log_error(const char* error) {
    fprintf(stderr, "%s", concat(ERROR_PREFIX, error));
}

#endif
