//
// Created by Quentin Robert de beauchamp on 10/12/21.
//

#ifndef CONTAINER_VECTOR_HPP
#define CONTAINER_VECTOR_HPP
#include <memory> /* allocator */
#include <iostream>
#include <cstddef> /* ptrdiff_t */
#include "Iterator.hpp"
#include "Enable.hpp"
#include "LexicoComp.hpp"
#include <cmath>

namespace ft {
	template<typename T, typename Alloc = std::allocator <T> >
	class vector
	{
		class random_access_iterator : public iterators_traits<iterator<random_access_iterator_tag, T> >
		{
		protected:
			typename random_access_iterator::pointer _p;
		public:
			/* Constructor */
			random_access_iterator(typename random_access_iterator::pointer x) : _p(x) {}

			// Default constructor
			random_access_iterator() {}

			// Copy constructor
			random_access_iterator(const random_access_iterator &x) {
				if (*this != x)
					*this = x;
			}

			// Destructor
			~random_access_iterator() {}

			// Operator
			random_access_iterator &operator=(const random_access_iterator &rhs) {
				_p = rhs._p;
				return (*this);
			}

			bool operator==(const random_access_iterator &rhs) const {
				return (_p == rhs._p);
			}

			bool operator!=(const random_access_iterator &rhs) const {
				return (_p != rhs._p);
			}

			typename random_access_iterator::reference operator*() const {
				return (*_p);
			}

			typename random_access_iterator::pointer operator->() const {
				return (_p);
			}

			random_access_iterator &operator++() {
				++_p;
				return (*this);
			}

			random_access_iterator operator++(int) {
				random_access_iterator tmp(*this);
				++_p;
				return (tmp);
			}

			random_access_iterator &operator--() {
				--_p;
				return (*this);
			}

			random_access_iterator operator--(int) {
				random_access_iterator tmp(*this);
				--_p;
				return (tmp);
			}

			friend random_access_iterator operator+(typename random_access_iterator::difference_type a, random_access_iterator const& rhs) {
				return rhs._p + a;
			}

			random_access_iterator operator+(typename random_access_iterator::difference_type add) const {
				return (_p + add);
			}

			typename random_access_iterator::difference_type operator-(const random_access_iterator &rhs) {
				return (_p - rhs._p);
			}

			random_access_iterator operator-(typename random_access_iterator::difference_type add) const {
				return (_p - add);
			}

			bool operator<(const random_access_iterator &rhs) const {
				return (_p < rhs._p);
			}

			bool operator<=(const random_access_iterator &rhs) const {
				return (_p <= rhs._p);
			}

			bool operator>(const random_access_iterator &rhs) const {
				return (_p > rhs._p);
			}

			bool operator>=(const random_access_iterator &rhs) const {
				return (_p >= rhs._p);
			}

			random_access_iterator &operator+=(typename random_access_iterator::difference_type rhs) {
				_p += rhs;
				return (*this);
			}

			random_access_iterator &operator-=(typename random_access_iterator::difference_type rhs) {
				_p -= rhs;
				return (*this);
			}

			typename random_access_iterator::reference operator[](typename random_access_iterator::difference_type x) const {
				return (_p[x]);
			}
		};
	public :
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef random_access_iterator						iterator;
		typedef random_access_iterator						const_iterator;
		typedef ptrdiff_t									difference_type;
		typedef size_t										size_type;
		typedef reverse_iterator<random_access_iterator>	const_reverse_iterator;
		typedef reverse_iterator<random_access_iterator>	reverse_iterator;
		class outOfRange : std::exception {
			const char* what() const throw (){
				return ("Out of Range");
			}
		}out;
	private :
		int capacity(int n) { // Capacity Strategy
			return (n + roundf(2 + (n * 0.1)));
		}
		typename iterator::pointer _array;
		size_type _size;
		size_type _capacity;
		Alloc _alloc;
	public :

		/** Constructor **/

		// Default constructor
		explicit vector(const allocator_type& alloc = allocator_type()) : _array(NULL), _size(0), _capacity(0), _alloc(alloc) {}

		// Fill constructor
		explicit vector(size_type n, const value_type & val = value_type(), const allocator_type& alloc = allocator_type()) : _size(n), _capacity(capacity(n)), _alloc(alloc) {
			_array = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++) {
				_alloc.construct(&_array[i], val);
			}
		}

		// Range constructor
		template <typename InputIterator>
		vector (InputIterator first, typename enable_if<(ft::is_same<InputIterator, typename random_access_iterator::pointer>::value || is_same<InputIterator, random_access_iterator>::value) && !ft::is_integral<InputIterator>::value, InputIterator>::type last, const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _alloc(alloc){
			size_type i = 0;
			for (InputIterator it = first; it != last; it++) {
				_size++;
			}
			_capacity = capacity(_size);
			_array = _alloc.allocate(_capacity);
			for (InputIterator it = first; it != last; it++) {
				_alloc.construct(&_array[i++], *it);
			}
		}

		// Copy constructor
		vector(const vector &x): _size(0), _capacity(0) {
			*this = x;
		}

		/** Destructor **/

		// Default destructor
		~vector() {
			clear();
		}

		/** Operator = **/

		vector & operator=(const vector& x){
			if (this == &x)
				return (*this);
			clear();
			_capacity = x._capacity;
			_alloc = x._alloc;
			_array = _alloc.allocate(_capacity);
			for (_size = 0; _size < x._size; _size++)
				_alloc.construct(&_array[_size], x._array[_size]);
			return (*this);
		}

		/** Iterator **/

		iterator begin() {
			return (&_array[0]);
		}

		const_iterator begin() const{
			return (&_array[0]);
		}

		reverse_iterator rbegin() {
			return (reverse_iterator(end()));
		}

		const_reverse_iterator rbegin() const {
			return (reverse_iterator(end()));
		}

		reverse_iterator rend() {
			return (reverse_iterator(begin()));
		}
		const_reverse_iterator rend() const {
			return (reverse_iterator(begin()));
		}

		const_iterator end() const{
			return (&_array[_size]);
		}

		iterator end(){
			return (&_array[_size]);
		}

		/** Capacity **/

		size_type size() const {
			return (_size);
		}

		size_type max_size() const {
			int ln = (sizeof(T) > 1 ? log(sizeof(T) ) / log(2) : 1);
			return (pow(2, 64 - ln) - (long double) 1);
		}

		void resize (size_type n, value_type val = value_type()) {
			if (n < _size) {
				while (n < _size)
					_alloc.destroy(&_array[_size--]);
			}
			else if (n > _size && n <= _capacity) {
				while (_size < n)
					_alloc.construct(&_array[_size++], val);
			}
			else {
				clear();
				_capacity = capacity(n);
				_array = _alloc.allocate(_capacity);
				for (_size = 0; _size < n; _size++)
					_alloc.construct(&_array[_size], val);
			}
		}

		size_type capacity() const {
			return (_capacity);
		}

		bool empty() const {
			return (_size == 0);
		}

		void reserve (size_type n) {
			if (n > _capacity) {
				typename random_access_iterator::pointer tmp;
				tmp = _alloc.allocate(capacity(n));
				for  (size_type i = 0; i < _size; i++) {
					_alloc.construct(&tmp[i], _array[i]);
					_alloc.destroy(&_array[i]);
				}
				if (_capacity)
					_alloc.deallocate(_array, _capacity);
				_array = tmp;
				_capacity = capacity(n);
			}
		}

		reference operator[](size_type i){
			if (i >= _size)
				throw out;
			return (_array[i]);
		}

		reference at(size_type n) {
			if (n >= _size)
				throw out;
			return (_array[n]);
		}

		const_reference at(size_type n) const {
			if (n >= _size)
				throw out;
			return (_array[n]);
		}

		reference front() {
			return (_array[0]);
		}

		const_reference front() const {
			return (_array[0]);
		}

		reference back() {
			return (_array[_size - 1]);
		}

		const_reference back() const {
			return (_array[_size - 1]);
		}

		template <class InputIterator>
		void assign (InputIterator first, typename enable_if<(ft::is_same<InputIterator, typename random_access_iterator::pointer>::value || is_same<InputIterator, random_access_iterator>::value) && !ft::is_integral<InputIterator>::value, InputIterator>::type last) {
			size_type count = 0;
			for (InputIterator it = first; it != last; it++){
				count++;
			}
			reserve(count);
			size_type before_size = _size;
			_size = 0;
			for (InputIterator it = first; it != last; it++){
				if (_size < before_size)
					_alloc.destroy(&_array[_size]);
				_alloc.construct(&_array[_size++], *it);
			}
			while (_size < before_size)
				_alloc.destroy(&_array[_size++]);
			_size = count;
		}

		void assign (size_type n, const value_type& val) {
			size_type i;
			reserve(n);
			for (i = 0; i < n; i++) {
				if (i < _size)
					_alloc.destroy(&_array[i]);
				_alloc.construct(&_array[i], val);
			}
			while (i < _size)
				_alloc.destroy(&_array[i++]);
			_size = n;
		}

		void push_back (const value_type& val) {
			reserve(_size + 1);
			_alloc.construct(&_array[_size++], val);
		}

		void pop_back() {
			_alloc.destroy(&_array[--_size]);
		}

		iterator insert(iterator position, const value_type& val) {
			typename random_access_iterator::difference_type p = position - begin();
			reserve(_size + 1);
			typename random_access_iterator::pointer pos = &_array[p];
			typename random_access_iterator::pointer it = &_array[_size];
			while (it != pos) {
				_alloc.construct(it, *(it - 1));
				_alloc.destroy(--it);
			}
			if (it == pos)
				_alloc.construct(it, val);
			_size++;
			return (it);
		}

		void insert(iterator position, size_type n, const value_type& val) {
			while (n--) {
				position = insert(position, val);
			}
		}

		template <class InputIterator>
		void insert (iterator position, InputIterator first, typename enable_if<(ft::is_same<InputIterator, typename random_access_iterator::pointer>::value || is_same<InputIterator, random_access_iterator>::value) && !ft::is_integral<InputIterator>::value, InputIterator>::type last) {
			for (InputIterator i = first; i < last; i++) {
				position = insert(position, *i);
				position ++;
			}
		}

		iterator erase (iterator position) {
			typename random_access_iterator::difference_type p = position - begin();
			_alloc.destroy(&_array[p]);
			_size--;
			typename random_access_iterator::pointer it = &_array[p];
			typename random_access_iterator::pointer pos = &_array[_size];
			while (it != pos) {
				_alloc.construct(it, *(it + 1));
				_alloc.destroy(++it);
			}
			return (position);
		}

		iterator erase (iterator first, iterator last) {
			typename random_access_iterator::difference_type p = last - first;
			while (p--)
				erase(first);
			return (first);
		}

		void swap (vector& x) {
			vector<T> tmp(*this);
			*this = x;
			x = tmp;
		}

		void clear() {
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_array[i]);
			if (_capacity > 0)
				_alloc.deallocate(_array, _capacity);
			_size = 0;
			_capacity = 0;
		}

		allocator_type get_allocator() const {
			return (_alloc);
		}

		friend bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			if (lhs.size() != rhs.size())
				return false;
			return (equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

		friend bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return (!(lhs == rhs));
		}

		friend bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}

		friend bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return (!(rhs < lhs));
		}

		friend bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return (rhs < lhs);
		}

		friend bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return (!(lhs < rhs));
		}
	};

	template< class T, class Alloc >
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
		x.swap(y);
	}
}

#endif
