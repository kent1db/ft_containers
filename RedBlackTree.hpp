#ifndef RBTREE_HPP
#define RBTREE_HPP
#include <iostream>
#include "LexicoComp.hpp"

#define REDC		"\x1B[31m"
#define BLACKC		"\x1B[30m"
#define RESETC		"\x1B[0m"
enum e_color
{
	black, red
};

namespace ft {
	template<typename T, typename Alloc = std::allocator<T> >
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

			/// Constructor ///
			node(T data) {
				this->data = data;
				this->left = NULL;
				this->right = NULL;
				this->parent = NULL;
				this->color = red;
			}

			~node() {}
		};
		typedef typename Alloc::template rebind<node>::other node_alloc_type;
	private:
		node_alloc_type _alloc;
		node *root;
		node *elem;
	public:
		/// Constructor ///
		tree() : _alloc(std::allocator<node>()), root(NULL) {}

		explicit tree(T data) : _alloc(std::allocator<node>()),  root(_alloc.allocate(1)) {
			_alloc.construct(root, node(data));
			root->color = black;
		}

		tree(const tree& x) : root(NULL) {
			*this = x;
		}

		/// Destructor ///
		~tree() {
			deleteTree(root);
		}

		/// Geters ///
		node *getRoot() {
			return (root);
		}

		tree& operator=(const tree& x) {
			if (!x || x.root == NULL || this == &x)
				return (*this);
			deleteTree(root);
			copyElem(x.root);
			return (*this);
		}

		node *createElem(T data) {
			elem = _alloc.allocate(1);
			_alloc.construct(elem, node(data));
			return elem;
		}

		void copyElem(node *toCopy) {
			if (toCopy == NULL)
				return ;
			copyElem(toCopy->right);
			copyElem(toCopy->left);
			insertElem(createElem(toCopy->data), root);
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

		node *insertElem(node *elem, node *start) {
			if (elem == NULL) {
				return (NULL);
			}
			if (start == NULL) {
				root = elem;
				return (root);
			}
			if (elem->data < start->data) {
				if (start->left)
					insertElem(elem, start->left);
				else {
					elem->parent = start;
					start->left = elem;
					insertFix(elem);
				}
			} else if (elem->data == start->data)
				return (NULL);
			else {
				if (start->right)
					insertElem(elem, start->right);
				else {
					elem->parent = start;
					start->right = elem;
					insertFix(elem);
				}
			}
			return (elem);
		}

		void insertFix(node *elem) {
			if (elem == NULL || elem->parent == NULL)
				return;
			while (elem->parent->color == red) {
				if (elem->parent->parent && elem->parent == elem->parent->parent->left) {
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
						if (elem->parent->parent)
							elem->parent->parent->color = red;
						rotateRight(elem->parent);
					}
				} else {
					if (elem->parent->parent && elem->parent->parent->left && elem->parent->parent->left->color == red) {
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
						if (elem->parent->parent)
							elem->parent->parent->color = red;
						rotateLeft(elem->parent);
					}
				}
				if (elem == root)
					break;
			}
			root->color = black;
		}

		void transplant(node *u, node *v) {
			if (u->parent == nullptr)
				root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			if (v)
				v->parent = u->parent;
		}

		node *minimum(node *start) {
			if (start->left)
				return (minimum(start->left));
			return (start);
		}

		void deleteElem(T data) {
			node *x;
			node *y;
			node *toDel = root;
			node *parent = NULL;
			e_color saveColor;
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
			saveColor = toDel->color;
			if (toDel->left == NULL) {
				x = toDel->right;
				parent = toDel->parent;
				transplant(toDel, x);
			}
			else if (toDel->right == NULL) {
				x = toDel->left;
				parent = toDel->parent;
				transplant(toDel, x);
			}
			else {
				y = minimum(toDel->right);
				saveColor = y->color;
				x = y->right;
				if (y->parent == toDel) {
					if (x) {
						parent = y;
						x->parent = y;
					}
				}
				else {
					transplant(y, y->right);
					y->right = toDel->right;
					y->right->parent = y;
				}
				transplant(toDel, y);
				y->left = toDel->left;
				y->left->parent = y;
				y->color = toDel->color;
			}
			ft_delete(toDel);
			if (saveColor == black && parent) {
				deleteFix(x, parent);
			}
		}

		void deleteFix(node* x, node * parent) {
			node *s;
			while (parent && x != root && ( x == NULL || x->color == black)) {
				std::cout << "oui\n";
				if (x == parent->left) {
					s = parent->right;
					if (s && s->color == red) {
						s->color = black;
						parent->color = red;
						rotateLeft(parent);
						s = parent->right;
					}
					if (s && s->left && s->left->color == black && s->right && s->right->color == black) {
						s->color = red;
						x = parent;
					} else if (s && s->right){
						if (s && s->right && s->right->color == black) {
							s->left->color = black;
							s->color = red;
							rotateRight(s);
							s = parent->right;
						}
						s->color = parent->color;
						parent->color = black;
						s->right->color = black;
						rotateLeft(parent);
						x = root;
					}
				} else {
					std::cout << "oui\n";
					s = parent->left;
					if (s && s->color == red) {
						s->color = black;
						parent->color = red;
						rotateRight(parent);
						s = parent->left;
					}
					if (s && s->right && s->right->color == black && s->left && s->left->color == black) {
						s->color = red;
						x = parent;
					} else if (s && s->left){
						if (s->left->color == black) {
							s->right->color = black;
							s->color = red;
							rotateLeft(s);
							s = parent->left;
						}
						s->color = parent->color;
						parent->color = black;
						s->left->color = black;
						rotateRight(parent);
						x = root;
					}
				}
			}
			if (x)
				x->color = black;
		}

			void display(void) {
			displayTree(root, "", true);
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

			void ft_delete(node *toDel) {
			_alloc.destroy(toDel);
			_alloc.deallocate(toDel, 1);
		}

			void deleteTree(node *root) {
				if (root == NULL)
					return;
				deleteTree(root->left);
				deleteTree(root->right);
				ft_delete(root);
				root = NULL;
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