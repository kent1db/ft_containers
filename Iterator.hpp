#ifndef Iterator_hpp
#define Iterator_hpp

#include <cstddef> // ptrdiff_t

namespace ft {
	struct bidirectional_iterator_tag {};
	struct random_access_iterator_tag {};

	template<typename Category, typename T, typename Distance = ptrdiff_t,
			typename Pointer = T *, typename Reference = T &>
	struct iterator
	{
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;
	};

	template<typename Iterator>
	struct iterators_traits
	{
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template<typename T>
	struct iterators_traits<T *>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template<typename T>
	struct iterators_traits<const T *>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T *pointer;
		typedef const T &reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template<typename Iterator>
	struct reverse_iterator : public iterators_traits<Iterator>
	{
	protected:
		Iterator current;
	public:
		typedef Iterator	iterator_type;
		typedef typename iterators_traits<Iterator>::difference_type   difference_type;
		typedef typename iterators_traits<Iterator>::pointer           pointer;
		typedef typename iterators_traits<Iterator>::reference         reference;

		reverse_iterator() :current() {}

		explicit reverse_iterator(iterator_type it) : current(it) {}

		reverse_iterator (const reverse_iterator<Iterator>& rev_it) : current(rev_it.current) {}

		iterator_type  base() const {
			return (current);
		}

		reference operator*() const {
			iterator_type tmp = current;
			return (*--tmp);
		}

		pointer operator->() const {
			return &(operator*());
		}

		reverse_iterator &operator++() {
			--current;
			return (*this);
		}

		reverse_iterator &operator++(int) {
			reverse_iterator tmp(*this);
			--current;
			return (tmp);
		}

		reverse_iterator &operator--() {
			++current;
			return (*this);
		}

		reverse_iterator &operator--(int) {
			reverse_iterator tmp(*this);
			++current;
			return (tmp);
		}

		reverse_iterator operator+(difference_type n) const {
			return reverse_iterator(current - n);
		}

		reverse_iterator &operator+=(difference_type n) {
			current -= n;
			return (*this);
		}

		reverse_iterator operator-(difference_type n) const {
			return reverse_iterator(current + n);
		}

		reverse_iterator &operator-=(difference_type n) {
			current += n;
			return (*this);
		}

		reference operator[](difference_type n) const {
			return *(*this + n);
		}
	};

	template<typename Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs) {
		return (lhs.current == rhs.current);
	}

	template<typename Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs) {
		return !(lhs == rhs);
	}
	template<typename Iterator>
	bool operator<(const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs) {
		return (lhs.current > rhs.current);
	}
	template<typename Iterator>
	bool operator>(const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs) {
		return (lhs.current < rhs.current);
	}
	template<typename Iterator>
	bool operator<=(const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs) {
		return !(lhs > rhs);
	}
	template<typename Iterator>
	bool operator>=(const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs) {
		return !(lhs < rhs);
	}

	template<typename Iterator>
	reverse_iterator<Iterator> operator+ (
			typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& rev_it) {
		return (rev_it.current - n);
	}

	template<typename Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (
			const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs) {
		return (rhs.current - lhs.current);
	}


}

#endif