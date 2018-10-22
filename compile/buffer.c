#include "buffer.h"
#include "input.h"
#include <stdlib.h>

void* wheel_buffer_resize(void* ptr, int size) {
	int* raw = NULL;
	int cap = 0;
	if (ptr != NULL) {
		raw = (int*)ptr - 1;
		cap = *raw;
	}

	if (size > cap) {
		cap *= 2;
		if (size > cap) {
			cap = size;
		}

		raw = realloc(raw, cap + sizeof(int));
		if (raw == NULL) {
			wheel_input_error("Out of memory");
		}
	}
	*raw = cap;
	return raw + 1;
}

void wheel_buffer_destroy(void* ptr) {
	if (ptr != NULL) {
		int* raw = (int*)ptr - 1;
		free(raw);
	}
}