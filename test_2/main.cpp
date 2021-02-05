
#include "Test.hpp"

int main()
{
	std::cout << ":: Vector ::" << std::endl;
	test_vector();
	std::cout << ":: List ::" << std::endl;
	test_list();
	std::cout << ":: Stack ::" << std::endl;
	test_stack();
	std::cout << ":: Queue ::" << std::endl;
	test_queue();
	std::cout << ":: Map ::" << std::endl;
	test_map();
	std::cout << ":: Everything is ok! ::" << std::endl;
	return 0;
}
