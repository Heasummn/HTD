#pragma once
#include <iostream>
#include <exception>
#include "string.h"

using namespace htd;

class StringTests
{
public:

	// MAJOR TODO: Clean up Tests by what they do and properly test everything
	void runAllTests()
	{
		std::cout << "Assert: Under 7 char string can be created" << std::endl;
		string foo("foo");
		std::cout << "Passed" << std::endl << std::endl;

		std::cout << "Assert: Over 7 char string can be created" << std::endl;
		string over8Chars("I am a really big string");
		std::cout << "Passed" << std::endl << std::endl;

		// Corner case, was unforseen
		std::cout << "Assert: Power of two char string can be created" << std::endl;
		string exactly16Chars("aaaaaaaaaaaaaa");
		std::cout << "Passed" << std::endl << std::endl;

		isEqual("Assert: Length of foo is equal to 3", foo.length() == 3);

		string empty;
		isEqual("Assert: Length of empty string is equal to 0", empty.length() == 0);

		isEqual("Assert: foo.at(0) returns f", foo.at(0) == 'f');
		assertSanity(foo, 3, "foo");

		{
			std::cout << "Assert: .at throws Out Of Range error" << std::endl;
			try {
				foo.at(21);
			}
			catch (...) {
				std::cout << "Passed" << std::endl << std::endl;
			}
		}

		isEqual("Assert: Front of foo is 'f'", foo.front() == 'f');
		assertSanity(foo, 3, "foo");

		isEqual("Assert: Back of foo is 'o'", foo.back() == 'o');
		assertSanity(foo, 3, "foo");

		{ // Test modification operator[]
			std::cout << "Assert: String can be modified using operator[]" << std::endl;
			foo[0] = 'd';
			if (foo.at(0) == 'd')
			{
				std::cout << "Passed" << std::endl;
				assertSanity(foo, 3, "doo");
			}
			else
				std::cout << "Failed" << std::endl;
			foo[0] = 'f'; // Reset it
			assertSanity(foo, 3, "foo");
			std::cout << "\n";
		} // End Test modification operator[]

		{ // Test modification .at()
			std::cout << "Assert: String can be modified using at" << std::endl;
			foo.at(0) = 'd';
			if (foo.at(0) == 'd')
			{
				std::cout << "Passed" << std::endl;
				assertSanity(foo, 3, "doo");
			}
			else
				std::cout << "Failed" << std::endl;
			foo.at(0) = 'f'; // Reset it
			assertSanity(foo, 3, "foo");
			std::cout << "\n";
		} // End Test modification .at()

		isEqual("Assert: == works as expected, check 1, same", foo == "foo");
		isEqual("Assert: == works as expected, check 2, different lengths", foo == "f", "FAILED", "Passed");
		isEqual("Assert: == works as expected, check 3, same lengths", foo == "boo", "FAILED", "Passed");

		isEqual("Assert: != works as expected, check 1, same lengths", foo != "boo");
		isEqual("Assert: != works as expected, check 2, different lengths", foo != "oo");
		isEqual("Assert: != works as expected, check 3, same", foo != "boo");

		foo.swap(over8Chars);
		isEqual("Assert: swap properly changes values", foo == "I am a really big string" && over8Chars == "foo"); // swap
		assertSanity(foo, 24, "I am a really big string");
		assertSanity(over8Chars, 3, "foo");

		foo.swap(over8Chars); // revert
		isEqual("Assert: swap properly reverts values", foo == "foo" && over8Chars == "I am a really big string"); // swap
		assertSanity(over8Chars, 24, "I am a really big string");
		assertSanity(foo, 3, "foo");

		foo.pop_back();
		isEqual("Assert: pop off works on normal string", foo == "fo");
		assertSanity(foo, 2, "fo");

		foo.push_back('o'); // revert
		isEqual("Assert: push back works on normal string", foo == "foo");
		assertSanity(foo, 3, "foo");

		isEqual("Assert: find works on char as input and normal string", foo.find('o') == 1);
		isEqual("Assert: find works on strings as input and normal string", foo.find("oo") == 1);
		isEqual("Assert: find works to find first char", foo.find('f') == 0);
		isEqual("Assert: find works to find itself", foo.find("foo") == 0);
		isEqual("Assert: find fails to find unavailable string #1", foo.find("bar") == foo.npos);
		isEqual("Assert: find fails to find unavailable string #2", foo.find("op") == foo.npos);
		isEqual("Assert: find fails to find unavailable string #3", over8Chars.find("gp") == over8Chars.npos);
		assertSanity(foo, 3, "foo");
	}

	void isEqual(htd::string message, bool assertion, htd::string pass = "Passed", htd::string fail = "FAILED")
	{
		std::cout << message.data() << std::endl;
		if (assertion)
			std::cout << pass.data();
		else
			std::cout << fail.data();
		std::cout << "\n" << std::endl;

	}

	void assertSanity(htd::string variable, size_t length, char* data)
	{
		if (variable.length() != length)
		{
			std::cout << "SANITY FAILED, length is not equal" << std::endl << std::endl;
			return;
		}

		size_t counter = 0;
		while (counter < length)
		{
			if (*(variable.data() + counter) != *(data + counter))
			{
				std::cout << "SANITY FAILED, values are not equal" << std::endl;
				std::cout << *(data + counter) << " != " << *(variable.data() + counter) << std::endl << std::endl;
				return;
			}
			counter++;
		}

	}
};