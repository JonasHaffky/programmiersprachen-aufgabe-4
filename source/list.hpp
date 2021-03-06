#ifndef BUW_LIST_HPP
#define BUW_LIST_HPP

#include <cstddef>
#include <iterator>
#include <typeinfo>
#include <iostream>

struct Circle //einfacher Kreis für Tests
{
	Circle (int radius) : m_radius(radius) {};
	int m_radius;
	void warp () {m_radius = 0;}
};

template <typename T> //Deklaratio vom struct List
struct List;

template <typename T> //Definition vom struct ListNode
struct ListNode
{
    ListNode() : m_value(), m_prev(nullptr), m_next(nullptr) {}
    ListNode(T const& v, ListNode* prev, ListNode* next)
        : m_value(v), m_prev(prev), m_next(next)
    {}
    T m_value;
    ListNode* m_prev;
    ListNode* m_next;
};

template <typename T>
struct ListIterator
{
	typedef ListIterator<T> Self;

	typedef T value_pointer;
	typedef T* pointer;
	typedef T& reference;
	typedef ptrdiff_t difference_type;
	typedef std::forward_iterator_tag iterator_category;

    friend class List<T>; //erlaubt Zugriff auf Membervariablen

	//Konstruktoren
	ListIterator () {}
	ListIterator(ListNode<T>* n) : m_node(n) {}
    
	reference operator*() const //dereference operator, gibt Werte die in Node gespeichert sind aus (by reference, not by value)
	{
		return m_node->m_value;
	}

	pointer operator->() const //dereference operator, gibt Pointer auf Werte die in Node gespeichert sind aus
	{
		return &(m_node->m_value);
	}

	//Prefix Increment
	Self& operator++() //gibt Referenz zu ListIterator<T> zurück, hochzählender Iterator
	{
		*this = next(); //next() gibt neuen ListIterator aus, weißt ListIterator sich selbst zu (kopiert Wert vom neuen Listiterator nach sich selbst)

		return *this; //gibt sich selbst als Referenz zurück (keinen Pointer zu sich selbst als Referenz)
	}

	//Prefix Decrement
	Self& operator--() //Verminderungsiterator
	{
		*this = prev(); //prev() gibt neuen ListIterator aus, weißt ListIterator sich selbst zu (kopiert Wert vom neuen Listiterator nach sich selbst)

		return *this; //gibt sich selbst als Referenz zurück (keinen Pointer zu sich selbst als Referenz)
	}

	// Post Increment
	Self operator++(int) //Referenz auf ListIterator<value_pointer>
	{
		ListIterator<T> temp(*this);
		operator++(); // Prefix-Increment von dieser Instanz
		return temp; //gibt alte Instanz zurück
	}

	// Post Decrement
	Self operator--(int) //Referenz auf ListIterator<value_pointer>, funktioniert nicht dür list.end()
	{
		ListIterator<T> temp(*this);
		operator--(); // Prefix-Decrement von dieser Instanz
		return temp; //gibt alte Instanz zurück
}

	bool operator==(const Self& x) const //Vergleich ob Iteratoren auf gleichen Knoten zeigen, nicht gleicher Wert
	{
		return m_node == x.m_node;
	}

	bool operator!=(const Self& x) const
	{
		return m_node != x.m_node;
	}

	//return next node
	Self next() const
	{
		if(m_node)
			return ListIterator(m_node->m_next);
		else
			return ListIterator(nullptr);
	}

	//return next node
	Self prev() const
	{
		if(m_node)
			return ListIterator(m_node->m_prev);
		else
			return ListIterator(nullptr);
	}

	private:
        ListNode<T>* m_node = nullptr; //Pointer von Iterator auf Node, der mit nullpointer initialisiert wird 
};

template <typename T>
struct ListConstIterator
{
    friend class List<T>;
public:
// not implemented yet
private:
    ListNode<T>* m_node = nullptr;
};

template <typename T>
class List
{
public:
	//set aliases for data types
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef ListIterator<T> iterator;
    typedef ListConstIterator<T> const_iterator;

    friend class ListIterator<T>;
    friend class ListConstIterator<T>;
    
    // Aufgabe 4.2 
    List():m_first(nullptr),m_last(nullptr),m_size(0){}; //Default Konstructor

	List(std::vector<value_type> const& values) : //Konstruktor mit Vektor
				m_size{0},
				m_first{nullptr},
				m_last{nullptr}
	{
		for (value_type value : values)
			push_back(value);
	}

	List(int size) :
				m_size{0},
				m_first{nullptr},
				m_last{nullptr}
	{
		for (int i = 0; i<size; ++i)
		{
			push_back(0);
		}
	}

	bool empty() const{return m_first == nullptr && m_last == nullptr;}
    std::size_t size() const{return m_size;}
    
    //Aufgabe 4.3
    void push_front(value_type value) //pushes element to front of list
	{
		//Case List empty
		if (m_size == 0)
		{
			//m_first zeigt auf das neue element
			m_first = new ListNode<T>{
				value, 		//T
				nullptr, 	//pointer auf prev
				nullptr 	//pointer auf next
			};

			//m_first und m_last zeigen auf das
			//einzige Element der Liste
			m_last = m_first;
		}

		//Case List not empty
		else
		{
			//former_first und m_first referenzieren
			//den front node
			ListNode<T>* former_first = m_first;

			//ListNode<T>* m_first referenziert den
			//neuen front node, dessen next der former_
			m_first = new ListNode<T>{
				value, 			//T
				nullptr, 		//pointer auf prev
				former_first 	//pointer auf next
			};

			//prev pointer des 2. elements
			//zeigt jetzt auf das front element
			former_first->m_prev = m_first;
		}

		++ m_size;
	}

	void push_back(value_type value) //pushs element to back of list
	{
		//Case List empty
		if (m_size == 0)
		{
			push_front(value);
		}

		//Case List not empty
		else
		{
			ListNode<T>* former_last = m_last;

			m_last = new ListNode<T>{
				value, former_last, nullptr};

			former_last->m_next = m_last;

			++ m_size;
		}
	}

	value_type pop_front()//removes front element of list and returns it's value
	{
		//Case List empty
		if (m_size == 0)
		{
			//ERROR???
		}
		//Case List has one element
		else if (m_size == 1)
		{
			//erstes element zwischenspeichern
			ListNode<T>* former_first = m_first;
			
			m_first = nullptr;
			m_last = nullptr;

			--m_size;
			return former_first->m_value;
			
		}
		//Case List has multiple elements
		else
		{				
			//erstes element zwischenspeichern
			ListNode<T>* former_first = m_first;
			
			//front zeigt auf das element auf das next
			//des ehm. front auch zeigt
			m_first = former_first->m_next;

			//das prev element von front wird auf nullptr umgebogen
			m_first->m_prev = nullptr;
            -- m_size;
			return former_first->m_value;
		}
	}
	
	
	value_type pop_back() //removes front element of list and returns it's value
	{
		//Case List empty
		if (m_size == 0)
		{
			//ERROR???
		}
		//Case List has one element
		else if (m_size == 1)
		{
			return pop_front();	
		}
		//Case List has multiple elements
		else
		{				
			//letztes element zwischenspeichern
			ListNode<T>* former_last = m_last;
			
			//front zeigt auf das element auf das next
			//des ehm. front auch zeigt
			m_last = former_last->m_prev;

			//das prev element von front wird auf nullptr umgebogen
			m_last->m_next = nullptr;
            -- m_size;
			return former_last->m_value;
		}
	}
	
	//returns value of front element
	value_type front() const
	{
		return m_first->m_value;
	}
	
	//returns value of back element
	value_type back() const
	{
		return m_last->m_value;
	}

	//Aufgabe 4.4
	void clear()
	{
		while(!empty())
			pop_front();
	}

	//Destructor
	~List(){clear();}

	//Aufgabe 4.6
	iterator begin () const
	{
		if (m_first)
			return iterator(m_first);
		else
			return iterator(nullptr);
	}

	iterator end () const
	{
		return iterator(nullptr);
	}

//Aufgabe 4.8
List(List<T> const& x) : m_size{0}, //copy-Konstruktor
				m_first{nullptr},
				m_last{nullptr}
	{
		auto it = x.begin();
		while(it != nullptr)
		{
			push_back(*it);
			++it;
		}
	}

//Aufgabe 4.9
void insert (iterator it, const T& obj)
	{
		if (m_size == 0)
			push_front(obj);

		else if(it == begin())
			push_front(obj);
		
		else if(it == end())
			push_back(obj);
		
		else
		{
			ListNode<T>* old = it.m_node; //old speichert iteratornode zwischen

			ListNode<T>* prev = it.m_node->m_prev;

			ListNode<T>* insert = new ListNode<T>{
				obj, 		//T
				prev, 	//Pointer auf prev 
				old		//Pointer auf next mit nullptr initialisieren
			};

			
			old->m_prev = insert; //Zeiger von old zu neuem Element
			prev->m_next = insert; //Zeiger von prev zu neuem Element
			++ m_size;
		}
}
//Aufgabe 4.10
void reverse ()
	{
		if (m_size > 1)
		{
			//Liste temp wird mit gleicher Größe angelegt
			int x = size();
			List<T> temp{x};

			//Iterator auf erstes this Element, und auf letztes temp Element
			iterator first = this->begin();
			iterator second = temp.begin();

			for(int j = 1; j<x; ++j)
			{
				++second;
			}
			
			for(int i = 0; i<x; ++i) //nicht sehr schön aber funktioniert
			{
				*second = *first;
				--second;
				++first;
			}

			*this = temp;
		} 
}

/*Aufgabe 4.12
List& operator=(List rhs)
{
	swap(rhs);
	return *this;
}

void swap(List & rhs)
{
	std::swap(m_first, rhs.m_first);
	std::swap(m_last, rhs.m_last);
}

Aufgabe 4.13
List(List&& listmove):
	m_first{listmove.m_first},m_last{listmove.m_last},m_size{listmove.m_size}{

		listmove.m_first = nullptr;
		listmove.m_last = nullptr;
		listmove.m_size = 0;
}*/

private:
    std::size_t m_size = 0;
    ListNode<T>* m_first = nullptr;
    ListNode<T>* m_last = nullptr;
};

template<typename T>
bool operator==(List<T> const& xs, List<T> const& ys)
{
	if(xs.size() == ys.size())
	{
		//jedes Element wird verglichen
		auto it_xs = xs.begin();
		auto it_ys = ys.begin();

		while(it_xs != nullptr) //solange it_xs kein nullpointer ist (Ende der Liste), überprüfe ob die Werte der Nodes gleich sind
		{
			if(*it_xs != *it_ys) //vergleiche
				return false;
			++it_xs;
			++it_ys;
		}
		return true;
	}
	else
		return false;
}

template<typename T>
bool operator!=(List<T> const& xs, List<T> const& ys)
{
	return !(xs==ys);
}

template<typename T>
List<T> reverse (List<T> const& list)
{
	List<T> temp {list};
	temp.reverse();
	return temp;
}

#endif // #define BUW_LIST_HPP