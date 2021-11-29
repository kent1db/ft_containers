#include "Vector.hpp"
#include <iterator>
#include "Stack.hpp"
#include <vector>
#include "Map.hpp"
#include <list>
#include <algorithm>
#include "RedBlackTree.hpp"

int 	main(void){
	int tab[] = {542, 247, 417, 453, 789, 554, 113, 486, 783, 138, 568, 723, 498, 334};
	ft::tree<int> tree;
	std::vector<int> vec(tab, tab + 14);
	std::random_shuffle(vec.begin(), vec.end());
	for (int i = 0; i < 14; i++)
		tree.insertElem(tree.createElem(tab[i]), tree.getRoot());
	int a = 0;
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
		tree.display();
		std::cout << "__________________"<< *it << "____________________\n";
		tree.deleteElem(*it);
		if (a == 7)
			break;
		a++;
		std::cout << a << std::endl;
	}
	return (0);
}
