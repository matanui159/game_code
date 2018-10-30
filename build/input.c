#include "input.h"
#include "file.h"
#include <au/log.h>
#include <au/string.h>
#include <stdarg.h>

void wheel_input_create(wheel_input_t* input, const char* path) {
	input->file = wheel_file_open(path, "rb");
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
	au_string_t string;
	au_string_create(&string);
	au_string_add(&string, "%s:%i", input->file, input->line);

	va_list list;
	va_start(list, fmt);
	au_vlog_fail(string.data, fmt, list);
}