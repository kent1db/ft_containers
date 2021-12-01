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
	int tab[] = {1, 45, 73, 45, 279, 348, 751, 45, 45, 45};
	std::string value[10] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};
	std::map<int, std::string> map;
	while (i < 10) {
		std::pair<int, std::string> a(tab[i], value[i]);
		map.insert(a);
		i++;
	}
	map[10] = "coucou";
	std::cout << map[10] << std::endl;
//	for (std::map<int, char>::iterator it = map.begin();  it != map.end(); it++){
//		std::cout << it->first << std::endl;
//	}

	ft::map<int, std::string> map2;
	i = 0;
	while (i < 10) {
		ft::pair<int, std::string> a2(tab[i], value[i]);
		map2.insert(a2);
		i++;
//		std::cout << "map.first = "<< (test.first)->first << std::endl;
//		std::cout << "map.second = " << test.second << std::endl;
	}
	map2[10] = "coucou";
	std::cout << map2[10] << std::endl;
//	std::cout << map2.empty() << "	" << map2.size() << "	" << map2.max_size() << std::endl;

//	ft::tree<int, char> tree;
//	ft::pair<int, char> a(42, 0);
//	tree.insert(a);
	return (0);
}