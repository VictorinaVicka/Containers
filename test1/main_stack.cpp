#include <iostream>
#include <iomanip>
#include <stack>
#include "colors.h"
#include "main.hpp"
#include "Start.hpp"
#include "List.hpp"
#include "Stack.hpp"

void		testStack()
{
	std::cout << _WHITE << "# testStack" << _END << std::endl;
	std::cout << _YELLOW <<  "/* ********************************************************************** */" << std::endl;
	std::cout << "/*                          "<< _WHITE << "BASIC TESTS" << _YELLOW << "                                   */" << std::endl;
	std::cout << "/* ********************************************************************** */" << _END << std::endl;
	ft::Stack<int> mystack;

	std::cout << "ft::Stack<" << _PURPLE << "int" << _END << "> mystack" << std::endl;
	std::cout << std::endl;


	std::cout << _WHITE << "# empty" << _END << std::endl;
	std::cout << "mystack.empty(): " <<  mystack.empty() << std::endl;
	std::cout << "mystack.size(): " << mystack.size() << std::endl;
	std::cout << _WHITE << "# one element" << _END << std::endl;
	mystack.push(42);
	std::cout << "mystack.push(42)" << std::endl;
	std::cout << "mystack.empty(): " <<  mystack.empty() << std::endl;
	std::cout << "mystack.size(): " << mystack.size() << std::endl;
	std::cout << "mystack.top(): " << mystack.top() << std::endl;
	std::cout << _WHITE << "# two element" << _END << std::endl;
	mystack.push(2);
	std::cout << "mystack.push(2)" << std::endl;
	std::cout << "mystack.size(): " << mystack.size() << std::endl;
	std::cout << "mystack.top(): " << mystack.top() << std::endl;
	std::cout << _WHITE << "# pop element" << _END << std::endl;
	mystack.pop();
	std::cout << "mystack.pop()" << std::endl;
	std::cout << "mystack.size(): " << mystack.size() << std::endl;
	std::cout << "mystack.top(): " << mystack.top() << std::endl;
	std::cout << std::endl;

	ft::Stack<int, ft::List<int> > mystack2;

	std::cout << "ft::Stack<" << _PURPLE << "int" << _END << ", " << _PURPLE << "ft::List" << _END << "> mystack2" << std::endl;
	std::cout << std::endl;


	std::cout << _WHITE << "# empty" << _END << std::endl;
	std::cout << "mystack2.empty(): " <<  mystack2.empty() << std::endl;
	std::cout << "mystack2.size(): " << mystack2.size() << std::endl;
	std::cout << _WHITE << "# one element" << _END << std::endl;
	mystack2.push(42);
	std::cout << "mystack2.push(42)" << std::endl;
	std::cout << "mystack2.empty(): " <<  mystack2.empty() << std::endl;
	std::cout << "mystack2.size(): " << mystack2.size() << std::endl;
	std::cout << "mystack2.top(): " << mystack2.top() << std::endl;
	std::cout << _WHITE << "# two element" << _END << std::endl;
	mystack2.push(2);
	std::cout << "mystack2.push(2)" << std::endl;
	std::cout << "mystack2.size(): " << mystack2.size() << std::endl;
	std::cout << "mystack2.top(): " << mystack2.top() << std::endl;
	std::cout << _WHITE << "# pop element" << _END << std::endl;
	mystack2.pop();
	std::cout << "mystack2.pop()" << std::endl;
	std::cout << "mystack2.size(): " << mystack2.size() << std::endl;
	std::cout << "mystack2.top(): " << mystack2.top() << std::endl;
	std::cout << std::endl;

	std::cout << _WHITE << "# test cpy and equality" << _END << std::endl;
	ft::Stack<int>	cpystack = mystack;
	std::cout << "ft::Stack<" << _PURPLE << "int" << _END << "> cpystack = mystack" << std::endl;
	std::cout << std::endl;

	std::cout << "cpystack == mystack:" << (cpystack == mystack) << std::endl;
	cpystack.push(7);
	std::cout << "cpystack.push(7)" << std::endl;
	std::cout << "cpystack == mystack:" << (cpystack == mystack) << std::endl;
}
