#ifndef WHEEL_LEXER_H_
#define WHEEL_LEXER_H_
#include <stdint.h>

typedef enum wheel_token_type_t {
	WHEEL_TOKEN_NONE = -1,
	WHEEL_TOKEN_EOF,
	WHEEL_TOKEN_NEWLINE,
	WHEEL_TOKEN_SYMBOL,
	WHEEL_TOKEN_NUMBER,
	WHEEL_TOKEN_NAME,
	WHEEL_TOKEN_STRING
} wheel_token_type_t;

typedef struct wheel_token_t {
	wheel_token_type_t type;
	union {
		char symbol;
		uint16_t number;
		char* string;
	};
} wheel_token_t;

wheel_token_t wheel_lexer_peek();
wheel_token_t wheel_lexer_next();
void wheel_lexer_error(wheel_token_t* token, const char* expect);

#endif