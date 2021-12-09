#ifndef SET_HPP
#define SET_HPP
#include <iostream>
#include "Iterator.hpp"
#include "RedBlackTree.hpp"
#include "LexicoComp.hpp"
#include "Enable.hpp"
#include "Pair.hpp"

namespace ft {
	template <
			typename T,
			typename Compare = std::less<T>,
			typename Alloc = std::allocator<T> >
	class set
	{
		class bidirectional_iterator : public iterators_traits<iterator<bidirectional_iterator_tag, T > >
		{
		private:
			void modifyValueType() {
				if (_node)
					_p = &_node->data.second;
				else
					_p = NULL;
			}
		protected:
			node<pair<T, T> > * _node;
			typename bidirectional_iterator::pointer _p;
		public:
			/* Constructor */
			bidirectional_iterator(node<pair<T, T> > *nodeCopy) : _node(nodeCopy) {
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
					node<pair<T, T> > *parent = _node->parent;
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
					node<pair<T, T> > *parent = _node->parent;
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
		typedef T											key_type;
		typedef T											value_type;
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
		tree<T, T, ft::pair<T, T>, allocator_type, key_compare> 	RBtree;
		size_type 			_size;
		allocator_type 		_alloc;
		key_compare 		_comp;

	public:
		/// Constructor ///
		explicit set (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type()) : RBtree(), _size(0), _alloc(alloc), _comp(comp) {}

		template <class InputIterator>
		set (InputIterator first, typename enable_if<(ft::is_same<InputIterator, typename bidirectional_iterator::pointer>::value || is_same<InputIterator, bidirectional_iterator>::value) && !ft::is_integral<InputIterator>::value, InputIterator>::type last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type()) : RBtree(), _size(0), _alloc(alloc), _comp(comp) {
			while (first != last) {
				RBtree.insert(ft::make_pair(*first, 0));
				first++;
				_size++;
			}
		}

		set (const set& x) : RBtree(x.RBtree), _size(x._size), _alloc(x._alloc), _comp(x._comp) {}

		/// Destructor ///

		~set() {
			clear();
		}

		/// Operator ///

		set & operator=(const set& x) {
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
			node<pair<T, T> > *node = RBtree.createElem(ft::pair<T, T>(0, 0));
			node->parent = RBtree.maximum();
			iterator it(node);
			return (reverse_iterator(it));
		}

		const_reverse_iterator rbegin() const {
			node<pair<T, T> > *node = RBtree.createElem(ft::pair<T, T>(0, 0));
			node->parent = RBtree.maximum();
			iterator it(node);
			return (reverse_iterator(it));
		}

		reverse_iterator rend() {
			return (reverse_iterator(begin()));
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
			return (std::numeric_limits<size_t>::max() / sizeof(node<pair<T, T> >));
		}

		/// Modifier ///
		pair<iterator,bool> insert(const value_type& val) {
			bool notExist = RBtree.notExist(ft::make_pair(val, val), RBtree.getRoot());
			if (notExist)
				_size++;
			return (ft::make_pair(RBtree.insert(ft::make_pair(val, val)), notExist));
		}

		iterator insert(iterator position, const value_type& val) {
			(void)position;
			if (RBtree.notExist(ft::make_pair(val, val), RBtree.getRoot()))
				_size++;
			return(RBtree.insert(ft::make_pair(val, val)));
		}

		template <class InputIterator>
		void insert(InputIterator first, typename enable_if<(ft::is_same<InputIterator, typename bidirectional_iterator::pointer>::value || is_same<InputIterator, bidirectional_iterator>::value) && !ft::is_integral<InputIterator>::value, InputIterator>::type last) {
			for (InputIterator i = first; i < last; i++) {
				if (RBtree.notExist(*i, RBtree.getRoot()))
					_size++;
				RBtree.insert(*i);
			}
		}

		void erase(iterator position) {
			if (position != NULL && RBtree.findKey(ft::make_pair(*position, 0), RBtree.getRoot())) {
				RBtree.deleteElem(ft::make_pair(*position, 0));
				_size--;
			}
		}

		size_type erase(const value_type& k) {
			node<pair<T, T> > *elem = NULL;
			if ((elem = RBtree.find(k, RBtree.getRoot()))) {
				RBtree.deleteElem(elem->data);
				_size--;
			}
			return (1);
		}

		void erase(iterator first, iterator last) {
			while (first != last) {
				iterator tmp = first;
				++tmp;
				if (RBtree.findKey(*first, RBtree.getRoot())) {
					RBtree.deleteElem(*first);
					_size--;
				}
				first = tmp;
			}
		}

		void swap(set& x) {
            RBtree.swap(x.RBtree);
            size_type 			tmp_size = x._size;
            allocator_type 		tmp_alloc = x._alloc;
            key_compare 		tmp_comp = x._comp;
            x._size = _size;
            x._alloc = _alloc;
            x._comp = _comp;
            _size = tmp_size;
            _alloc = tmp_alloc;
            _comp = tmp_comp;
		}

		void clear() {
			_size = 0;
			RBtree.deleteTree(RBtree.getRoot());
		}

		/// Observers ///

		key_compare key_comp() const {
			return (_comp);
		}

		class value_compare {
			friend class set;

		protected:
			Compare comp;

			value_compare(Compare c) : comp(c) {}
		public:
			bool operator()(const value_type &x, const value_type &y) const {
				return comp(x, y);
			}
		};

		value_compare value_comp() const {
			return (value_compare(_comp));
		}

		/// Operations ///

		iterator find(const value_type& k) {
			return (RBtree.find(k, RBtree.getRoot()));
		}

		const_iterator find(const value_type& k) const {
			return (RBtree.find(k, RBtree.getRoot()));
		}

		size_type count(const value_type& k) const {
			return ((find(k) == NULL) ? 0 : 1);
		}

		iterator lower_bound(const value_type& k) {
			iterator it = begin();
			while (it != end() && _comp(*it, k))
				it++;
			return (it);
		}

		const_iterator lower_bound(const value_type& k) const {
			const_iterator it = begin();
			while (it != end() && _comp(*it, k))
				it++;
			return (it);
		}

		iterator upper_bound(const value_type& k) {
			iterator it = begin();
			while (it != end() && (_comp(*it, k) || *it == k))
				it++;
			return (it);
		}

		const_iterator upper_bound (const value_type& k) const {
			const_iterator it = begin();
			while (it != end() && (_comp(*it, k) || *it == k))
				it++;
			return (it);
		}

		pair<const_iterator,const_iterator>	equal_range(const value_type& k) const {
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

		pair<iterator,iterator>	equal_range(const value_type& k) {
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}


		void display(){
			RBtree.display();
		}

		/// Allocator ///
		allocator_type get_allocator() const {
			return (_alloc);
		}
	};
}

#endif