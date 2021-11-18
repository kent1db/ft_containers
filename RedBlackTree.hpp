#ifndef RBTREE_HPP
#define RBTREE_HPP
#include <iostream>
#include "LexicoComp.hpp"

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
			else {
				if (root->right)
					insertElem(elem, root->right);
				else {
					elem->parent = root;
					root->right = elem;
				}
			}
			return (elem);
		}

		void displayTree(node *root) {
			if (root == NULL)
				return ;
			displayTree(root->left);
			std::cout << "data is : " << root->data;
			if (root->parent)
				std::cout << " and parent is " << root->parent->data;
			else
				std::cout << " root node";
			if (root->left)
				std::cout << " and left is " << root->left->data;
			if (root->right)
				std::cout << " and right is " << root->right->data;
			std::cout << std::endl;
			displayTree(root->right);
		}

		void deleteTree(node *root){
			if (root == NULL)
				return;
			deleteTree(root->left);
			deleteTree(root->right);
			delete root;
		}

		void rotateLeft(node *elem) {
			node *parentElem = elem->parent;
			node *gparentElem = elem->parent->parent;
			if (elem == NULL)
				return ;
			if (elem->left) {
				elem->left->parent = parentElem;
				parentElem->right = elem->left;
				elem->left = NULL;
				elem->parent = NULL;
			}
			if (gparentElem == NULL)
				root = elem;
			else if (gparentElem->left == parentElem) {
				gparentElem->left = elem;
				elem->parent = gparentElem;
			}
			else {
				gparentElem->right = elem;
				elem->parent = gparentElem;
			}
			elem->left = parentElem;
			parentElem->parent = elem;
		}

		void rotateRight(node *elem) {
			node *parentElem = elem->parent;
			node *gparentElem = elem->parent->parent;
			if (elem == NULL)
				return ;
			if (elem->right) {
				elem->right->parent = parentElem;
				parentElem->left = elem->right;
				elem->right = NULL;
				elem->parent = NULL;
			}
			if (gparentElem == NULL)
				root = elem;
			else if (gparentElem->left == parentElem) {
				gparentElem->left = elem;
				elem->parent = gparentElem;
			}
			else {
				gparentElem->right = elem;
				elem->parent = gparentElem;
			}
			elem->right = parentElem;
			parentElem->parent = elem;
		}

	};
}

#endif