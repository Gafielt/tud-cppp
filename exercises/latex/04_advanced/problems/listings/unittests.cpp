#include <UnitTest++/UnitTest++.h>

#include "List.hpp"

TEST(ListSimpleUsageTest)
{
	// Teste appendElement und deleteFirst für List<int>
  // Wie sind die erwarteten Werte von getSize() und ggf. getFirstElement()?
}

TEST(ListAdvancedUsageTest) {
	
	// Füge an eine List<double> Elemente an und an beliebieger Stelle eine
	// prüfe,ob das n-te Element für jeden Eintrag der Erwartung entpricht
}

TEST(ListIteratorTest)
{
	// Nutze den Iterator um wortweise "Hello World!" einer Liste hinzuzufügen.
}

TEST(ExceptionsTest)
{
	// Teste die 3 Methoden, bei denen Exceptions auftreten können.
}

int main(int, char **)
{
	return UnitTest::RunAllTests();
}
