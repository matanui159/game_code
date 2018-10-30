#include "file.h"
#include <au/log.h>
#include <errno.h>
#include <string.h>

FILE* wheel_file_open(const char* path, const char* mode) {
	FILE* file = fopen(path, mode);
	if (file == NULL) {
		au_log_fail(path, "%s", strerror(errno));
	}
}