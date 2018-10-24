#include "input.h"
#include "util.h"
#include <string.h>
#include <errno.h>

static FILE* g_file;
static int g_peek = -1;

static const char* g_path;
static int g_line = 1;

void wheel_input_init(const char* path) {
	g_file = wheel_util_file(path, "rb");
	g_path = path;
}

char wheel_input_peek() {
	if (g_peek == -1) {
		g_peek = fgetc(g_file);
		
		if (g_peek == 0 || g_peek >= 0x80) {
			wheel_input_error("Invalid character $%02X", g_peek);
		}
		if (g_peek == -1) {
			g_peek = 0;
		}
		if (g_peek == '\n') {
			++g_line;
		}
	}
	return g_peek;
}

char wheel_input_next() {
	char next = wheel_input_peek();
	g_peek = -1;
	return next;
}

void wheel_input_error(const char* fmt, ...) {
	va_list list;
	va_start(list, fmt);

	va_list copy;
	va_copy(copy, list);
	int size = vsnprintf(NULL, 0, fmt, copy) + 1;
	va_end(copy);

	char buffer[size];
	vsnprintf(buffer, size, fmt, list);
	va_end(list);
	wheel_util_error("[%s:%i] %s", g_path, g_line, buffer);
}