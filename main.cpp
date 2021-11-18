#include "Vector.hpp"
#include <iterator>
#include "Stack.hpp"
#include <vector>
#include "Map.hpp"
#include "RedBlackTree.hpp"

int 	main(void){

	ft::tree<int> it(40);
	ft::tree<int>::node *elem;
	it.insertElem(it.createElement(50), it.getRoot());
	elem = it.insertElem(it.createElement(20), it.getRoot());
	it.insertElem(it.createElement(30), it.getRoot());
	it.insertElem(it.createElement(10), it.getRoot());
//	it.insertElem(it.createElement(70), it.getRoot());
//	it.insertElem(it.createElement(30), it.getRoot());
//	it.insertElem(it.createElement(20), it.getRoot());
//	it.insertElem(it.createElement(10), it.getRoot());
//	it.insertElem(it.createElement(1), it.getRoot());
	it.displayTree(it.getRoot());
	std::cout << "\nrotate\n";
	it.rotateRight(elem);
	it.displayTree(it.getRoot());
	return (0);
}
