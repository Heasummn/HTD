#pragma once
#include <iostream>
#include "list.h"

using namespace HTD;
class ListTests
{

public:
	void runAllTests()
	{
		runCtorTests();
	}

	void runCtorTests()
	{
		{
			std::cout << "Empty List can be created" << std::endl;
			list<int> emptyList;
			std::cout << "Passed" << std::endl << std::endl;
		}


	}
};