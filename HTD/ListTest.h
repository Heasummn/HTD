#pragma once
#include <iostream>
#include "list.h"

using namespace htd;
class ListTests
{

public:
	void runAllTests()
	{
		runCtorTests();
		runIteratorTests();
	}

	void runCtorTests()
	{
		{
			std::cout << "Empty List can be created" << std::endl;
			list<int> emptyList;
			std::cout << "Passed" << std::endl << std::endl;

			std::cout << "List can be range created" << std::endl;
			list<int> list_5(5, 7); // A list of 5 7's
			std::cout << "Passed" << std::endl << std::endl;
		}
	}

	void runIteratorTests()
	{
		std::cout << "Iterator can be used to loop through list" << std::endl;
		list<int> list_5(5, 7);
		for (list<int>::iterator i = list_5.begin(); i != list_5.end(); i++)
		{ }
		std::cout << "Passed" << std::endl << std::endl;
	}
};