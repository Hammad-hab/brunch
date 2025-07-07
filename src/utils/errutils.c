#ifndef ERRUTIL
#define ERRUTIL
#include "strutils.c"

void log_error(const char* error) {
    fprintf(stderr, "...And 🍪Brunch Said:  %s\n", error);
}

#endif
