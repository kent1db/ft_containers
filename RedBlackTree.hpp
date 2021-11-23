#ifndef RBTREE_HPP
#define RBTREE_HPP
#include <iostream>
#include "LexicoComp.hpp"

#define REDC        "\x1B[31m"
#define BLACKC    "\x1B[30m"
#define RESETC    "\x1B[0m"
enum e_color
{
	black, red
};
namespace ft {
	template<typename T>
	class tree
	{
	public:
		struct node
		{
			T data;
			node *left;
			node *right;
			node *parent;
			e_color color;
			bool empty;
		};
	private:
		node *root;
		node *elem;
	public:
		node *createElement() {
			elem = new node;
			elem->data = 0;
			elem->empty = true;
			elem->left = NULL;
			elem->right = NULL;
			elem->parent = NULL;
			elem->color = red;
			return (elem);
		}

		node *createElement(T data) {
			elem = new node;
			elem->data = data;
			elem->empty = false;
			elem->left = NULL;
			elem->right = NULL;
			elem->parent = NULL;
			elem->color = red;
			return (elem);
		}

		/// Constructor ///
		tree() : root(createElement()) { root->color = black; }

		tree(T data) : root(createElement(data)) { root->color = black; }

		/// Destructor ///
		~tree() {
			deleteTree(root);
		}

		/// Geters ///
		node *getRoot() {
			return (root);
		}

		node *getParent(node *elem) {
			return (elem->parent);
		}

		node *getLeft(node *elem) {
			return (elem->left);
		}

		node *getRight(node *elem) {
			return (elem->right);
		}

		node *insertElem(node *elem, node *root, bool on) {
			if (elem == NULL) {
				return (NULL);
			}
			if (elem->data < root->data) {
				if (root->left)
					insertElem(elem, root->left, on);
				else {
					elem->parent = root;
					root->left = elem;
					if (on)
						insertFix(elem);
				}
			} else if (elem->data == root->data)
				return (NULL);
			else {
				if (root->right)
					insertElem(elem, root->right, on);
				else {
					elem->parent = root;
					root->right = elem;
					if (on)
						insertFix(elem);
				}
			}
			return (elem);
		}

		void insertFix(node *elem) {
			if (elem == NULL || elem->parent == NULL)
				return;
			while (elem->parent->color == red) {
				if (elem->parent == elem->parent->parent->left) {
					if (elem->parent->parent->right && elem->parent->parent->right->color == red) {
						elem->parent->parent->right->color = black;
						elem->parent->color = black;
						elem->parent->parent->color = red;
						elem = elem->parent->parent;
					} else {
						if (elem == elem->parent->right) {
							node *tmp = elem->parent;
							rotateLeft(elem);
							elem = tmp;
						}
						elem->parent->color = black;
						elem->parent->parent->color = red;
						rotateRight(elem->parent);
					}
				} else {
					if (elem->parent->parent->left && elem->parent->parent->left->color == red) {
						elem->parent->parent->left->color = black;
						elem->parent->color = black;
						elem->parent->parent->color = red;
						elem = elem->parent->parent;
					} else {
						if (elem == elem->parent->left) {
							node *tmp = elem->parent;
							rotateRight(elem);
							elem = tmp;
						}
						elem->parent->color = black;
						elem->parent->parent->color = red;
						rotateLeft(elem->parent);
					}
				}
				if (elem == root)
					break;
			}
			root->color = black;
		}

		void deleteElem(T data) {
			node *x;
			node *y;
			node *toDel = root;
			while (toDel != NULL) {
				if (toDel->data == data)
					break;
				if (toDel->data > data)
					toDel = toDel->left;
				else
					toDel = toDel->right;
			}
			if (toDel == NULL)
				return;
			e_color saveColor = toDel->color;
			if (toDel->left == NULL)
				x = toDel->right;
		}

		void displayTree(node *root, std::string indent, bool last) {
			if (root != NULL) {
				std::cout << indent;
				if (last) {
					std::cout << "R----";
					indent += "   ";
				} else {
					std::cout << "L----";
					indent += "|  ";
				}
				std::string sColor = root->color ? REDC : BLACKC;
				std::cout << sColor << root->data << RESETC << std::endl;
				displayTree(root->left, indent, false);
				displayTree(root->right, indent, true);
			}
		}

		void deleteTree(node *root) {
			if (root == NULL)
				return;
			deleteTree(root->left);
			deleteTree(root->right);
			delete root;
		}

		void rotateLeft(node *elem) {
			if (elem == NULL || elem->parent == NULL || elem->parent->left == elem)
				return;
			node *parentElem = elem->parent;
			node *gparentElem = elem->parent->parent;
			parentElem->right = elem->left;
			if (elem->left) {
				elem->left->parent = parentElem;
				elem->left = NULL;
			}
			elem->parent = gparentElem;
			if (gparentElem == NULL)
				root = elem;
			else if (gparentElem->left == parentElem)
				gparentElem->left = elem;
			else
				gparentElem->right = elem;
			elem->left = parentElem;
			parentElem->parent = elem;
		}

		void rotateRight(node *elem) {
			if (elem == NULL || elem->parent == NULL || elem->parent->right == elem)
				return;
			node *parentElem = elem->parent;
			node *gparentElem = elem->parent->parent;
			parentElem->left = elem->right;
			if (elem->right) {
				elem->right->parent = parentElem;
				elem->right = NULL;
			}
			elem->parent = gparentElem;
			if (gparentElem == NULL)
				root = elem;
			else if (gparentElem->left == parentElem)
				gparentElem->left = elem;
			else
				gparentElem->right = elem;
			elem->right = parentElem;
			parentElem->parent = elem;
		}
	};
}
#endif