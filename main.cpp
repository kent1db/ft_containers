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
	int i= 0;
	int tab[] = {1, 45, 73, 49, 279, 348, 751, 66, 423, 44};
	std::map<int, char> map;
	while (i < 10) {
		std::pair<int, char> a(tab[i++], 0);
		map.insert(a);
	}
	for (std::map<int, char>::iterator it = map.begin();  it != map.end(); it++){
		std::cout << it->first << std::endl;
	}

	ft::map<int, char> map2;
	i = 0;
	while (i < 1) {
		ft::pair<int, char> a2(tab[i++], 0);
		map2.insert(a2);
	}

//	ft::tree<int, char> tree;
//	ft::pair<int, char> a(42, 0);
//	tree.insert(a);
	return (0);
}