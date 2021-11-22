#include "Vector.hpp"
#include <iterator>
#include "Stack.hpp"
#include <vector>
#include "Map.hpp"
#include "RedBlackTree.hpp"

int 	main(void){

	ft::tree<int> it(33);
	it.insertElem(it.createElement(13), it.getRoot());
	it.insertElem(it.createElement(53), it.getRoot());
	it.insertElem(it.createElement(11), it.getRoot());
	it.insertElem(it.createElement(21), it.getRoot());
	it.insertElem(it.createElement(41), it.getRoot());
	it.insertElem(it.createElement(61), it.getRoot());
	it.insertElem(it.createElement(15), it.getRoot());
	it.insertElem(it.createElement(31), it.getRoot());
	it.insertElem(it.createElement(20), it.getRoot());
	it.insertElem(it.createElement(42), it.getRoot());
//	it.insertElem(it.createElement(43), it.getRoot());
//	it.insertElem(it.createElement(56), it.getRoot());
//	it.insertElem(it.createElement(36), it.getRoot());
//	it.insertElem(it.createElement(27), it.getRoot());
//	it.insertElem(it.createElement(52), it.getRoot());
//	it.insertElem(it.createElement(45), it.getRoot());
	it.displayTree(it.getRoot(), "", true);
	return (0);
}
