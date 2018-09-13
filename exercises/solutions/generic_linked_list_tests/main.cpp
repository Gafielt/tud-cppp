#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>

#include <UnitTest++/UnitTest++.h>

#include "List.hpp"

TEST(ListSimpleUsageTest)
{
	List<int> testList;
	
	testList.appendElement(3);
	CHECK_EQUAL(testList.getSize(), 1);
	CHECK_EQUAL(testList.getFirst(), 3);
	
	testList.deleteFirst();
	CHECK_EQUAL(testList.getSize(), 0);
}

TEST(ListAdvancedUsageTest) {
	List<double> testList;
	
	testList.insertElementAt(1.0, 0);
	testList.appendElement(2.0);
	testList.appendElement(3.0);
	testList.insertElementAt(1.5, 1);
	
	CHECK_EQUAL(1.0, testList.getNthElement(0));
	CHECK_EQUAL(1.5, testList.getNthElement(1));
	CHECK_EQUAL(2.0, testList.getNthElement(2));
	CHECK_EQUAL(3.0, testList.getNthElement(3));
	CHECK_EQUAL(3.0, testList.getLast());
	
}

TEST(ListIteratorTest)
{
	List<std::string> testList;
	testList.appendElement("Hello");
	testList.appendElement("World");
	testList.appendElement("!");
	
	for (ListIterator<std::string> iter = testList.begin(); iter != testList.end(); ++iter) {
		std::cout << *iter << " ";
	}
}

TEST(dummy) {
	CHECK_EQUAL(3, dummy());
}

int main(int,char **)
{
	return UnitTest::RunAllTests();
}
