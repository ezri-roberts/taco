#ifndef SCRIPT_H
#define SCRIPT_H

#include "tcpch.h"

enum {

	TOKEN_ILLEGAL,
	TOKEN_EOF,
	TOKEN_IDENT,
	TOKEN_LOCATION,
	TOKEN_DECLARE,
	TOKEN_NAME,
	TOKEN_CHOICE,
	TOKEN_TEXT,
	TOKEN_JUMP,
	TOKEN_TRUE,
	TOKEN_FALSE,
	TOKEN_NUM,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_EQUAL,
	TOKEN_LESS,
	TOKEN_GREATER,
};

enum {

	LINE_LOCATION,
	LINE_TEXT,
	LINE_CHOICE,
	LINE_JUMP,
	LINE_DECLARE,
	LINE_LOGIC,
};

typedef struct {

	int type;
	char *literal;
} Token;

typedef struct Line {

	int type;
	char *prefix;
	char *contents;
} Line;

typedef struct {

	const char *input;
	int position;
	int read_position;
	char ch;
	Line lines[1000];
} Lexer;

void script_read_file(const char *path);
Token token_new(int type, char *literal);
Lexer lexer_new();
void lexer_read_char(Lexer *lexer);
Line lexer_read_line(char *str);
Token lexer_next_token(Lexer *lexer);
void lexer_read_identifier(Lexer *lexer, Token *tok);
char* lexer_get_line_prefix(char *line);
int lexer_get_line_type(char *prefix);
char* lexer_get_character_name(char *line);
const char* _line_type_tostring(Line *line);
char _get_line_prefix(const char *line);
void _trim_whitespace(char *str);
int _lookup_ident(const char *ident);
bool _is_letter(char ch);
bool _is_symbol_prefix(char ch);
char* _remove_prefix(const char *str);

#endif // !SCRIPT_H
