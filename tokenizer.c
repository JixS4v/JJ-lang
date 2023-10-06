#include <string.h>
#include <ctype.h>
#include <regex.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "tokens.h"
#include "array.h"

regex_t separator_regex;
regex_t number_regex;

token to_token(char* set)
{
	printf("Tokenizing %s \n",set);
	switch(set[0])
	{
		case '=':
			return 	ASSIGN;
		case '+':
			return SUM_OPERATOR;
		case '(':
			return LEFT_PARENS;
		case ')':
			return RIGHT_PARENS;
		case '{':
			return LEFT_BRACKET;
		case '}':
			return RIGHT_BRACKET;
		case ';':
			return SEMICOLON;
	}
	if(strcmp(set, "int")==0)
	{
		return INT;
	}
	if(regexec(&number_regex, set, 0, NULL, 0)==0)
	{
		printf("found int literal \n");
		return INT_LITERAL;
	}
	return IDENTIFIER;
}

symbol make_symbol(char* set)
{
	symbol newsymb;
	newsymb.token = to_token(set);
	newsymb.string = strdup(set);
	return newsymb;
}

bool is_separator(char character)
{
	return (isspace(character) || character == '=' || character == '(' || character == ')' || character == ';' );
}

void free_symbol(symbol* to_free, int length)
{
	int i;
	for(i=0;i<length;i++)
	{
		free(to_free[i].string);
	}
	free(to_free);
}

int main(int argc, char *argv[])
{
	regcomp(&number_regex, "^[0-9]*$", 0);

	FILE* pCode;
	
	pCode = fopen("code.jj", "r");
	symbol* token_array;
	token_array = malloc(sizeof(symbol));

	printf("Allocated token array for the first time \n");
	int token_array_size = 0;

	char currentCharacter;
	char* charBuffer;
	charBuffer = malloc(sizeof(char));
	memset(charBuffer, 0, sizeof(char));
	printf("allocated character buffer for the first time \n");
	int char_buffer_size = 0;

	symbol current_symbol;
	do{
		printf("Token number %i \n", token_array_size);
		currentCharacter = fgetc(pCode);
		if(currentCharacter == EOF){
			continue;
		}
		if(is_separator(currentCharacter))
		{
			printf("Found Separator \n");
			if(char_buffer_size==0)
			{
				if(isspace(currentCharacter)){
					continue;
				}
				charBuffer[0] = currentCharacter;
				current_symbol = make_symbol(charBuffer);
				token_array = append_to_array(token_array, token_array_size, &current_symbol, sizeof(symbol));
				token_array_size++;
				memset(charBuffer, 0, sizeof(char));
				charBuffer=realloc(charBuffer, sizeof(char));
				continue;
			}
			current_symbol = make_symbol(charBuffer);
			token_array = append_to_array(token_array, token_array_size, &current_symbol, sizeof(symbol));
			token_array_size++;
			memset(charBuffer, 0, sizeof(char)*char_buffer_size);
			charBuffer=realloc(charBuffer, sizeof(char));
			char_buffer_size = 0;
			if(!isspace(currentCharacter))
			{
				charBuffer[0] = currentCharacter;
				current_symbol = make_symbol(charBuffer);
				token_array = append_to_array(token_array, token_array_size, &current_symbol, sizeof(symbol));
				token_array_size++;
				char_buffer_size = 0;
				memset(charBuffer, 0, sizeof(char)*1);
			}
			continue;
		}
		append_to_array(charBuffer, char_buffer_size, &currentCharacter, sizeof(char));
		char_buffer_size++;
		printf("added to the char buffer \n");
	}
	while(currentCharacter != EOF);
	if(char_buffer_size>0)
	{
		current_symbol = make_symbol(charBuffer);
		token_array = append_to_array(token_array, token_array_size, &current_symbol, sizeof(symbol));
	}
	else
	{
		token_array_size-=1;
	}
	free(charBuffer);
	printf("token_array %i \n", token_array);
	int i;
	for(i = 0; i<=token_array_size; i++){
		printf("Token number %i: %i = \"%s\" \n",i,token_array[i].token, token_array[i].string);
	}
	fclose(pCode);
}


