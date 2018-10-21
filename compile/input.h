#ifndef WHEEL_INPUT_H_
#define WHEEL_INPUT_H_

void wheel_input_init(const char* path);
char wheel_input_peek();
char wheel_input_next();
void wheel_input_error(const char* fmt, ...);

#endif