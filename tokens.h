typedef enum token_types{IDENTIFIER, ASSIGN, INT, INT_LITERAL, SUM_OPERATOR, LEFT_PARENS, RIGHT_PARENS, LEFT_BRACKET, RIGHT_BRACKET, SEMICOLON}token;

typedef struct
{
	token token;
	char* string;
} symbol;
