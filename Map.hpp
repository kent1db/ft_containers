#ifndef MAP_HPP
#define MAP_HPP
#include <iostream>
#include "Iterator.hpp"
#include "RedBlackTree.hpp"
#include "LexicoComp.hpp"
#include "Enable.hpp"
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
					node<pair<const Key, T> > *parent = _node->parent;
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
					node<pair<const Key, T> > *parent = _node->parent;
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
			clear();
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
			node<pair<const Key, T> > *node = RBtree.createEnd(ft::pair<const Key, T>(0, 0));
			node->parent = RBtree.maximum();
			iterator it(node);
			return (reverse_iterator(it));
		}

		const_reverse_iterator rbegin() const {
			node<pair<const Key, T> > *node = RBtree.createEnd(ft::pair<const Key, T>(0, 0));
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
			return (std::numeric_limits<size_t>::max() / sizeof(node<pair<const Key, T> >));
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

		void erase(iterator position) {
			if (position != NULL && RBtree.findKey(*position, RBtree.getRoot())) {
				RBtree.deleteElem(*position);
				_size--;
			}
		}

		size_type erase(const key_type& k) {
			node<value_type> *elem = NULL;
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

		void swap(map& x) {
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
			typedef pair<const Key, T>							value_type;
		protected:
			Compare comp;
		public:
			value_compare(Compare c) : comp(c) {}
			bool operator()(const value_type &x, const value_type &y) const {
				return comp(x.first, y.first);
			}
		};

		value_compare value_comp() const {
			return (value_compare(_comp));
		}

		/// Operations ///

		iterator find(const key_type& k) {
			return (RBtree.find(k, RBtree.getRoot()));
		}

		const_iterator find(const key_type& k) const {
			return (RBtree.find(k, RBtree.getRoot()));
		}

		size_type count(const key_type& k) const {
			return ((find(k) == NULL) ? 0 : 1);
		}

		iterator lower_bound(const key_type& k) {
			iterator it = begin();
			while (it != end() && _comp(it->first, k))
				it++;
			return (it);
		}

		const_iterator lower_bound(const key_type& k) const {
			const_iterator it = begin();
			while (it != end() && _comp(it->first, k))
				it++;
			return (it);
		}

		iterator upper_bound(const key_type& k) {
			iterator it = begin();
			while (it != end() && (_comp(it->first, k) || it->first == k))
				it++;
			return (it);
		}

		const_iterator upper_bound (const key_type& k) const {
			const_iterator it = begin();
			while (it != end() && (_comp(it->first, k) || it->first == k))
				it++;
			return (it);
		}

		pair<const_iterator,const_iterator>	equal_range(const key_type& k) const {
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

		pair<iterator,iterator>	equal_range(const key_type& k) {
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