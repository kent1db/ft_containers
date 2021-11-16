#include "Vector.hpp"
#include <vector>
#include <iterator>


int 	main(void){

	std::cout << "My Vector\n";
	/*** My Vector ***/

	ft::vector<int> a;
	a.push_back(100);
	a.push_back(200);
	a.push_back(200);
	a.push_back(600);
	a.push_back(700);
	a.push_back(800);
	a.push_back(1000);
	a.push_back(2000);
	int c[7] = {0, 1 , 2 , 3 , 4 , 5 ,6};
	ft::vector<int> ye(c, c + 5);
	ft::vector<int>::iterator it = a.begin();
	std::cout << *it++ << std::endl;
	std::cout << *it << std::endl;
	*it = 800;
	std::cout<< *(5 + it) << std::endl;
	std::cout << *it << std::endl;


//	5 + it ;

//	std::cout << *it << std::endl;

//	for (unsigned long n = 0; n < a.size(); n++) {
//		std::cout << it[n] << std::endl;
//	}



	std::cout << "Reference Vector\n";
	/*** Reference Vector ***/

	return (0);
}
