#include "stack.h"

#ifdef __cplusplus
#include <cstdlib>
#include <cstring>
#include <cassert>
#else
#include "stdlib.h"
#include "string.h"
#include "assert.h"
#endif

static void Stack_grow(Stack *s)
{
	s->alloc_length *= 2;
	s->elems = realloc(s->elems, s->sizeof_elem * s->alloc_length);
}

void Stack_init(Stack *s, int elemSize, void (*freefn)(void *elem))
{
	s->sizeof_elem = elemSize;
	s->length = 0;
	s->alloc_length = 4;
	s->elems = malloc(s->sizeof_elem * s->alloc_length);
	s->freefn = freefn;
	assert(s->elems != NULL);
}

void Stack_delete(Stack *s)
{
	if (s->freefn) {
		for (int i = 0; i < s->length; i++) {
			s->freefn((char *) s->elems + s->sizeof_elem * i);
		}
	}

	free(s->elems);
}

void Stack_push(Stack *s, void *val)
{
	if (s->length == s->alloc_length) {
		Stack_grow(s);
	}

	void *dest = (char *) s->elems + s->length * s->sizeof_elem;
	memcpy(dest, val, s->sizeof_elem);
	s->length++;
}

void Stack_pop(Stack *s, void *where)
{
	if (s->length == 0) {
		return;
	}

	void *top_elem = (char *) s->elems + (s->length - 1) * s->sizeof_elem;
	memcpy(where, top_elem, s->sizeof_elem);
	s->length--;
}
