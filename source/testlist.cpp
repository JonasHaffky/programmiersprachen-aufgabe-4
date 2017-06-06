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
	List<int> list(std::vector<int>{5,2,8});
	REQUIRE(5 == list.front());
	REQUIRE(8 == list.back());
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
	List<int> list (std::vector<int>{8,2,4});
	REQUIRE(3 == list.size());
	list.clear();
	REQUIRE(list.empty());
}

// AUFGABE 4.5 und 4.6
TEST_CASE("iterator initializations", "[ListIterator]")
{
	List<int> list (std::vector<int>{8,2,4});
	
	ListIterator<int> it {};
	it = list.begin();
	REQUIRE(*it == 8);

	auto auto_it = list.begin();
	REQUIRE(*auto_it == 8);

	ListIterator<int> it_begin {list.begin()};
	REQUIRE(*it_begin == 8);

	ListIterator<int> it_end {list.end()};
	REQUIRE(*it_end == 4);
}

TEST_CASE("operator-> test", "[ListIterator]")
{
	List<Circle> circle_list;
	circle_list.push_back(Circle{8});
	circle_list.push_back(Circle{6});
	circle_list.push_back(Circle{7});

	auto it = circle_list.begin();

	int x = it->m_radius;
	REQUIRE(x == 8);

	it->warp();
	REQUIRE(it->m_radius == 0);

}

TEST_CASE("should be a empty range after default construction", "[iterators]")
{
	List<int> list;
	
	auto b = list.begin();
	auto e = list.end();
	REQUIRE(b == e);

	list.push_front(9);
	e = list.end();
	REQUIRE(b != e);
}

TEST_CASE("provide access to the first element with begin", "[iterators]")
{
	List<int> list;
	list.push_front(18);
	REQUIRE(18 == *list.begin());
}

// AUFGABE 4.7
TEST_CASE ("== and != operator", "[list comparison]")
{
	List<int> list1;
	list1.push_front(12);
	
	List<int> list2;
	list2.push_front(12);
	
	List<int> list3;
	list3.push_front(24);

	REQUIRE(list1 == list2);
	REQUIRE(list1 != list3);
}


int main(int argc, char* argv[])
{
    return Catch::Session().run(argc, argv);
    return 0;
}