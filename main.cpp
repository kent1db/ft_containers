#include "Vector.hpp"
#include <vector>
#include <iterator>


int 	main(void){

	std::cout << "My Vector\n";
	/*** My Vector ***/

	ft::vector<int> myvector;
	myvector.push_back(100);
	myvector.push_back(200);
	myvector.push_back(300);

	myvector.clear();
	myvector.push_back(1101);
	myvector.push_back(2202);


	std::cout << "Reference Vector\n";
	/*** Reference Vector ***/


	return (0);
}
