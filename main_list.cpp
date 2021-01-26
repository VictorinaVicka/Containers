#include "List.hpp"
#include "Utils.hpp"

void    list_test(ft::List<int> &list)
{
    ft::List<int>::iterator it;
    ft::List<int>::iterator it2;

    it = list.begin();
    it2 = list.end();
    while (it != it2)
    {
        std::cout << *it << std::endl;
        it++;
    }
}

void    list_test_iterator()
{
    std::cout << "----------ITERATOR----------" << std::endl;

    ft::List<int> list;
    list.push_front(111);
    list.push_front(0);
    list.push_front(777);

    ft::List<int>::iterator it;
    ft::List<int>::iterator it2;
    ft::List<int>::reverse_iterator rit;
    ft::List<int>::reverse_iterator rit2;

    it = list.begin();
    it2 = list.end();
    rit = list.rend();
    rit2 = list.rbegin();

    while (it != it2)
    {
        std::cout << *it << std::endl;
        it++;
    }
    std::cout << "Reverse Enumeration" << std::endl;
    while (rit2 != rit) {
        std::cout << *rit2 << std::endl;
		rit2++;
    }

    it = list.begin();
    std::cout << "begin: " << *it << std::endl;
    it = list.end();
    it--;
    std::cout << "end: " << *it << std::endl;
    rit = list.rbegin();
    std::cout << "rbegin: " << *rit << std::endl;
    rit = list.rend();
	rit--;
    std::cout << "rend: " << *rit << std::endl;

    list.clear();
}

void    list_test_capacity() {
    std::cout << "----------CAPACITY----------" << std::endl;

    ft::List<int> list;
    list_test(list);
    std::cout << "empty ?: " << list.empty() << std::endl;
    std::cout << "size: " << list.size() << std::endl;
    list.push_front(111);
    list.push_front(0);
    list.push_front(0);
    list.push_front(0);
    list.push_front(777);

    list_test(list);

    std::cout << "empty ?: " << list.empty() << std::endl;
    std::cout << "size: " << list.size() << std::endl;
    std::cout << "max size: " << list.max_size() << std::endl;

    list.pop_front();
    list_test(list);

    std::cout << "empty ?: " << list.empty() << std::endl;
    std::cout << "size: " << list.size() << std::endl;

    list.clear();
    list_test(list);
    std::cout << "empty ?: " << list.empty() << std::endl;
    std::cout << "size: " << list.size() << std::endl;
}

void    list_test_access() {
    std::cout << "----------ACCESS----------" << std::endl;

    ft::List<int> list;
    list.push_front(111);
    list.push_front(0);
    list.push_front(0);
    list.push_front(0);
    list.push_front(777);

    list_test(list);

    std::cout << "front: " << list.front() << std::endl;
    std::cout << "back: " << list.back() << std::endl;

    list.clear();
}

void    list_test_assign() {
    std::cout << "----------ASSIGN----------" << std::endl;

    ft::List<int> list;
    list.push_front(111);
    list.push_front(0);
    list.push_front(0);
    list.push_front(0);
    list.push_front(777);

    list_test(list);

    std::cout <<  "Assign" << std::endl;
    list.assign((size_t)8, (const int)42);
    list_test(list);

    ft::List<int> list2;
    list2.push_front(111);
    list2.push_front(0);
    list2.push_front(0);
    list2.push_front(0);
    list2.push_front(777);

    std::cout << "list2" << std::endl;
    list_test(list2);

    std::cout <<  "Assign" << std::endl;
    list.assign(list2.begin(), list2.end());
    list_test(list);

    list.clear();
    list2.clear();
}

void    list_test_push_pop() {
    std::cout << "----------PUSH & POP----------" << std::endl;

    ft::List<int> list;
    list.push_front(111);
    list.push_front(0);
    list.push_front(0);
    list.push_front(0);
    list.push_front(777);

    list_test(list);

    list.pop_front();
    list_test(list);

    list.pop_back();
    list_test(list);

    list.push_back(42);
    list_test(list);

    list.clear();
}

void    list_test_insert() {
    std::cout << "----------INSERT----------" << std::endl;

    ft::List<int> list;
    list.push_front(111);
    list.push_front(0);
    list.push_front(0);
    list.push_front(0);
    list.push_front(777);

    list_test(list);

    list.insert(list.begin(), 42);
    list.insert(list.end(), 42);

    list_test(list);

    list.insert(list.end(), (size_t)8, 3);

    list_test(list);

    ft::List<int> list2(list);

    list.insert(list.end(), list2.begin(), list2.end());

    list_test(list);

    list.clear();
    list2.clear();
}

void    list_test_erase() {
    std::cout << "----------ERASE----------" << std::endl;

    ft::List<int> list;
    list.push_front(111);
    list.push_front(0);
    list.push_front(0);
    list.push_front(0);
    list.push_front(777);

    list_test(list);

    list.erase(list.begin());

    list_test(list);

    ft::List<int>::iterator it;

    it = list.begin();
    it++;

    list.erase(it, list.end());

    list_test(list);

    list.clear();    
}

void    list_test_swap() {
    std::cout << "----------SWAP----------" << std::endl;

    ft::List<int> list;
    list.push_front(111);
    list.push_front(0);
    list.push_front(0);
    list.push_front(0);
    list.push_front(777);

    ft::List<int> list2;
    list2.push_front(42);
    list2.push_front(42);
    list2.push_front(42);
    list2.push_front(42);
    list2.push_front(42);

    std::cout << "list" << std::endl;
    list_test(list);
    std::cout << "list2" << std::endl;
    list_test(list2);

    std::cout << "swap" << std::endl;
    list.swap(list2);

    std::cout << "list" << std::endl;
    list_test(list);
    std::cout << "list2" << std::endl;
    list_test(list2);
}

void    list_test_resize() {
    std::cout << "----------RESIZE----------" << std::endl;

    ft::List<int> list;
    list.push_front(111);
    list.push_front(0);
    list.push_front(0);
    list.push_front(0);
    list.push_front(777);

    list_test(list);

    list.resize(2);
    list_test(list);
    list.resize(8, 42);
    list_test(list);
}

void    list_test_clear() {
    std::cout << "----------CLEAR----------" << std::endl;

    ft::List<int> list;
    list.push_front(111);
    list.push_front(0);
    list.push_front(0);
    list.push_front(0);
    list.push_front(777);

    list_test(list);
    list.clear();
    list_test(list);
}

void    list_test_splice() {
    std::cout << "----------SPLICE----------" << std::endl;

    ft::List<int> list;
    list.push_front(111);
    list.push_front(0);
    list.push_front(0);
    list.push_front(0);
    list.push_front(777);

    ft::List<int> list2;
    list2.push_front(42);
    list2.push_front(42);
    list2.push_front(42);
    list2.push_front(42);
    list2.push_front(42);

    std::cout << "list" << std::endl;
    list_test(list);
    std::cout << "list2" << std::endl;
    list_test(list2);

    std::cout << "splice" << std::endl;
    list.splice(list.end(), list2);
    std::cout << "list" << std::endl;
    list_test(list);
    std::cout << "list2" << std::endl;
    list_test(list2);

    std::cout << "splice" << std::endl;
    list2.splice(list2.end(), list, list.begin());
    std::cout << "list" << std::endl;
    list_test(list);
    std::cout << "list2" << std::endl;
    list_test(list2);

    ft::List<int>::iterator it;
    it = list.begin();
    it++;

    std::cout << "splice" << std::endl;
    list2.splice(list2.end(), list, it, list.end());
    std::cout << "list" << std::endl;
    list_test(list);
    std::cout << "list2" << std::endl;
    list_test(list2);
}

void    list_test_remove() {
    std::cout << "----------REMOVE----------" << std::endl;

    ft::List<int> list;
    list.push_front(111);
    list.push_front(0);
    list.push_front(0);
    list.push_front(0);
    list.push_front(777);

    list_test(list);

    list.remove(0);
    list_test(list);
}

bool predicate1(int i) {
    return i == 42;
}

bool predicate2(int i) {
    return i > 1;
}

void    list_test_remove_if() {
    std::cout << "----------REMOVE IF----------" << std::endl;

    ft::List<int> list;
    list.push_front(111);
    list.push_front(0);
    list.push_front(0);
    list.push_front(0);
    list.push_front(777);

    list_test(list);
    
    list.remove_if(&predicate1);

    list_test(list);

    list.remove_if(&predicate2);

    list_test(list);
}

void    list_test_unique() {
    std::cout << "----------UNIQUE----------" << std::endl;

    ft::List<int> list;
    list.push_front(111);
    list.push_front(111);
    list.push_front(0);
    list.push_front(0);
    list.push_front(0);
    list.push_front(777);
    list.push_front(777);

    list_test(list);

    list.unique();

    list_test(list);
}

void    list_test_merge_sort_reverse() {
    std::cout << "----------MERGE SORT REVERSE----------" << std::endl;

    ft::List<int> list;
    list.push_front(111);
    list.push_front(111);
    list.push_front(0);
    list.push_front(0);
    list.push_front(0);
    list.push_front(777);
    list.push_front(777);

    ft::List<int> list2;
    list2.push_front(1);
    list2.push_front(2);
    list2.push_front(3);
    list2.push_front(4);
    list2.push_front(5);
    list2.push_front(6);
    list2.push_front(7);
    list2.push_front(8);
    list2.push_front(9);

    std::cout << "list" << std::endl;
    list_test(list);
    std::cout << "list2" << std::endl;
    list_test(list2);

    std::cout << "sort" << std::endl;
    list.sort();
    list2.sort();

    std::cout << "list" << std::endl;
    list_test(list);
    std::cout << "list2" << std::endl;
    list_test(list2);

    std::cout << "merge" << std::endl;
    list.merge(list2);

    std::cout << "list" << std::endl;
    list_test(list);
    std::cout << "list2" << std::endl;
    list_test(list2);

    std::cout << "reverse" << std::endl;
    list.reverse();

    std::cout << "list" << std::endl;
    list_test(list);
    std::cout << "list2" << std::endl;
    list_test(list2);
}

void    list_test_relational_operators() {
    std::cout << "----------RELATIONAL OPERTORS----------" << std::endl;

	ft::List<int> list;
    list.push_front(111);
    list.push_front(111);
    list.push_front(0);
    list.push_front(0);
    list.push_front(0);
    list.push_front(777);
    list.push_front(777);
	ft::List<int> list2(list);

    std::cout << "list" << std::endl;
    list_test(list);
    std::cout << "list2" << std::endl;
    list_test(list2);

	std::cout << (list == list2) << std::endl;
	std::cout << (list >= list2) << std::endl;
	std::cout << (list <= list2) << std::endl;

	list2.push_back(50);
	std::cout << (list != list2) << std::endl;
	std::cout << (list < list2) << std::endl;
	std::cout << (list <= list2) << std::endl;
	std::cout << (list2 > list) << std::endl;
	std::cout << (list2 >= list) << std::endl;

	list.push_back(200);
	std::cout << (list != list2) << std::endl;
	std::cout << (list > list2) << std::endl;
	std::cout << (list >= list2) << std::endl;
	std::cout << (list2 < list) << std::endl;
	std::cout << (list2 <= list) << std::endl;
}


void testList() {
	list_test_iterator();
    list_test_capacity();
    list_test_access();
    list_test_assign();
    list_test_push_pop();
    list_test_insert(); 
    list_test_erase();
    list_test_swap();
    list_test_resize();
    list_test_clear();
    list_test_splice();
    list_test_remove();
    list_test_remove_if();
    list_test_unique();
    list_test_merge_sort_reverse();
    list_test_relational_operators();
}