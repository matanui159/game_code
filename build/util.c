#include "util.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define STRETCHY_BUFFER_IMPLEMENTATION
#define STRETCHY_BUFFER_OUT_OF_MEMORY wheel_util_error("Out of memory")
#include "stretchy_buffer.h"

void wheel_util_verror(const char* fmt, va_list list) {
	fputs("[ERROR] ", stderr);
	vfprintf(stderr, fmt, list);
	fputc('\n', stderr);
	exit(EXIT_FAILURE);
}

void wheel_util_error(const char* fmt, ...) {
	va_list list;
	va_start(list, fmt);
	wheel_util_verror(fmt, list);
}

FILE* wheel_util_file(const char* path, const char* mode) {
	FILE* file = fopen(path, mode);
	if (file == NULL) {
		wheel_util_error("%s: %s", path, strerror(errno));
	}
	return file;
}