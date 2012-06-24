#include "stack.h"
#include "gtest/gtest.h"
#include <cstring>

void str_freefn(void *str)
{
	free(*(char **) str);
}

TEST(Stack_push, PushesValueToStackIncreaseLength) {
	Stack s;
	Stack_init(&s, sizeof(int), NULL);
	int pushVal = 1;
	Stack_push(&s, (void *) &pushVal);
	EXPECT_EQ(1, s.length);
	Stack_delete(&s);
}

TEST(Stack_push, PushesValueToStackIncreaseLengthAndReallocIfInsufficient) {
	Stack s;
	Stack_init(&s, sizeof(int), NULL);
	int pushVal = 1;
	for (int i = 0; i < 5; i++) {
		Stack_push(&s, (void *) &pushVal);
	}

	EXPECT_EQ(5, s.length);
	Stack_delete(&s);
}

TEST(Stack_pop, PopFromTopOfStack) {
	Stack s;
	Stack_init(&s, sizeof(int), NULL);
	int pushVal[3] = {1, 2, 3};
	int popVal;

	for (int i = 0; i < 3; i++) {
		Stack_push(&s, (void *) &pushVal[i]);
	}

	Stack_pop(&s, &popVal);
	EXPECT_EQ(2, s.length);
	EXPECT_EQ(3, popVal);
	Stack_delete(&s);
}

TEST(Stack_pop, NotWriteAnythingIfNoElemsInStack) {
	Stack s;
	Stack_init(&s, sizeof(int), NULL);
	int popVal = NULL;

	Stack_pop(&s, &popVal);
	EXPECT_EQ(NULL, popVal);
	Stack_delete(&s);
}

TEST(Stack_delete, DeleteOwnedElements) {
	Stack s;
	Stack_init(&s, sizeof(char *), str_freefn);
	const char *pushVals[3] = {"Alice", "Bob", "Carl"};

	for (int i = 0; i < 3; i++) {
		char *name = strdup(pushVals[i]);
		Stack_push(&s, (void *) &name);
	}

	Stack_delete(&s);
}
