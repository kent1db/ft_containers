#include "Vector.hpp"
#include <iterator>
#include "Stack.hpp"
#include <vector>
#include "Map.hpp"

int 	main(void){


	ft::vector<int> vec(3, 100);
	ft::stack<int> first;
	ft::stack<int> second(vec);

	std::cout << "size of : " << first.size() << "\n";


	return (0);
}
