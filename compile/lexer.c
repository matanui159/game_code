#include "lexer.h"
#include "input.h"
#include "buffer.h"
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

static wheel_token_t g_peek = {.type = WHEEL_TOKEN_NONE};

static void lexer_error(char c, const char* expect) {
	switch (c) {
		case 0:
			g_peek.type = WHEEL_TOKEN_EOF;
			break;
		case '\n':
			g_peek.type = WHEEL_TOKEN_NEWLINE;
			break;
		default:
			g_peek.type = WHEEL_TOKEN_SYMBOL;
			g_peek.symbol = c;
			break;
	}
	wheel_lexer_error(&g_peek, expect);
}

static bool lexer_isname(char c) {
	return isalnum(c) || c == '_' || c == '.';
}

static int lexer_nexthex() {
	char c = wheel_input_next();
	if (!isxdigit(c)) {
		lexer_error(c, "hex digit");
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

static uint8_t lexer_nextchar() {
	uint8_t c = wheel_input_next();
	if (c == 0) {
		lexer_error(c, "character");
	} else if (c == '\\') {
		c = wheel_input_next();
		
		switch (c) {
			case 't':
				c = '\t';
				break;
			case 'n':
				c = '\n';
				break;
			case 'x':
				c = (lexer_nexthex() << 4) | lexer_nexthex();
				break;
		}
	}
	return c;
}

static void lexer_number(uint32_t number) {
	if (number > UINT16_MAX) {
		wheel_input_error("Invalid number %i", number);
	}
	g_peek.type = WHEEL_TOKEN_NUMBER;
	g_peek.number = number;
}

wheel_token_t wheel_lexer_peek() {
	if (g_peek.type == WHEEL_TOKEN_NONE) {
		char c;
		while (isspace(c = wheel_input_peek()) && c != '\n') {
			wheel_input_next();
		}

		if (c == '\0') {
			g_peek.type = WHEEL_TOKEN_EOF;
		} else if (c == '\n') {
			wheel_input_next();
			g_peek.type = WHEEL_TOKEN_NEWLINE;
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
				number += lexer_nexthex();
			}
			lexer_number(number);

		} else if (c == '\'') {

			wheel_input_next();
			g_peek.type = WHEEL_TOKEN_NUMBER;
			g_peek.number = lexer_nextchar();
			if ((c = wheel_input_next()) != '\'') {
				lexer_error(c, "closing quote");
			}

		} else if (lexer_isname(c)) {

			g_peek.type = WHEEL_TOKEN_NAME;
			g_peek.string = NULL;
			while (lexer_isname(wheel_input_peek())) {
				stb_sb_push(g_peek.string, toupper(wheel_input_next()));
			}
			stb_sb_push(g_peek.string, 0);

		} else if (c == '"') {

			wheel_input_next();
			g_peek.type = WHEEL_TOKEN_STRING;
			g_peek.string = NULL;
			while (wheel_input_peek() != '"') {
				stb_sb_push(g_peek.string, lexer_nextchar());
			}
			stb_sb_push(g_peek.string, 0);
			wheel_input_next();

		} else {
			lexer_error(c, "token character");
		}
	}
	return g_peek;
}

wheel_token_t wheel_lexer_next() {
	wheel_token_t next = wheel_lexer_peek();
	g_peek.type = WHEEL_TOKEN_NONE;
	return next;
}

void wheel_lexer_error(wheel_token_t* token, const char* expect) {
	switch (token->type) {
		case WHEEL_TOKEN_EOF:
			wheel_input_error("Expected %s, got end of file", expect);
		case WHEEL_TOKEN_NEWLINE:
			wheel_input_error("Expected %s, got new line", expect);
		case WHEEL_TOKEN_SYMBOL:
			wheel_input_error("Expected %s, got `%c`", expect, token->symbol);
		case WHEEL_TOKEN_NUMBER:
			wheel_input_error("Expected %s, got %i", expect, token->number);
		case WHEEL_TOKEN_NAME:
			wheel_input_error("Expected %s, got %s", expect, token->string);
		case WHEEL_TOKEN_STRING:
			wheel_input_error("Expected %s, got \"%s\"", expect, token->string);
		default:
			wheel_input_error("Expected %s", expect);
	}
}