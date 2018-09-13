#include <UnitTest++/UnitTest++.h>

#include "List.hpp"

TEST(ListSimpleUsageTest)
{
	// teste appendElement und deleteFirst für List<int>
}

TEST(ListAdvancedUsageTest) {
	
	// füge an eine List<double> Elemente an und an beliebieger Stelle eine
	// prüfe,ob das n-te Element für jeden Eintrag der Erwartung entpricht
}

TEST(ListIteratorTest)
{
	// Nutze den Iterator um wortweise "Hello World!" einer Liste hinzuzufügen
}

TEST(ExceptionsTest)
{
	// teste die 3 Methoden, bei denen Exceptions auftreten können
}

int main(int,char **)
{
	return UnitTest::RunAllTests();
}
