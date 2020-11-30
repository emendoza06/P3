#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "tree.h"


// structure defining stack
typedef struct stack {

	char *label;
	struct stack *next;
	struct stack *last;

} Stack;

Stack * createStackNode(char *label);

void push(Stack * stack, char *label);

void pop(Stack* stack);

void stackPrint(Stack *stk);

Stack * staticsem(int lvl, TreeNode *root, Stack *top);

int checkStack(Stack * top, char *label);
