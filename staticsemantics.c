#include "staticsemantics.h"

Stack * createStackNode(char *label){
	Stack * ns = (Stack *) malloc (sizeof(struct stack));
	ns->label = malloc(sizeof(label + 1));
	ns->label = label;
	ns->next = NULL;	
	ns->last = NULL;

	return ns;
}

void push(Stack *top, char *label){

	if(top == NULL){
		top = createStackNode(label);
	} else {
		Stack * ptr = createStackNode(label);
		top->next = ptr;
		top->next->last = top;
		top->next->next = NULL;
	}
}

void pop(Stack *top){
	printf("The label is: %s\n", top->label);
	
	if(top->last != NULL){
		top->last->next = NULL;
	}
}

int checkStack(Stack * top, char *label){
	Stack * ptr = top;
	int i = 0;
	while(ptr != NULL){
		if(strcmp(ptr->label, label) == 0){
			printf("Found at %d\n", i);
			return 1;
		} else {
			ptr = ptr->last;
			i += 1;
		}
	}
	printf("%s not found in stack\n", label);
	return 0;
}

void stackPrint(Stack *top){
	Stack * ptr = top;
	int i = 0;
	while(ptr != NULL){
		printf("Stack element %d from top is %s\n", i, ptr->label);
		ptr = ptr->last;
		i += 1;
	}
}

Stack * staticsem(int lvl, TreeNode *root, Stack *top)
{
//	printf("In staticsem function \n");

    if (root != NULL)
    {
//	printf("In staticsem, root not null\n");
        
    	if (strcmp(root->label, "<vars>") == 0){
    		if(root->head != NULL){
    			if(checkStack(top, root->head->tok->tokenName) != 1){
    				printf("Token name put on stack: %s\n", root->head->tok->tokenName);
    				if (top == NULL){
    					top = createStackNode(root->head->tok->tokenName);
    				} else {
    					push(top, root->head->tok->tokenName);
    					top = top->next;
    				}
    			} else {
    				printf("Error in static semantics, tree level %d! Variable %s already declared! Exiting..\n", lvl, root->head->tok->tokenName);
    				exit(1);
    			}
    		}
    	} else if (strcmp(root->label, "R") == 0){
    		if(root->head->tok->tokenID == 1000){
    			// printf("Token ID: %d\n", root->head->tok->tokenID);
    			if(checkStack(top, root->head->tok->tokenName) != 1){
    				printf("Error in static semantics, tree level %d! Variable %s is not defined in stack! Exiting..\n", lvl, root->head->tok->tokenName);
    			}
    		}
    	}
//	else {
//		printf("In static semantics, root-> label does not match any\n");
//}                 

        top = staticsem(lvl + 1, root->child1, top);
        top = staticsem(lvl + 1, root->child2, top);
        top = staticsem(lvl + 1, root->child3, top);
        top = staticsem(lvl + 1, root->child4, top);



    }

return top;
}
