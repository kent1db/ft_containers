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
		class bidirectional_iterator : public iterators_traits<iterator<bidirectional_iterator_tag, T> >
		{
			protected:
			typename bidirectional_iterator::pointer _p;
			public:
			/* Constructor */
			bidirectional_iterator(typename bidirectional_iterator::pointer x) : _p(x) {}

			// Default constructor
			bidirectional_iterator() {}

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
				++_p;
				return (*this);
			}

			bidirectional_iterator operator++(int) {
				bidirectional_iterator tmp(*this);
				++_p;
				return (tmp);
			}

			bidirectional_iterator &operator--() {
				--_p;
				return (*this);
			}

			bidirectional_iterator operator--(int) {
				bidirectional_iterator tmp(*this);
				--_p;
				return (tmp);
			}
		};
	public:
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef std::pair<const Key, T>						value_type;
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
		tree<value_type, allocator_type> 	RBtree;
		size_type 			_size;
		Alloc				_alloc;

//		/// Constructor ///
//		explicit map (const key_compare& comp = key_compare(),
//					  const allocator_type& alloc = allocator_type()) : RBtree(NULL) {}
//
//		template <class InputIterator>
//		map (InputIterator first, typename enable_if<(ft::is_same<InputIterator, typename bidirectional_iterator::pointer>::value || is_same<InputIterator, bidirectional_iterator>::value) && !ft::is_integral<InputIterator>::value, InputIterator>::type last,
//			 const key_compare& comp = key_compare(),
//			 const allocator_type& alloc = allocator_type()) : RBtree(NULL) {
//			while (first != last) {
//		 		RBtree.insertElem(RBtree.createElement(*first), RBtree.getRoot());
//		 		first++;
//			}
//		}
//
//		map (const map& x) : RBtree(x.RBtree) {}
//
//		/// Operator ///
//
//		map & operator=(const map& x) {}
	};
}

#endif