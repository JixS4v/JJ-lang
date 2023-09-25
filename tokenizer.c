#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>
#include <stdlib.h>

typedef enum token_types{IDENTIFIER, ASSIGN, INT, INT_LITERAL, LEFT_PARENS, RIGHT_PARENS, SEMICOLON}token;

regex_t separator_regex;
regex_t number_regex;
int OG_token_size = 16;
int OG_symbol_table_size = 20;

token to_token(char set[])
{
	switch(set[0])
	{
		case '=':
			return 	ASSIGN;
		case '(':
			return LEFT_PARENS;
		case ')':
			return RIGHT_PARENS;
		case ';':
			return SEMICOLON;
	}
	if(strcmp(set, "int"))
	{
		return INT;
	}
	if(regexec(&number_regex, set, 0, NULL, 0)==0)
	{
		printf("found int literal");
		return INT_LITERAL;
	}
	return IDENTIFIER;
}

bool is_separator(char character)
{
	char t_char[1];
	t_char[0] = character;
	
	if(regexec(&separator_regex, t_char, 0, NULL, 0)==0)	
	{
		return true;
	}
	return false;
}

int main(int argc, char *argv[])
{
	regcomp(&separator_regex, "=*\(*)*;*\s*\n*", 0);
	regcomp(&number_regex, "^[0-9]*$", 0);

	FILE* pCode;
	
	pCode = fopen("code.j", "r");
	token* token_array;
	token_array = malloc(OG_symbol_table_size*sizeof(token));
	printf("Allocated token array for the first time \n");
	int token_array_size = 0;

	char currentCharacter;
	char* charBuffer;
	charBuffer = malloc(OG_token_size*sizeof(char));
	printf("allocated character buffer for the first time \n");
	int char_buffer_size = 0;

	do{
		currentCharacter = fgetc(pCode);
		if(is_separator(currentCharacter))
		{
			if(char_buffer_size==0&&currentCharacter!=' ')
			{
				charBuffer[0] = currentCharacter;
				token_array[token_array_size] = to_token(charBuffer);
				token_array_size++;
				memset(charBuffer, 0, sizeof(char));
				continue;
			}
			if(token_array_size>=OG_symbol_table_size)
			{
				printf("line 82");
				token_array=realloc(token_array, (token_array_size+1)*sizeof(token));
			}	
			token_array[token_array_size] = to_token(charBuffer);
			token_array_size++;
			memset(charBuffer, 0, sizeof(char)*char_buffer_size);
			char_buffer_size = 0;
			if(currentCharacter!=' ')
			{
				charBuffer[0] = currentCharacter;
				if(token_array_size>=OG_symbol_table_size)
				{
					printf("Line 93");
					token_array = realloc(token_array, (token_array_size+1)*sizeof(token));
				}
				token_array[token_array_size] = to_token(charBuffer);
				token_array_size++;
				memset(charBuffer, 0, sizeof(char));
			}
			continue;
		}
		if(char_buffer_size>=OG_token_size)
		{
			printf("Line 103");
			charBuffer = realloc(charBuffer, (char_buffer_size+1)*sizeof(char));	
		}
		charBuffer[char_buffer_size] = currentCharacter;
		char_buffer_size++;
		printf("added to the char buffer");
	}
	while(currentCharacter != EOF);
	free(charBuffer);
	printf("token_array %i \n", token_array);
	fclose(pCode);
}


