#include "lexer.h"
#include "input.h"
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

static wheel_token_t g_peek = {.type = WHEEL_TOKEN_NONE};

static void lexer_number(uint32_t number) {
	if (number > UINT16_MAX) {
		wheel_input_error("Invalid number %i", number);
	}
	g_peek.type = WHEEL_TOKEN_NUMBER;
	g_peek.number = number;
}

static bool lexer_isname(char c) {
	return isalnum(c) || c == '_' || c == '.';
}

wheel_token_t wheel_lexer_peek() {
	if (g_peek.type == WHEEL_TOKEN_NONE) {
		char c;
		while (isspace(c = wheel_input_peek())) {
			wheel_input_next();
		}

		if (c == '\0') {
			g_peek.type = WHEEL_TOKEN_EOF;
		} else if (strchr("=:-+~", c) != NULL) {

			g_peek.type = WHEEL_TOKEN_SYMBOL;
			g_peek.symbol = wheel_input_next();

		} else if (isdigit(c)) {

			uint32_t number = 0;
			while (isdigit(wheel_input_peek())) {
				number *= 10;
				number += wheel_input_next() - '0';
			}
			lexer_number(number);

		} else if (c == '$') {

			wheel_input_next();
			uint32_t number = 0;
			while (isxdigit(wheel_input_peek())) {
				number <<= 4;
				char c = wheel_input_next();
				if (c <= '9') {
					number += c - '0';
				} else if (c <= 'F') {
					number += c - 'A' + 10;
				} else if (c <= 'f') {
					number += c - 'a' + 10;
				}
			}
			lexer_number(number);

		// } else if (lexer_isname(c)) {



		} else {
			wheel_input_error("Invalid character '%c'", c);
		}
	}
	return g_peek;
}

wheel_token_t wheel_lexer_next() {
	wheel_token_t next = wheel_lexer_peek();
	g_peek.type = WHEEL_TOKEN_NONE;
	return next;
}