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

TEST_CASE("add multiple elements with push_front", "[modifiers]")
{
	List<int> list(std::vector<int>{1,2,3});
	REQUIRE(1 == list.front());
	REQUIRE(3 == list.back());
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

//AUFGABE 4.4

TEST_CASE("clear list", "[modifiers]")
{
	List<int> list;
	list.push_front(19);
	list.push_front(8);
	list.push_front(12);
	REQUIRE(list.size()==3);
	list.clear();
	REQUIRE(list.empty());
}

int main(int argc, char* argv[])
{
    return Catch::Session().run(argc, argv);
    return 0;
}