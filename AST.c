#include "AST.h"
#include "tokens.h"
#include <stdlib.h>
#include <string.h>

TREE* convert_to_AST(symbol* symbol_array, int symbol_array_size)
{
	TREE* flow = malloc(sizeof(TREE));
	int tree_current_index = 0;
	FUNCTION* function_array = malloc(sizeof(FUNCTION));
	int function_array_current_index = 0;
	int i;
	for(i=0; i <= symbol_array_size; i++) {
		switch(symbol_array[i].token)
		{
			case IDENTIFIER:
				break;
			case INT:
				if(symbol_array[i+1].token==IDENTIFIER)
				{
					switch(symbol_array[i+2].token)
					{
						case LEFT_PARENS:
							break;
					}
				}
				break;

		}
	}
}
void* append_to_array(void* array, int array_current_index, void* to_append, size_t size_of_type){
	void* arrayPtr = realloc(array , size_of_type*(array_current_index+ 1));
	memcpy(arrayPtr+array_current_index, to_append, size_of_type);
	return arrayPtr;
}
