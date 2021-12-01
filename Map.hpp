#ifndef MAP_HPP
#define MAP_HPP
#include <iostream>
#include "Iterator.hpp"
#include "RedBlackTree.hpp"
#include "LexicoComp.hpp"
#include "Pair.hpp"

namespace ft {
	template <	typename Key,
	        	typename T,
	        	typename Compare = std::less<Key>,
	        	typename Alloc = std::allocator<pair<const Key, T > > >
	class map
	{
	class bidirectional_iterator : public iterators_traits<iterator<bidirectional_iterator_tag, pair<const Key, T> > >
		{
		private:
			void modifyValueType() {
				if (_node)
					_p = &_node->data;
				else
					_p = NULL;
			}
		protected:
			node<pair<const Key, T> > * _node;
			typename bidirectional_iterator::pointer _p;
		public:
			/* Constructor */
			bidirectional_iterator(node<pair<const Key, T> > *nodeCopy) : _node(nodeCopy) {
				modifyValueType();
			}

			// Default constructor
			bidirectional_iterator() : _node(NULL), _p(0) {}

			// Copy constructor
			bidirectional_iterator(const bidirectional_iterator &x) {
				if (*this != x)
					*this = x;
			}

			// Destructor
			~bidirectional_iterator() {}

			// Operator
			bidirectional_iterator &operator=(const bidirectional_iterator &rhs) {
				_p = rhs._p;
				_node = rhs._node;
				return (*this);
			}

			bool operator==(const bidirectional_iterator &rhs) const {
				return (_p == rhs._p);
			}

			bool operator!=(const bidirectional_iterator &rhs) const {
				return (_p != rhs._p);
			}

			typename bidirectional_iterator::reference operator*() const {
				return (*_p);
			}

			typename bidirectional_iterator::pointer operator->() const {
				return (_p);
			}

			bidirectional_iterator &operator++() {
				if (_node == NULL)
					return (*this);
				if (_node->right == NULL) {
					node<pair<const Key, T> > parent = _node->parent;
					while (parent && _node == parent->right) {
						_node = parent;
						parent = parent->parent;
					}
					_node = parent;
					modifyValueType();
					return (*this);
				} else {
					_node = _node->right;
					while (_node && _node->left != NULL)
						_node = _node->left;
					modifyValueType();
				}
				return (*this);
			}

			bidirectional_iterator operator++(int) {
				bidirectional_iterator tmp(*this);
				operator++();
				return (tmp);
			}

			bidirectional_iterator &operator--() {
				if (_node == NULL)
					return (*this);
				if (_node->left == NULL) {
					node<pair<const Key, T> > parent = _node->parent;
					while (parent && _node == parent->left) {
						_node = parent;
						parent = parent->parent;
					}
					_node = parent;
					modifyValueType();
					return (*this);
				} else {
					_node = _node->left;
					while (_node && _node->right != NULL)
						_node = _node->right;
					modifyValueType();
				}
				return (*this);
			}

			bidirectional_iterator operator--(int) {
				bidirectional_iterator tmp(*this);
				operator--();
				return (tmp);
			}
		};
	public:
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef pair<const Key, T>							value_type;
		typedef Compare										key_compare;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef bidirectional_iterator						iterator;
		typedef bidirectional_iterator						const_iterator;
		typedef size_t										size_type;
		typedef typename iterator::difference_type 			difference_type;
		typedef reverse_iterator<iterator>					const_reverse_iterator;
		typedef reverse_iterator<iterator>					reverse_iterator;
	protected:
		tree<Key, T, value_type, allocator_type, key_compare> 	RBtree;
		size_type 			_size;
		allocator_type 		_alloc;
		key_compare 		_comp;

	public:
		/// Constructor ///
		explicit map (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type()) : RBtree(), _size(0), _alloc(alloc), _comp(comp) {}

		template <class InputIterator>
		map (InputIterator first, typename enable_if<(ft::is_same<InputIterator, typename bidirectional_iterator::pointer>::value || is_same<InputIterator, bidirectional_iterator>::value) && !ft::is_integral<InputIterator>::value, InputIterator>::type last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type()) : RBtree(), _size(0), _alloc(alloc), _comp(comp) {
			while (first != last) {
		 		RBtree.insert(*first);
		 		first++;
				_size++;
			}
		}

		map (const map& x) : RBtree(x.RBtree), _size(x._size), _alloc(x._alloc), _comp(x._comp) {}

		/// Destructor ///

		~map() {
			_size = 0;
		}

		/// Operator ///

		map & operator=(const map& x) {
			RBtree = x.RBtree;
			_size = x._size;
		}

		/// Iterator ///
		iterator begin() {
			return (RBtree.minimum());
		}

		const_iterator begin() const {
			return (RBtree.minimum());
		}

		iterator end() {
			return (NULL);
		}

		const_iterator end() const {
			return (NULL);
		}

		reverse_iterator rbegin() {
			node<pair<const Key, T> > *node = RBtree.createElem(ft::pair<const Key, T>(0, 0));
			node->parent = RBtree.maximum();
			iterator it(node);
			return (reverse_iterator(it));
		}

		const_reverse_iterator rbegin() const {
			node<pair<const Key, T> > *node = RBtree.createElem(ft::pair<const Key, T>(0, 0));
			node->parent = RBtree.maximum();
			iterator it(node);
			return (reverse_iterator(it));
		}

		reverse_iterator rend() {
			return (reverse_iterator(begin()));
			// TODO create new elem null right before minimum aka first elem
		}

		const_reverse_iterator rend() const {
			return (reverse_iterator(begin()));
		}

		/// Capacity ///
		bool empty() const {
			return (_size == 0);
		}

		size_type size() const {
			return (_size);
		}

		size_type max_size() const {
			int ln = (sizeof(node<pair<const Key, T> >) > 1 ? log(sizeof(node<pair<const Key, T> >) ) / log(2) : 1);
			return (pow(2, 64 - ln) - (long double) 1);
		}

		/// Element acces ///
		mapped_type& operator[](const key_type& k) {
			if (RBtree.find(k, RBtree.getRoot()))
				return ((RBtree.find(k, RBtree.getRoot()))->data.second);
			pair<key_type , mapped_type> p;
			p.first = k;
			_size++;
			return (RBtree.insert(p)->data.second);
		}

		/// Modifier ///
		pair<iterator,bool> insert(const value_type& val) {
			bool notExist = RBtree.notExist(val, RBtree.getRoot());
			if (notExist)
				_size++;
			return (ft::make_pair(RBtree.insert(val), notExist));
		}

		iterator insert(iterator position, const value_type& val) {
			(void)position;
			if (RBtree.notExist(val, RBtree.getRoot()))
				_size++;
			return(RBtree.insert(val));
		}

		template <class InputIterator>
		void insert(InputIterator first, typename enable_if<(ft::is_same<InputIterator, typename bidirectional_iterator::pointer>::value || is_same<InputIterator, bidirectional_iterator>::value) && !ft::is_integral<InputIterator>::value, InputIterator>::type last) {
			for (InputIterator i = first; i < last; i++) {
				if (RBtree.notExist(*i, RBtree.getRoot()))
					_size++;
				RBtree.insert(*i);
			}
		}

	};
}

#endif