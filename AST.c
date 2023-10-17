#include "AST.h"
#include "tokens.h"
#include <stdlib.h>
#include <string.h>
#include "array.h"

int look_ahead(symbol* symbol_array, int index, token look_for, int max_length)
{
	i;
	for(i=index; i<max_length; i++)
	{
		if(symbol_array[i].token==look_for)
		{
			return i;
		}
	}
	return 0;
}
TREE* get_tree_at_index(TREE* first, int index)
{
	TREE* current=first;
	int i;
	for(i=0; i<index; i++)
	{
		current = *current.next;
	}
	return current;
}

TREE* convert_to_AST(symbol* symbol_array, int starting_index, int final_index)
{
	TREE* flow = malloc(sizeof(TREE));
	int tree_current_index = 0;
	FUNCTION* function_array = malloc(sizeof(FUNCTION));
	int function_array_current_index = 0;
	int i;
	for(i=starting_index; i <=final_index; i++) {
		switch(symbol_array[i].token)
		{
			case IDENTIFIER:
				//TODO: Call function if is function call
				break;
			case INT:
				if(symbol_array[i+1].token==IDENTIFIER)
				{
					if(symbol_array[i+2].token==LEFT_PARENS)
					{
							//a function definition
						int right_paren_index=  look_ahead(symbol_array, i+3, RIGHT_PARENS, final_index+1);
						if(right_paren_index!=0)
							if(symbol_array[right_paren_index+1].token == LEFT_BRACKET)
							{
								int right_bracket_index = look_ahead(symbol_array, right_paren_index+2, RIGHT_BRACKET, final_index+1);
								if(right_bracket_index == 0)
								{
									print("Match your fuckin brackets");
								}
								else
								{
									char* funcName = /*TODO: copy string from identifier*/;
									FUNCTION newFunc = {name, /*TODO: argument parsing*/, convert_to_AST(symbol_array, right_paren_index+2, right_bracket_index - 1), TYPE_INT, /*TODO: hahah return values*/};
									append_to_array(function_array, function_array_current_index, &newFunc, sizeof(FUNCTION));
								}

							}
							else
							{
								print("Fuckin asshole learn to define a function properly");
							}
						}
						else
						{
							print("Unmatched parenthesis you fucking asshole");
						}
					}
					else
					{
						//define an int
						NODE* identifier = malloc(sizeof(NODE));
						*identifier = (NODE){
							NODE_IDENTIFIER,
							{
								.NODE_IDENTIFIER=(struct NODE_IDENTIFIER){
									strcpy(symbol_array[i+1].string)
								};
							}
						};
						NODE defint_node = (NODE){
							DEFINT,
							{
								.DEFINT = (struct DEFINT){identifier}	
							}
						};

						TREE* defint = malloc(sizeof(tree));
						TREE* current = get_tree_at_index(flow, tree_current_index);
						current->next=defint;
						defint->node = defint_node;
					}
				}
				break;
			case ASSIGN:
				NODE* identifier = malloc(sizeof(NODE));
				*identifier = (NODE){
					NODE_IDENTIFIER,
					{
						.NODE_IDENTIFIER = (struct NODE_IDENTIFIER){strcpy(symbol_array[i-1].string)};
					}
				};
				int semicolon_index = look_ahead(symbol_array, i+1, SEMICOLON, final_index+1);
				TREE* value = convert_to_AST(symbol_array, i+1, semicolon_index-1);
				NODE* value_node = malloc(sizeof(NODE));
				*value_node = *value.node; 
				
				break;		

		}
	}
}
