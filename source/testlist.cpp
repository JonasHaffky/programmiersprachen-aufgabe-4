#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "list.hpp"

//Aufgabe 4.2
TEST_CASE("empty", "[List]")
{
    List<int> l1;
    REQUIRE(l1.empty()==true);
}

TEST_CASE("size", "[List]")
{

	List<int> l1;
	REQUIRE(l1.size()==0);
}

// AUFGABE4.3

TEST_CASE("add an element with push_front", "[modifiers]")
{
	List<int> l2;
	l2.push_front(19);
	REQUIRE(l2.front()==19);
}

TEST_CASE("add an element with push_back", "[modifiers]")
{
	List<int> list;
	list.push_back(54);
	REQUIRE(list.back()==54);
}

TEST_CASE("remove an element with pop_front", "[modifiers]")
{
	List<int> list;
	list.push_front(42);
	REQUIRE(42 == list.front());
	REQUIRE(42 == list.back());
	
	list.push_front(12);

	REQUIRE(12 == list.front());
	REQUIRE(42 == list.back());

	list.pop_front();
	REQUIRE(42 == list.front());

	list.pop_front();
	REQUIRE(list.size() == 0);
}

TEST_CASE("remove an element with pop_back", "[modifiers]")
{
	List<int> list;
	list.push_front(42);
	REQUIRE(42 == list.front());
	REQUIRE(42 == list.back());
	
	list.push_front(12);

	REQUIRE(12 == list.front());
	REQUIRE(42 == list.back());

	list.pop_back();
	REQUIRE(12 == list.front());

	list.pop_back();
	REQUIRE(list.size() == 0);
}

int main(int argc, char* argv[])
{
    return Catch::Session().run(argc, argv);
    return 0;
}