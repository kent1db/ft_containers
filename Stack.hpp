#ifndef STACK_HPP
#define STACK_HPP

#include "Vector.hpp"
#include "Iterator.hpp"
namespace ft {
	template <typename T, typename Container = ft::vector<T> >
	class stack {
	public:
		typedef Container container_type;
		typedef typename Container::value_type value_type;
		typedef typename Container::size_type size_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;
	protected:
		container_type c;
	public:
		explicit stack (const container_type& ctnr = container_type()) : c(ctnr) {}

		bool empty() const {
			return (c.empty());
		}

		size_type size() const {
			return (c.size());
		}

		value_type& top() {
			return (c.back());
		}

		const value_type& top() const {
			return (c.back());
		}

		void push (const value_type& val) {
			return (c.push_back(val));
		}

		void pop() {
			return (c.pop_back());
		}
		friend bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return (lhs.c == rhs.c);
		}

		friend bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return !(lhs == rhs);
		}

		friend bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return (lhs.c < rhs.c);
		}

		friend bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return (lhs.c > rhs.c);
		}

		friend bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return !(lhs > rhs);
		}

		friend bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return !(lhs < rhs);
		}
	};

}

#include <iostream>

#endif