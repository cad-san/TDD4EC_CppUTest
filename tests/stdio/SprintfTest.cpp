#include "CppUTest/TestHarness.h"

extern "C"
{
#include <stdio.h>
#include <memory.h>
}

TEST_GROUP(sprintf)
{
	char output[100];
	const char * expected;

	void setup()
	{
		memset(output, 0xaa, sizeof(output));
		expected = "";
	}

	void teardown()
	{
	}

	void expect(const char* s)
	{
		expected = s;
	}

	void given(int charWritten)
	{
		LONGS_EQUAL(strlen(expected), charWritten);
		STRCMP_EQUAL(expected, output);
		BYTES_EQUAL(0xaa, output[strlen(expected) + 1]);
	}
};


TEST(sprintf, NoFormatOperations)
{
	expect("hey");
	given(sprintf(output, "hey"));
}

TEST(sprintf, InsertString)
{
	expect("Hello World\n");
	given(sprintf(output, "%s\n", "Hello World"));
}
