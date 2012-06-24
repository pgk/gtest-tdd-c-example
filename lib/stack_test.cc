#include "stack.h"
#include "gtest/gtest.h"
#include <cstring>

void str_freefn(void *str)
{
	free(*(char **) str);
}

class StackTest : public testing::Test {
protected:
	virtual void SetUp() { Stack_init(&s, sizeof(int), NULL); }
	virtual void TearDown() { Stack_delete(&s); }
	Stack s;
};

TEST_F(StackTest, PushesValueToStackIncreaseLength) {
	int pushVal = 1;
	Stack_push(&s, (void *) &pushVal);
	EXPECT_EQ(1, s.length);
}

TEST_F(StackTest, PushesValueToStackIncreaseLengthAndReallocIfInsufficient) {
	int pushVal = 1;
	for (int i = 0; i < 5; i++) {
		Stack_push(&s, (void *) &pushVal);
	}

	EXPECT_EQ(5, s.length);
}

TEST_F(StackTest, PopFromTopOfStack) {
	int pushVal[3] = {1, 2, 3};
	int popVal;

	for (int i = 0; i < 3; i++) {
		Stack_push(&s, (void *) &pushVal[i]);
	}

	Stack_pop(&s, &popVal);
	EXPECT_EQ(2, s.length);
	EXPECT_EQ(3, popVal);
}

TEST_F(StackTest, NotWriteAnythingIfNoElemsInStack) {
	int popVal = NULL;
	Stack_pop(&s, &popVal);
	EXPECT_EQ(NULL, popVal);
}

TEST_F(StackTest, DeleteOwnedElements) {
	Stack d;
	Stack_init(&d, sizeof(char *), str_freefn);
	const char *pushVals[3] = {"Alice", "Bob", "Carl"};

	for (int i = 0; i < 3; i++) {
		char *name = strdup(pushVals[i]);
		Stack_push(&d, (void *) &name);
	}

	Stack_delete(&d);
}
