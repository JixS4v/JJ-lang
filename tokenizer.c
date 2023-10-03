#include <string.h>
#include <ctype.h>
#include <regex.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "tokens.h"

typedef struct 
{
	token token;
	char* string;
} symbol;

regex_t separator_regex;
regex_t number_regex;
int OG_token_size = 1;
int OG_symbol_table_size = 1;

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

int main(int argc, char *argv[])
{
	regcomp(&number_regex, "^[0-9]*$", 0);

	FILE* pCode;
	
	pCode = fopen("code.j", "r");
	symbol* token_array;
	token_array = malloc(OG_symbol_table_size*sizeof(symbol));

	printf("Allocated token array for the first time \n");
	int token_array_size = 0;

	char currentCharacter;
	char* charBuffer;
	charBuffer = malloc(OG_token_size*sizeof(char));
	memset(charBuffer, 0, OG_token_size*sizeof(char));
	printf("allocated character buffer for the first time \n");
	int char_buffer_size = 0;

	do{
		printf("Token number %i \n", token_array_size);
		currentCharacter = fgetc(pCode);
		if(currentCharacter == EOF){
			continue;
		}
		if(is_separator(currentCharacter))
		{
			printf("Found Separator \n");
			if(token_array_size>=OG_symbol_table_size)
			{
				token_array=realloc(token_array,(token_array_size+1)*sizeof(symbol));
				printf("Resizing token array \n");
			}	
			if(char_buffer_size==0)
			{
				if(isspace(currentCharacter)){
					continue;
				}
				charBuffer[0] = currentCharacter;
				token_array[token_array_size] = make_symbol(charBuffer);
				token_array_size++;
				memset(charBuffer, 0, sizeof(char));
				charBuffer=realloc(charBuffer, OG_token_size*sizeof(char));
				continue;
			}
			
			token_array[token_array_size] = make_symbol(charBuffer);
			token_array_size++;
			memset(charBuffer, 0, sizeof(char)*char_buffer_size);
			charBuffer=realloc(charBuffer, OG_token_size*sizeof(char));
			char_buffer_size = 0;
			if(!isspace(currentCharacter))
			{
				if(token_array_size>=OG_symbol_table_size)
				{
					token_array=realloc(token_array, (token_array_size+1)*sizeof(symbol));
					printf("Resizing token array \n");
				}	
				charBuffer[0] = currentCharacter;
				token_array[token_array_size] = make_symbol(charBuffer);
				token_array_size++;
				char_buffer_size = 0;
				memset(charBuffer, 0, sizeof(char)*1);
			}
			continue;
		}
		if(char_buffer_size>=OG_token_size)

		{
			charBuffer = realloc(charBuffer, (char_buffer_size+1)*sizeof(char));	
			printf("Resizing character buffer \n");
		}
		charBuffer[char_buffer_size] = currentCharacter;
		char_buffer_size++;
		printf("added to the char buffer \n");
	}
	while(currentCharacter != EOF);
	if(char_buffer_size>0)
	{
		if(token_array_size >= OG_symbol_table_size)
		{
			token_array= realloc(token_array, (token_array_size+1)*sizeof(symbol));
			token_array[token_array_size] = make_symbol(charBuffer);
		}	
		
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


