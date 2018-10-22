#include "input.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

static FILE* g_file;
static int g_peek = -1;

static const char* g_path;
static int g_line = 1;

void wheel_input_init(const char* path) {
	g_path = path;

	g_file = fopen(path, "rb");
	if (g_file == NULL) {
		wheel_input_error("%s", strerror(errno));
	}
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
	fprintf(stderr, "%s:%i: ", g_path, g_line);
	vfprintf(stderr, fmt, list);
	fputc('\n', stderr);
	va_end(list);
	exit(EXIT_FAILURE);
}