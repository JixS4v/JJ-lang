#include "array.h"
#include <string.h>
#include <stdlib.h>

void* append_to_array(void* array, int array_current_index, void* to_append, size_t size_of_type){
	void* arrayPtr = realloc(array , size_of_type*(array_current_index+ 1));
	memcpy(arrayPtr+array_current_index, to_append, size_of_type);
	return arrayPtr;
}
