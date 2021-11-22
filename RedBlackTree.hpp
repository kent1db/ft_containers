#ifndef RBTREE_HPP
#define RBTREE_HPP
#include <iostream>
#include "LexicoComp.hpp"
#define REDC		"\x1B[31m"
#define BLACKC	"\x1B[30m"
#define RESETC	"\x1B[0m"

enum e_color {black, red};

namespace ft {
	template <typename T>
	class tree {
	public:
		struct node {
			T data;
			node *left;
			node *right;
			node *parent;
			e_color color;
			bool	empty;
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
		node *getParent(node *elem){
			return (elem->parent);
		}
		node *getLeft(node *elem){
			return (elem->left);
		}
		node *getRight(node *elem){
			return (elem->right);
		}

		node *insertElem(node *elem, node *root) {
			if (elem == NULL) {
				return (NULL);
			}
			if (elem->data < root->data) {
				if (root->left)
					insertElem(elem, root->left);
				else {
					elem->parent = root;
					root->left = elem;
				}
			}
			else if (elem->data == root->data)
				return (NULL);
			else {
				if (root->right)
					insertElem(elem, root->right);
				else {
					elem->parent = root;
					root->right = elem;
				}
			}
			insertFix(elem);
			return (elem);
		}

		void insertFix(node *k) {
			node *u;
			while (k->parent->color == red) {
				if (k->parent == k->parent->parent->right) {
					u = k->parent->parent->left;
					if (u->color == red) {
						u->color = black;
						k->parent->color = black;
						k->parent->parent->color = red;
						k = k->parent->parent;
					} else {
						if (k == k->parent->left) {
							k = k->parent;
							rotateRight(k);
						}
						k->parent->color = black;
						k->parent->parent->color = red;
						rotateLeft(k->parent->parent);
					}
				} else {
					u = k->parent->parent->right;

					if (u->color == red) {
						u->color = black;
						k->parent->color = black;
						k->parent->parent->color = red;
						k = k->parent->parent;
					} else {
						if (k == k->parent->right) {
							k = k->parent;
							rotateLeft(k);
						}
						k->parent->color = black;
						k->parent->parent->color = red;
						rotateRight(k->parent->parent);
					}
				}
				if (k == root) {
					break;
				}
			}
			root->color = black;
//			if (elem == NULL || elem->parent == NULL)
//				return ;
//			node *p = elem->parent;
//			node *gp = p->parent;
//			while (p->color == red) {
//				if (p == gp->left) {
//					if (gp->right->color == red) {
//						gp->right->color = black;
//						p->color = black;
//						gp->color = red;
//						elem = gp;
//					} else {
//						if (elem == p->right) {
//							node *tmp = elem;
//							elem = p;
//							rotateLeft(tmp);
//						}
//						p->color = black;
//						gp->color = red;
//						rotateRight(p);
//					}
//				} else {
//					if (gp->left->color == red) {
//						gp->left->color = black;
//						p->color = black;
//						gp->color = red;
//						elem = gp;
//					} else {
//						if (elem == p->left) {
//							node *tmp = elem;
//							elem = p;
//							rotateRight(tmp);
//						}
//						p->color = black;
//						gp->color = red;
//						rotateLeft(p);
//					}
//				}
//				if (elem == root)
//					break;
//			}
//			root->color = black;

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

		void deleteTree(node *root){
			if (root == NULL)
				return;
			deleteTree(root->left);
			deleteTree(root->right);
			delete root;
		}

		void rotateLeft(node *x) {
			node * y = x->right;
			x->right = y->left;
			if (y->left != NULL) {
				y->left->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == nullptr) {
				this->root = y;
			} else if (x == x->parent->left) {
				x->parent->left = y;
			} else {
				x->parent->right = y;
			}
			y->left = x;
			x->parent = y;
//			if (elem == NULL || elem->parent == NULL || elem->parent->left == elem)
//				return ;
//			node *parentElem = elem->parent;
//			node *gparentElem = elem->parent->parent;
//			parentElem->right = elem->left;
//			if (elem->left) {
//				elem->left->parent = parentElem;
//				elem->left = NULL;
//			}
//			elem->parent = gparentElem;
//			if (gparentElem == NULL)
//				root = elem;
//			else if (gparentElem->left == parentElem)
//				gparentElem->left = elem;
//			else
//				gparentElem->right = elem;
//			elem->left = parentElem;
//			parentElem->parent = elem;
		}

		void rotateRight(node *x) {
			node * y = x->left;
			x->left = y->right;
			if (y->right != NULL) {
				y->right->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == nullptr) {
				this->root = y;
			} else if (x == x->parent->right) {
				x->parent->right = y;
			} else {
				x->parent->left = y;
			}
			y->right = x;
			x->parent = y;
//			if (elem == NULL || elem->parent == NULL || elem->parent->right == elem)
//				return ;
//			node *parentElem = elem->parent;
//			node *gparentElem = elem->parent->parent;
//			parentElem->left = elem->right;
//			if (elem->right) {
//				elem->right->parent = parentElem;
//				elem->right = NULL;
//			}
//			elem->parent = gparentElem;
//			if (gparentElem == NULL)
//				root = elem;
//			else if (gparentElem->left == parentElem)
//				gparentElem->left = elem;
//			else
//				gparentElem->right = elem;
//			elem->right = parentElem;
//			parentElem->parent = elem;
		}

	};
}

#endif