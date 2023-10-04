#include "types.h"

typedef struct NODE NODE; //Forward reference
typedef struct TREE TREE;
typedef struct FUNCTION FUNCTION;

// A basic node, one operation that can be nested if one value references the result of another operation
struct NODE{
	enum {
		NUMBER,
		DEFINT,
		ASSIGNVAR,
		ADD,
	}tag;
	union {
		struct NUMBER {int number;} NUMBER;// regular-ass number 
		struct IDENTIFIER {char* identifier;} IDENTIFIER;// variable name
		struct DEFINT { NODE *identifier;} DEFINT;// define operator of a variable
		struct ASSIGN { NODE *identifier; NODE *value;} ASSIGN;// opperation to assign a variable
	       	struct ADD { NODE *left; NODE *right;} ADD;// performs a sum of two values	
	}data;
};
//Linked List elementst that contain different operations(define and assign for instance), linear execution.
struct TREE{
	NODE node;
	TREE* next;
};

struct FUNCTION{
	//arguments, malloced array
	NODE* arguments;
	//pointer to the first node of the linked list
	TREE* first;
	//returning functionality
	datatype returnType;
	NODE* returnValue;
};	
