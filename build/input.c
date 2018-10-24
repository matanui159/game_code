#include "input.h"
#include "util.h"

void wheel_input_create(wheel_input_t* input, const char* path) {
	input->file = wheel_util_file(path, "rb");
	input->path = path;
	input->line = 1;
	input->peek = -1;
}

void wheel_input_destroy(wheel_input_t* input) {
	fclose(input->file);
}

char wheel_input_peek(wheel_input_t* input) {
	if (input->peek == -1) {
		input->peek = fgetc(input->file);
		
		if (input->peek < ' ' || input->peek > '~') {
			if (input->peek == -1) {
				input->peek = 0;
			} else {
				wheel_input_error(input,
					"Invalid character $%02X", input->peek
				);
			}
		}
		if (input->peek == '\n') {
			++input->peek;
		}
	}
	return input->peek;
}

char wheel_input_next(wheel_input_t* input) {
	char next = wheel_input_peek(input);
	input->peek = -1;
	return next;
}

void wheel_input_error(wheel_input_t* input, const char* fmt, ...) {
	va_list list;
	va_start(list, fmt);

	va_list copy;
	va_copy(copy, list);
	int size = vsnprintf(NULL, 0, fmt, copy) + 1;
	va_end(copy);

	char buffer[size];
	vsnprintf(buffer, size, fmt, list);
	va_end(list);
	wheel_util_error("[%s:%i] %s", input->path, input->line, buffer);
}