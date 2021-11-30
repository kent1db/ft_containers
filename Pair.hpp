//
// Created by Quentin Robert de beauchamp on 11/25/21.
//
#ifndef PAIR_HPP
#define PAIR_HPP
namespace ft {
	template<typename T1, typename T2>
	class pair
	{
	public:
		pair(): first(0), second(0) {};

		template<typename V, typename W>
		pair(const pair<V, W> &pr) : first(pr.first), second(pr.second) {}

		pair(T1 const &first, T2 const &second) : first(first), second(second) {}

		pair& operator=(pair const& __p) {
			first = __p.first;
			second = __p.second;
			return *this;
		}

		bool operator==(ft::pair<T1, T2> const &inst) {
			return this->first == inst.first && this->second == inst.second;
		}

		bool operator!=(ft::pair<T1, T2> &inst) {
			return !(*this == inst);
		}

		bool operator<(ft::pair<T1, T2> &inst) {
			return this->first < inst.first ||
				   (!(inst.first < this->first) && this->second < inst.second);
		}

		bool operator<=(ft::pair<T1, T2> &inst) {
			return !(inst < *this);
		}

		bool operator>(ft::pair<T1, T2> &inst) {
			return inst < *this;
		}

		bool operator>=(ft::pair<T1, T2> &inst) {
			return !(*this < inst);
		}

	public:
		T1 first;
		T2 second;
	};

	template<typename T1, typename T2>
	pair<T1, T2> make_pair(T1 x, T2 y) {
		return pair<T1, T2>(x, y);
	}
}

#endif