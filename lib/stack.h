#ifndef STACK_H
#define STACK_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _stack {
	void *elems;
	int sizeof_elem;
	int length;
	int alloc_length;
	void (*freefn)(void *);
} Stack;

void Stack_init(Stack *s, int elemSize, void (*freefn)(void *));
void Stack_delete(Stack *s);
void Stack_push(Stack *s, void *val);
void Stack_pop(Stack *s, void *where);

#ifdef __cplusplus
}
#endif

#endif