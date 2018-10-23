#ifndef WHEEL_UTIL_H_
#define WHEEL_UTIL_H_
#include <stdio.h>
#include <stdarg.h>

void wheel_util_verror(const char* fmt, va_list list);
void wheel_util_error(const char* fmt, ...);
FILE* wheel_util_file(const char* path, const char* mode);

#endif