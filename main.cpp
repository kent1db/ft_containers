#include "Vector.hpp"
#include <iterator>
#include "Stack.hpp"
#include <vector>
#include <map>
#include "Pair.hpp"
#include "Map.hpp"
#include <list>
#include <algorithm>
#include "RedBlackTree.hpp"

int 	main(void){
	int tab[] = {1, 45, 73, 49, 279, 348, 751, 66, 423, 44};
	int i = 0;
	std::map<int, char> map;
	while (i < 10) {
		std::pair<int, char> a(tab[i], 0);
		map.insert(a);
		i++;
	}
	for (std::map<int, char>::iterator it = map.begin(); it != map.end(); it++) {
		std::cout << it->first << std::endl;
	}
	return (0);
}

