#include "lexer.h"
#include "util.h"
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

static void lexer_error(wheel_lexer_t* lexer, char c, const char* expect) {
	switch (c) {
		case 0:
			lexer->peek.type = WHEEL_TOKEN_EOF;
			break;
		case '\n':
			lexer->peek.type = WHEEL_TOKEN_NEWLINE;
			break;
		default:
			lexer->peek.type = WHEEL_TOKEN_SYMBOL;
			lexer->peek.symbol = c;
			break;
	}
	wheel_lexer_error(lexer, &lexer->peek, expect);
}

static bool lexer_isname(char c) {
	return isalnum(c) || c == '_' || c == '.';
}

static int lexer_nexthex(wheel_lexer_t* lexer) {
	char c = wheel_input_next(&lexer->input);
	if (!isxdigit(c)) {
		lexer_error(lexer, c, "hex digit");
	}

	if (c <= '9') {
		return c - '0';
	} else if (c <= 'F') {
		return c - 'A' + 10;
	} else if (c <= 'f') {
		return c - 'a' + 10;
	} else {
		return 0;
	}
}

static uint8_t lexer_nextchar(wheel_lexer_t* lexer) {
	uint8_t c = wheel_input_next(&lexer->input);
	if (c == 0) {
		lexer_error(lexer, c, "character");
	} else if (c == '\\') {
		c = wheel_input_next(&lexer->input);
		
		switch (c) {
			case 't':
				c = '\t';
				break;
			case 'n':
				c = '\n';
				break;
			case 'x':
				c = (lexer_nexthex(lexer) << 4) | lexer_nexthex(lexer);
				break;
		}
	}
	return c;
}

static void lexer_number(wheel_lexer_t* lexer, uint32_t number) {
	if (number > UINT16_MAX) {
		wheel_input_error(&lexer->input, "Invalid number %i", number);
	}
	lexer->peek.type = WHEEL_TOKEN_NUMBER;
	lexer->peek.number = number;
}

void wheel_lexer_create(wheel_lexer_t* lexer, const char* path) {
	wheel_input_create(&lexer->input, path);
	lexer->peek.type = WHEEL_TOKEN_NONE;
}

wheel_token_t wheel_lexer_peek(wheel_lexer_t* lexer) {
	if (lexer->peek.type == WHEEL_TOKEN_NONE) {
		char c;
		while (isspace(c = wheel_input_peek(&lexer->input)) && c != '\n') {
			wheel_input_next(&lexer->input);
		}

		if (c == '\0') {

			lexer->peek.type = WHEEL_TOKEN_EOF;

		} else if (c == '\n') {

			wheel_input_next(&lexer->input);
			lexer->peek.type = WHEEL_TOKEN_NEWLINE;

		} else if (strchr("=:-+~", c) != NULL) {

			lexer->peek.type = WHEEL_TOKEN_SYMBOL;
			lexer->peek.type = wheel_input_next(&lexer->input);

		} else if (isdigit(c)) {

			uint32_t number = 0;
			while (isdigit(wheel_input_peek(&lexer->input))) {
				number *= 10;
				number += wheel_input_next(&lexer->input) - '0';
			}
			lexer_number(lexer, number);

		} else if (c == '$') {

			wheel_input_next(&lexer->input);
			uint32_t number = 0;
			while (isxdigit(wheel_input_peek(&lexer->input))) {
				number <<= 4;
				number += lexer_nexthex(lexer);
			}
			lexer_number(lexer, number);

		} else if (c == '\'') {

			wheel_input_next(&lexer->input);
			lexer->peek.type = WHEEL_TOKEN_NUMBER;
			lexer->peek.number = lexer_nextchar(lexer);
			if ((c = wheel_input_next(&lexer->input)) != '\'') {
				lexer_error(lexer, c, "closing quote");
			}

		} else if (lexer_isname(c)) {

			lexer->peek.type = WHEEL_TOKEN_NAME;
			lexer->peek.string = NULL;
			while (lexer_isname(wheel_input_peek(&lexer->input))) {
				c = toupper(wheel_input_next(&lexer->input));
				stb_sb_push(lexer->peek.string, c);
			}
			stb_sb_push(lexer->peek.string, 0);

		} else if (c == '"') {

			wheel_input_next(&lexer->input);
			lexer->peek.type = WHEEL_TOKEN_STRING;
			lexer->peek.string = NULL;
			while (wheel_input_peek(&lexer->input) != '"') {
				stb_sb_push(lexer->peek.string, lexer_nextchar(lexer));
			}
			stb_sb_push(lexer->peek.string, 0);
			wheel_input_next(&lexer->input);

		} else {

			lexer_error(lexer, c, "token character");

		}
	}
	return lexer->peek;
}

wheel_token_t wheel_lexer_next(wheel_lexer_t* lexer) {
	wheel_token_t next = wheel_lexer_peek(lexer);
	lexer->peek.type = WHEEL_TOKEN_NONE;
	return next;
}

void wheel_lexer_error(wheel_lexer_t* lexer, wheel_token_t* token, const char* expect) {
	switch (token->type) {
		case WHEEL_TOKEN_EOF:
			wheel_input_error(&lexer->input,
				"Expected %s, got end of file", expect
			);
		case WHEEL_TOKEN_NEWLINE:
			wheel_input_error(&lexer->input,
				"Expected %s, got new line", expect
			);
		case WHEEL_TOKEN_SYMBOL:
			wheel_input_error(&lexer->input,
				"Expected %s, got `%c`", expect, token->symbol
			);
		case WHEEL_TOKEN_NUMBER:
			wheel_input_error(&lexer->input,
				"Expected %s, got %i", expect, token->number
			);
		case WHEEL_TOKEN_NAME:
			wheel_input_error(&lexer->input,
				"Expected %s, got %s", expect, token->string
			);
		case WHEEL_TOKEN_STRING:
		wheel_input_error(&lexer->input,
				"Expected %s, got \"%s\"", expect, token->string
			);
		default:
			wheel_input_error(&lexer->input,
				"Expected %s", expect
			);
	}
}