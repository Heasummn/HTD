#include <iostream>
#include "StringTest.h"
#include "ListTest.h"

int main() {
	std::cout << "******************************" << std::endl;
	std::cout << "*    RUNNING STRING TESTS    *" << std::endl;
	std::cout << "******************************" << std::endl;
	StringTests StrTest;
	StrTest.runAllTests();
	std::cout << "*******************************" << std::endl;
	std::cout << "*    FINISHED STRING TESTS    *" << std::endl;
	std::cout << "*******************************" << std::endl << std::endl << std::endl;

	std::cout << "******************************" << std::endl;
	std::cout << "*     RUNNING LIST TESTS     *" << std::endl;
	std::cout << "******************************" << std::endl;
	ListTests ListTest;
	ListTest.runAllTests();
	std::cout << "*******************************" << std::endl;
	std::cout << "*     FINISHED LIST TESTS     *" << std::endl;
	std::cout << "*******************************" << std::endl << std::endl << std::endl;

	return 0;
}