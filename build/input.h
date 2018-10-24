#ifndef WHEEL_INPUT_H_
#define WHEEL_INPUT_H_
#include <stdio.h>

typedef struct wheel_input_t {
	FILE* file;
	const char* path;
	int line;
	int peek;
} wheel_input_t;

void wheel_input_create(wheel_input_t* input, const char* path);
void wheel_input_destroy(wheel_input_t* input);
char wheel_input_peek(wheel_input_t* input);
char wheel_input_next(wheel_input_t* input);
void wheel_input_error(wheel_input_t* input, const char* fmt, ...);

#endif