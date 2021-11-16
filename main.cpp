#include "Vector.hpp"
#include <vector>
#include <iterator>


int 	main(void){

	std::cout << "My Vector\n";
	/*** My Vector ***/

	ft::vector<int> a;
	ft::vector<int>::iterator it = a.begin();
	it = a.insert(it, 4);
	it = a.insert(it, 4);


	std::cout << "Reference Vector\n";
	/*** Reference Vector ***/

	std::cout << "oui\n";

	return (0);
}
