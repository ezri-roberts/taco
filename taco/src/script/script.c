#include "script.h"
#include <ctype.h>
#include <string.h>

static const char *line_types[] = {
	"LINE_LOCATION",
	"LINE_TEXT",
	"LINE_CHOICE",
	"LINE_JUMP",
	"LINE_DECLARE",
	"LINE_LOGIC",
};

Token token_new(int type, char *literal) {

	Token tok;
	tok.type = type;
	tok.literal = literal;
	tok.literal[strlen(tok.literal)] = '\0';

	return tok;
}

Lexer lexer_new() {

	Lexer lexer;

	// lexer.input = input;
	lexer.position = 0;
	lexer.read_position = 0;
	lexer.ch = 0;

	// lexer_read_char(&lexer);

	return lexer;
}

void script_read_file(const char *path) {

	FILE *file;

    // Open the file
    file = fopen(path, "r");

    // Check if the file was opened successfully
	TC_ASSERT(file, "Could not open script.");

	Lexer lexer = lexer_new();
    // Read and print the contents line by line
	int line_number = 0;
    char line[1000]; // Adjust this buffer size according to your needs
    while (fgets(line, sizeof(line), file) != NULL) {

		_trim_whitespace(line);
		line[strcspn(line, "\n")] = 0; // Remove newline.
		line[strcspn(line, "\r")] = 0; // Remove newline.
		line[strcspn(line, "\t")] = 0; // Remove newline.

		// Skip empty lines.
		if (line[0] == '\0' || line[0] == '`') continue;
		// printf("|%s|\n", line);
		TC_INFO(line);
		lexer.lines[line_number] = lexer_read_line(line);
		line_number++;
    }


    // Close the file
    fclose(file);
}

Line lexer_read_line(const char *str) {

	Line line;

	char prefix = str[0];
	char *val = _remove_prefix(str);
	_trim_whitespace(val);

	// if (_is_symbol_prefix(prefix)) {

		line.prefix = &prefix;
		line.contents = val;
		line.type = lexer_get_line_type(line.prefix);
		TC_INFO(_line_type_tostring(&line));

		// printf("|%c|", prefix);
		// printf("%lu\n", strlen(str));
		// printf("|%s|\n", val);
		free(val);
	// } else { // Dialogue
	// 	
	// }

	return line;
}

void lexer_read_char(Lexer *lexer) {

	if (lexer->read_position >= strlen(lexer->input)) {
		lexer->ch = 0;
	} else {
		lexer->ch = lexer->input[lexer->read_position];
	}

	lexer->position = lexer->read_position;
	lexer->read_position++;
}

Token lexer_next_token(Lexer *lexer) {

	Token tok;

	switch (lexer->ch) {

		default:
			if (_is_letter(lexer->ch)) {

				lexer_read_identifier(lexer, &tok);
				tok.type = TOKEN_IDENT;
				// TC_INFO("%s, %s", _token_tostring(&tok), tok.literal);
				return tok;
			} else {
				tok = token_new(TOKEN_ILLEGAL, &lexer->ch);
			}
		case '@':
			tok = token_new(TOKEN_LOCATION, &lexer->ch); break;
		case '*':
			tok = token_new(TOKEN_CHOICE, &lexer->ch); break;
		case '#':
			tok = token_new(TOKEN_JUMP, &lexer->ch); break;
		case '$':
			tok = token_new(TOKEN_DECLARE, &lexer->ch); break;
		case '+':
			tok = token_new(TOKEN_PLUS, &lexer->ch); break;
		case '=':
			tok = token_new(TOKEN_EQUAL, &lexer->ch); break;
		case '<':
			tok = token_new(TOKEN_LESS, &lexer->ch); break;
		case '>':
			tok = token_new(TOKEN_GREATER, &lexer->ch); break;
		case 0:
			tok = token_new(TOKEN_EOF, "");
		
	}

	// TC_INFO("%s, %s", _token_tostring(&tok), tok.literal);
	printf("%s\n", tok.literal);

	lexer_read_char(lexer);
	return tok;
}

void lexer_read_identifier(Lexer *lexer, Token *tok) {

	int pos = lexer->position;
	
	while (_is_letter(lexer->ch)) {
		lexer_read_char(lexer);
	}

	int len = lexer->position - pos; 

	strncpy(tok->literal, lexer->input + pos, len);
	tok->literal[len] = '\0';
}

bool _is_letter(char ch) {
	return 'a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z' || ch == '_';
}

bool _is_symbol_prefix(char ch) {

	return ch == '@' ||
		ch == '$' || 
		ch == '*' ||
		ch == '#' ||
		ch == '+' ||
		ch == '-' ||
		ch == '=' ||
		ch == '<' ||
		ch == '>';
}

void _trim_whitespace(char *str) {

	int start = 0;
	int end = strlen(str);

	char current = str[start];
	// Start
	while (isspace(current)) {

		start++;
		current = str[start];
	}

	current = str[end];
	// End 
	while (isspace(current)) {

		end--;
		current = str[end];
	}

	strncpy(str, str + start, end);
	str[end] = '\0';
}

const char* _line_type_tostring(Line *line) {
	return line_types[line->type];
}

char* _remove_prefix(const char *str) {

	int len = strlen(str);
    
    // Allocate memory for the new string (len - 1) characters plus the null terminator
    char *new_str = (char *)malloc(len);

    if (new_str == NULL) {
        // Memory allocation failed
        return NULL;
    }

    // Copy characters from the original string starting from the second character
    // to the new string
    strcpy(new_str, str + 1);

    return new_str;
}

int lexer_get_line_type(char *prefix) {

	switch (*prefix) {

		case '@':
			return LINE_LOCATION; break;	
		case '*':
			return LINE_CHOICE; break;	
		case '#':
			return LINE_JUMP; break;	
	}

	return LINE_TEXT;
}
