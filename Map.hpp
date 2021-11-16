#ifndef MAP_HPP
#define MMAP_HPP
#include <iostream>
#include "Iterator.hpp"

namespace ft {
	template <	typename Key,
	        	typename T,
	        	typename Compare = std::less<Key>,
	        	typename Alloc = std::allocator<std::pair<const Key, T > > >
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
	};
}

#endif