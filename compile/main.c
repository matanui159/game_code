#include "input.h"
#include "lexer.h"
#include <stdio.h>

int main() {
	wheel_input_init("test.txt");
	wheel_token_t token;

	while ((token = wheel_lexer_next()).type != WHEEL_TOKEN_EOF) {
		switch (token.type) {
			case WHEEL_TOKEN_NEWLINE:
				printf("NEW LINE\n");
			case WHEEL_TOKEN_SYMBOL:
				printf("SYMBOL '%c'\n", token.symbol);
				break;
			case WHEEL_TOKEN_NUMBER:
				printf("NUMBER %i\n", token.number);
				break;
			case WHEEL_TOKEN_NAME:
				printf("NAME %s\n", token.string);
				break;
			default:
				printf("UNKNOWN\n");
		}
	}
	return 0;
}