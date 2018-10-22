#include "build.h"
#include "lexer.h"
#include <stdio.h>

void wheel_build(const char* path) {
	printf("BUILD: %s\n", path);
	wheel_token_t token = wheel_lexer_next();
	wheel_lexer_error(&token, "nothing");
}