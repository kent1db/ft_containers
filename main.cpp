#include "Vector.hpp"
#include <iterator>
#include "Stack.hpp"
#include <vector>
#include <map>
#include "Pair.hpp"
#include "Map.hpp"
#include <list>
#include <algorithm>
#include "RedBlackTree.hpp"
#include "Set.hpp"

#define REDC        "\x1B[31m"
#define GRNC        "\x1B[32m"
#define RESETC        "\x1B[0m"
#define BLACKC        "\x1B[37m"
int err = 0;
int i = 0;

template<typename T>
void EXPECT_EQ(T my, T your) {
	if (my != your) {
		std::cerr << REDC << "\tFAIL : EXCEPT EQUAL BUT NOT EQUAL" << RESETC << std::endl;
		err = 1;
	}
}

template<typename T>
void EXPECT_NE(T my, T your) {
	if (my == your) {
		std::cerr << REDC << "\tFAIL : EXCEPT NOT EQUAL BUT EQUAL" << RESETC << std::endl;
		err = 1;
	}
}

void EXPECT_FALSE(bool check) {
	if (check) {
		std::cerr << REDC << "\tFAIL : EXCEPT FALSE BUT TRUE" << RESETC << std::endl;
		err = 1;
	}
}

void EXPECT_TRUE(bool check) {
	if (!check) {
		std::cerr << REDC << "\tFAIL : EXCEPT TRUE BUT FALSE" << RESETC << std::endl;
		err = 1;
	}
}

void displayStatus(const std::string &test) {
	if (err) {
		std::cout << GRNC << "❌ TEST-" << i++ << " : " << test << std::endl;
		err = 0;
	} else
		std::cout << GRNC << "✅ TEST-" << i++ << " : " << test << std::endl;
}

template<typename T>
void testContentOfVector(T content, size_t size, ft::vector<T> a) {
	size_t count = 0;
	T *array;
	if (std::is_integral<T>::value)
		array = new T[size];
	for (size_t i = 0; i < size; ++i)
		array[i] = content;
	for (typename ft::vector<T>::iterator it = a.begin(); it < a.end(); it++) {
		if (count > size)
			break;
		EXPECT_EQ(*it, array[count]);
		count++;
	}
	EXPECT_EQ(count, size);
	if (std::is_integral<T>::value)
		delete[] array;
}

template<typename T>
void testContentOfVector(T content, size_t size) {
	size_t count = 0;
	ft::vector<T> a(size, content);
	T *array = nullptr;
	if (std::is_integral<T>::value)
		array = new T[size];
	for (size_t i = 0; i < size; ++i)
		array[i] = content;
	for (typename ft::vector<T>::iterator it = a.begin(); it < a.end(); it++) {
		if (count > size)
			break;
		EXPECT_EQ(*it, array[count]);
		count++;
	}
	EXPECT_EQ(count, size);
	if (std::is_integral<T>::value)
		delete[] array;
	if (size != 0)
		EXPECT_FALSE(a.empty());
	else
		EXPECT_TRUE(a.empty());
}

void Constructor_Operator_TEST(void) {
	ft::vector<int> g;
	EXPECT_EQ(g.empty(), true);
	EXPECT_EQ(g.size(), (size_t) 0);
	EXPECT_EQ(g.capacity(), (size_t) 0);
	size_t size_a = 1000;
	ft::vector<char> a(size_a, 'b');
	testContentOfVector('b', size_a, a);
	const ft::vector<char> &c(a);
	EXPECT_EQ(a, c);
	const ft::vector<char> &d = a;
	EXPECT_EQ(a, d);
	testContentOfVector(1, 4200);
	testContentOfVector("blablou", 0);
	testContentOfVector(true, 4200);
	testContentOfVector(static_cast<unsigned long long int>(199), 100);
	ft::vector<std::string> testVec(2, static_cast<std::string>("coucou"));
	EXPECT_EQ(static_cast<std::string>(*testVec.begin()), static_cast<std::string>("coucou"));
	std::string end = *(testVec.end() - 1);
	EXPECT_EQ(end, static_cast<std::string>("coucou"));
	EXPECT_NE(*testVec.end(), static_cast<std::string>("coucou"));
	int myints[] = {1, 2, 3, 4, 5, 6, 7};
	ft::vector<int> john(myints, myints + 5);
	displayStatus("Constructor And Operator Equal With Different Types");
}

void Reverse_Iterator_TEST(void) {
	ft::vector<int> vector;  // three ints with a value of 100
	std::vector<int> svector;         // three ints with a value of 100
	for (int i = 0; i < 10000; ++i) {
		vector.push_back(i);
		svector.push_back(i);
		vector.push_back(i);
		svector.push_back(i);
	}
	ft::vector<int>::reverse_iterator rit = vector.rbegin();
	std::vector<int>::reverse_iterator srit = svector.rbegin();
	int r = rit[10];
	int sr = srit[10];
	EXPECT_EQ(r, sr);
	EXPECT_EQ(*(rit + 5), *(srit + 5));
	EXPECT_EQ(*(rit + 205), *(srit + 205));
	while (rit != vector.rend())
		EXPECT_EQ(*srit++, *rit++);
	int r2 = rit[-10];
	int sr2 = srit[-10];
	EXPECT_EQ(r2, sr2);
	EXPECT_EQ(rit.base(), vector.begin());
	EXPECT_EQ(*(rit -= 5), *(srit -= 5));
	EXPECT_EQ(*rit--, *srit--);
	EXPECT_EQ(*--rit, *--srit);
	EXPECT_EQ(rit, rit);
	EXPECT_FALSE(rit < rit);
	EXPECT_TRUE(rit <= ++rit);
	EXPECT_TRUE(rit < (rit + 1));
	EXPECT_TRUE(rit > (rit - 1));
	EXPECT_FALSE(rit != rit);
	EXPECT_TRUE(rit != (rit + 1));
	displayStatus("Reverse Iterator");
}

void Const_Rev_Iterator_TEST(void) {
	ft::vector<int> vector;  // three ints with a value of 100
	std::vector<int> svector;         // three ints with a value of 100
	for (int i = 0; i < 10000; ++i) {
		vector.push_back(i);
		svector.push_back(i);
		vector.push_back(i);
		svector.push_back(i);
	}
	ft::vector<int>::const_reverse_iterator rit = vector.rbegin();
	std::vector<int>::const_reverse_iterator srit = svector.rbegin();
	int r = rit[10];
	int sr = srit[10];
	EXPECT_EQ(r, sr);
	EXPECT_EQ(*(rit + 5), *(srit + 5));
	EXPECT_EQ(*(rit + 205), *(srit + 205));
	while (rit != vector.rend())
		EXPECT_EQ(*srit++, *rit++);
	int r2 = rit[-10];
	int sr2 = srit[-10];
	EXPECT_EQ(r2, sr2);
	EXPECT_EQ(rit.base(), vector.begin());
	EXPECT_EQ(*(rit -= 5), *(srit -= 5));
	EXPECT_EQ(*rit--, *srit--);
	EXPECT_EQ(*--rit, *--srit);
	EXPECT_EQ(rit, rit);
	EXPECT_FALSE(rit < rit);
	EXPECT_TRUE(rit <= ++rit);
	EXPECT_TRUE(rit < (rit + 1));
	EXPECT_TRUE(rit > (rit - 1));
	EXPECT_FALSE(rit != rit);
	EXPECT_TRUE(rit != (rit + 1));
	displayStatus("Reverse Const Iterator");
}

void ConstIterator_TEST(void) {
	ft::vector<int> vector(3, 100);  // three ints with a value of 100
	ft::vector<int>::const_iterator it;
	ft::vector<int>::const_iterator it3(it);
	ft::vector<int>::iterator it2;
	for (it = vector.begin(); it != vector.end(); ++it) {
// *it += 5;
	}
	it2 = --vector.end();
	it = it2;
	it3 = it2;
// it2 = it;
	displayStatus("Const Iterator");
}

void Glagan_TEST(void) {
	ft::vector<int> myvector;
	ft::vector<int>::iterator it;
	std::vector<int> stdvector;
	std::vector<int>::iterator sit;
	it = myvector.end();
	sit = stdvector.end();
	for (int i = 0; i < 20; ++i) {
		it = myvector.insert(it, i);
		sit = stdvector.insert(sit, i);
	}
	EXPECT_EQ(myvector.back(), stdvector.back());
	displayStatus("Insert");
}

void IteratorOP1_TEST(void) {
	ft::vector<int> myvector;
	ft::vector<int>::iterator it;
	std::vector<int> stdvector;
	std::vector<int>::iterator stdit;
	for (int i = 0; i < 20; ++i) {
		myvector.push_back(i);
		stdvector.push_back(i);
	}
	EXPECT_EQ(myvector.front(), stdvector.front());
	EXPECT_EQ(myvector.back(), stdvector.back());
	EXPECT_EQ(myvector.size(), stdvector.size());
	it = myvector.begin();
	stdit = stdvector.begin();
	EXPECT_EQ(*it, *stdit);
	it += 10;
	stdit += 10;
	EXPECT_EQ(*it, *stdit);
	it -= 5;
	stdit -= 5;
	EXPECT_EQ(*it, *stdit);
	it -= 5;
	stdit -= 5;
	EXPECT_EQ(*it, *stdit);
	EXPECT_EQ(*(it + 10), *(stdit + 10));
	EXPECT_EQ(it[10], stdit[10]);
	displayStatus("Operator 1");
}

//
void IteratorOP2_TEST(void) {
	ft::vector<std::pair<int, int> > myvector2;
	ft::vector<std::pair<int, int> >::iterator it2;
	std::vector<std::pair<int, int> > stdvector2;
	std::vector<std::pair<int, int> >::iterator stdit2;
	std::pair<int, int> p(1, 2);
	myvector2.push_back(p);
	stdvector2.push_back(p);
	it2 = myvector2.begin();
	stdit2 = stdvector2.begin();
	EXPECT_EQ(it2->first, stdit2->first);
	EXPECT_EQ(it2->second, stdit2->second);
	displayStatus("Operator 2");
}

void IteratorOP3_TEST(void) {
	ft::vector<int> myvector;
	ft::vector<int>::iterator it;
	ft::vector<int>::const_iterator cit;
	std::vector<int> stdvector;
	std::vector<int>::iterator stdit;
	std::vector<int>::const_iterator cstdit;
	for (int i = 0; i < 10; ++i) {
		myvector.push_back(i);
		stdvector.push_back(i);
	}
	it = myvector.begin();
	stdit = stdvector.begin();
	cit = myvector.begin();
	cstdit = stdvector.begin();
	EXPECT_EQ(*(5 + it), *(5 + stdit));
	EXPECT_EQ(*(5 + cit), *(5 + cstdit));
	EXPECT_EQ(cit, it);
	EXPECT_EQ(it, cit);
	displayStatus("Operator 3");
}

void RelationalOperators_TEST(void) {
	int myint[] = {0, 1, 2, 3, 4};
	ft::vector<int> foo(3, 100);                          // three ints with a value of 100
	ft::vector<int> bar(2, 200);                          // two ints with a value of 200
	ft::vector<int> three(myint, myint + 3);  // three ints with a value of 100
	ft::vector<int> four(myint, myint + 4);   // two ints with a value of 200

	EXPECT_FALSE(foo == bar);
	EXPECT_TRUE(foo != bar);
	EXPECT_FALSE(foo > bar);
	EXPECT_TRUE(foo < bar);
	EXPECT_FALSE(foo >= bar);
	EXPECT_TRUE(foo <= bar);
	EXPECT_FALSE(three == four);
	EXPECT_TRUE(three != four);
	EXPECT_FALSE(three > four);
	EXPECT_TRUE(three < four);
	EXPECT_FALSE(three >= four);
	EXPECT_TRUE(three <= four);
	displayStatus("Relational Operator");
}

//
void Clear_TEST(void) {
	ft::vector<int> myvector;
	myvector.push_back(100);
	myvector.push_back(200);
	myvector.push_back(300);
	myvector.clear();
	myvector.push_back(1101);
	myvector.push_back(2202);
	EXPECT_EQ(myvector.front(), 1101);
	EXPECT_EQ(myvector.back(), 2202);
	EXPECT_EQ(myvector.size(), size_t(2));
	displayStatus("Clear");
}

//
void Swap_TEST(void) {
	ft::vector<int> foo(3, 100);  // three ints with a value of 100
	ft::vector<int> bar(5, 200);  // five ints with a value of 200

	EXPECT_EQ(foo.size(), size_t(3));
	EXPECT_EQ(bar.size(), size_t(5));
	foo.swap(bar);
	EXPECT_EQ(foo.size(), size_t(5));
	EXPECT_EQ(bar.size(), size_t(3));
	displayStatus("Swap");
}

//
void Erase_TEST(void) {
	ft::vector<int> myvector;

// set some values (from 1 to 10)
	for (int i = 1; i <= 10; i++)
		myvector.push_back(i);

// erase the 6th element
	myvector.erase(myvector.begin() + 5);
// erase the first 3 elements:
	myvector.erase(myvector.begin(), myvector.begin() + 3);
	int resultarr[] = {4, 5, 7, 8, 9, 10};
	for (size_t i = 0; i < myvector.size(); ++i)
		EXPECT_EQ(myvector[i], resultarr[i]);
	displayStatus("Erase");
}

void Insert_TEST(void) {
	ft::vector<int> myvector(3, 100);
	ft::vector<int>::iterator it;
	it = myvector.begin();
	it = myvector.insert(it, 200);
	myvector.insert(it, 2, 300);

// "it" no longer valid, get a new one:
	it = myvector.begin();
	ft::vector<int> anothervector(2, 400);
	myvector.insert(it + 2, anothervector.begin(), anothervector.end());
	int myarray[] = {501, 502, 503};
	myvector.insert(myvector.begin(), myarray, myarray + 3);

// 503, 502, 501, 300, 300, 400, 400, 200, 100, 100, 100,
	int resultarr[] = {501, 502, 503, 300, 300, 400, 400, 200, 100, 100, 100};
	for (size_t i = 0; i < myvector.size(); ++i)
// std::cout << myvector[i] << ", ";
		EXPECT_EQ(myvector[i], resultarr[i]);
	displayStatus("Insert");
}

void InsertPos_TEST(void) {
	ft::vector<int> myvector;
	ft::vector<int>::iterator it;
	std::vector<int> stdvector;
	std::vector<int>::iterator sit;
	it = myvector.end();
	sit = stdvector.end();
	for (int i = 0; i < 20; ++i) {
		it = myvector.insert(it, i);
		sit = stdvector.insert(sit, i);
	}
	it = myvector.insert(myvector.begin(), -1);
	sit = stdvector.insert(stdvector.begin(), -1);
	EXPECT_EQ(myvector.size(), stdvector.size());
	EXPECT_EQ(*it, *sit);
	for (int i = 0; i < 20; ++i)
		EXPECT_EQ(myvector[i], stdvector[i]);
	displayStatus("Insert pos");
}

void InsertN_TEST(void) {
	ft::vector<int> myvector(3, 100);
	std::vector<int> stdvector(3, 100);
	for (int i = 0; i < 20; ++i) {
		myvector.insert(myvector.end(), 3, i);
		stdvector.insert(stdvector.end(), 3, i);
	}
	myvector.insert(myvector.begin(), 10, 200);
	stdvector.insert(stdvector.begin(), 10, 200);
	EXPECT_EQ(myvector.size(), stdvector.size());
	for (int i = 0; i < 20; ++i)
		EXPECT_EQ(myvector[i], stdvector[i]);
	displayStatus("Insert n");
}

void InsertRange_TEST(void) {
	ft::vector<int> myvector, myvector2;
	ft::vector<int>::iterator it;
	std::vector<int> stdvector, stdvector2;
	for (int i = 0; i < 100; ++i) {
		myvector.insert(myvector.end(), 3, i);
		stdvector.insert(stdvector.end(), 3, i);
	}
	myvector2.insert(myvector2.begin(), myvector.begin(), myvector.begin() + 20);
	stdvector2.insert(stdvector2.begin(), stdvector.begin(), stdvector.begin() + 20);
	EXPECT_EQ(myvector.size(), stdvector.size());
	for (int i = 0; i < 20; ++i)
		EXPECT_EQ(myvector[i], stdvector[i]);
	myvector2.insert(myvector2.end(), myvector.end() - 40, myvector.end());
	stdvector2.insert(stdvector2.end(), stdvector.end() - 40, stdvector.end());
	EXPECT_EQ(myvector.size(), stdvector.size());
	for (int i = 0; i < 20; ++i)
		EXPECT_EQ(myvector[i], stdvector[i]);
	displayStatus("Insert range");
}

void PopBack_TEST(void) {
	ft::vector<int> myvector;
	int sum(0);
	myvector.push_back(100);
	myvector.push_back(200);
	myvector.push_back(300);
	while (!myvector.empty()) {
		sum += myvector.back();
		myvector.pop_back();
	}
	EXPECT_EQ(sum, 600);
	displayStatus("Pop Back");
}

void PushBack_TEST(void) {
	ft::vector<int> first;
	ft::vector<int> second(1000, 5);
	ft::vector<int> third(second.begin(), second.begin() + 100);
	for (int i = 0; i < 3000; ++i) {
		first.push_back(i);
		second.push_back(i);
		third.push_back(i);
	}
	EXPECT_EQ(first.size(), size_t(3000));
	EXPECT_EQ(second.size(), size_t(4000));
	EXPECT_EQ(third.size(), size_t(3100));
	displayStatus("Push Back");
}

void Assign_TEST(void) {
	ft::vector<int> first;
	ft::vector<int> second;
	ft::vector<int> third;
	first.assign(7, 100);  // 7 ints with a value of 100

	ft::vector<int>::iterator it;
	it = first.begin() + 1;
	second.assign(it, first.end() - 1);      // the 5 central values of first

	int myints[] = {1776, 7, 4};
	third.assign(myints, myints + 3);  // assigning from array.

	EXPECT_EQ(first.size(), size_t(7));
	EXPECT_EQ(second.size(), size_t(5));
	EXPECT_EQ(third.size(), size_t(3));
	displayStatus("Assign");
}

void VFrontBack_TEST(void) {
	ft::vector<int> myvector;
	myvector.push_back(78);
	EXPECT_EQ(myvector.front(), myvector.back());
	myvector.push_back(16);

// now front equals 78, and back 16
	EXPECT_EQ(myvector.front(), 78);
	myvector.front() -= myvector.back();
	EXPECT_EQ(myvector.front(), 62);
	EXPECT_EQ(myvector.back(), 16);
	displayStatus("Front back");
}

void At_TEST(void) {
	ft::vector<int> myvector(10);      // 10 zero-initialized ints

// assign some values:
	for (size_t i = 0; i < myvector.size(); i++)
		myvector.at(i) = i;
	for (size_t i = 0; i < myvector.size(); i++)
		EXPECT_EQ(myvector.at(i), int(i));
	displayStatus("At");
}

void BracketOperator_TEST(void) {
	ft::vector<int> myvector(10);      // 10 zero-initialized elements
	std::vector<int> stdvector(10);         // 10 zero-initialized elements

	ft::vector<int>::size_type sz = myvector.size();

// assign some values:
	for (size_t i = 0; i < sz; i++) {
		myvector[i] = i;
		stdvector[i] = i;
	}
// reverse vector using operator[]:
	for (size_t i = 0; i < sz / 2; i++) {
		int temp;
		temp = myvector[sz - 1 - i];
		myvector[sz - 1 - i] = myvector[i];
		myvector[i] = temp;
		temp = stdvector[sz - 1 - i];
		stdvector[sz - 1 - i] = stdvector[i];
		stdvector[i] = temp;
	}
	for (size_t i = 0; i < sz; i++)
		EXPECT_EQ(myvector[i], stdvector[i]);
	displayStatus("Bracket");
}

void Reserve_TEST(void) {
	ft::vector<int> bar;
	std::vector<int> stdbar;
	bar.reserve(100);
	stdbar.reserve(100);
	for (int i = 0; i < 100; ++i) {
		bar.push_back(i);
		stdbar.push_back(i);
	}
	EXPECT_EQ(bar.size(), stdbar.size());
	bar.reserve(50);
	stdbar.reserve(50);
	EXPECT_EQ(bar.size(), stdbar.size());
	bar.push_back(10);
	stdbar.push_back(10);
	EXPECT_EQ(bar.size(), stdbar.size());
	ft::vector<int> bar2(10, 100);
	std::vector<int> stdbar2(10, 100);
	EXPECT_EQ(bar2.size(), stdbar2.size());
	bar2.push_back(10);
	stdbar2.push_back(10);
	EXPECT_EQ(bar2.size(), stdbar2.size());
	displayStatus("Reserve");
}

void Empty_TEST(void) {
	ft::vector<int> myvector;
	std::vector<int> stdvector;
	int sum = 0;
	int stdsum = 0;
	for (int i = 1; i <= 10; i++) {
		myvector.push_back(i);
		stdvector.push_back(i);
	}
	while (!myvector.empty()) {
		sum += myvector.back();
		myvector.pop_back();
	}
	while (!stdvector.empty()) {
		stdsum += stdvector.back();
		stdvector.pop_back();
	}
	EXPECT_EQ(stdsum, sum);
	displayStatus("Empty");
}

void Capacity_TEST(void) {
	ft::vector<int> myvector;
	std::vector<int> stdvector;

// set some content in the vector:
	for (int i = 0; i < 65; i++) {
		myvector.push_back(i);
		stdvector.push_back(i);
	}
	EXPECT_EQ(myvector.size(), stdvector.size());
	displayStatus("Capacity");
}

void Resize_TEST(void) {
	ft::vector<int> myvector;

// set some initial content:
	for (int i = 1; i < 10; i++)
		myvector.push_back(i);
	EXPECT_EQ(myvector.size(), size_t(9));
	myvector.resize(5);
	EXPECT_EQ(myvector.size(), size_t(5));
	myvector.resize(8, 100);
	EXPECT_EQ(myvector.size(), size_t(8));
	myvector.resize(12);
	EXPECT_EQ(myvector.size(), size_t(12));
	displayStatus("Resize");
}

void MaxSize_TEST(void) {
	ft::vector<int> myvector;
	std::vector<int> stdvector;
	EXPECT_EQ(myvector.max_size(), stdvector.max_size());
	ft::vector<double> myvector2;
	std::vector<double> stdvector2;
	EXPECT_EQ(myvector2.max_size(), stdvector2.max_size());
	ft::vector<char> myvector3;
	std::vector<char> stdvector3;
	EXPECT_EQ(myvector3.max_size(), stdvector3.max_size());
	displayStatus("MaxSize");
}

void Size_TEST(void) {
	ft::vector<int> myints;
	EXPECT_EQ(myints.size(), size_t(0));
	for (int i = 0; i < 10; i++)
		myints.push_back(i);
	EXPECT_EQ(myints.size(), size_t(10));
	myints.insert(myints.end(), 10, 100);
	EXPECT_EQ(myints.size(), size_t(20));
	myints.pop_back();
	EXPECT_EQ(myints.size(), size_t(19));
	displayStatus("Size");
}

void ReverseBegin_TEST(void) {
	ft::vector<int> myvector(5);  // 5 default-constructed ints

	int i = 0;
	ft::vector<int>::reverse_iterator rit = myvector.rbegin();
	for (; rit != myvector.rend(); ++rit)
		*rit = ++i;
	for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it) {
		EXPECT_EQ(*it, i--);
	}
	displayStatus("ReverseBegin");
}

void Begin_TEST(void) {
	ft::vector<int> myvector;
	for (int i = 1; i <= 5; i++)
		myvector.push_back(i);
	int i = 1;
	for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it) {
		EXPECT_EQ(*it, i++);
	}
	displayStatus("Begin");
}

void AssignOperator_TEST(void) {
	ft::vector<int> foo(3, 0);
	ft::vector<int> bar(5, 0);
	bar = foo;
	foo = ft::vector<int>();
	EXPECT_EQ(foo.size(), size_t(0));
	EXPECT_EQ(bar.size(), size_t(3));
	displayStatus("AssignOperator");
}

void Constructors_TEST(void) {
// constructors used in the same order as described above:
	ft::vector<int> first;                                                                        // empty vector of ints
	ft::vector<int> second(4, 100);                                               // four ints with value 100
	ft::vector<int> third(second.begin(), second.end() - 1);  // iterating through second
	ft::vector<int> fourth(third);                                                        // a copy of third

// the iterator constructor can also be used to construct from arrays:
	int myints[] = {16, 2, 77, 29, 5, 100};
	ft::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));
	EXPECT_EQ(first.size(), size_t(0));
	EXPECT_EQ(second.size(), size_t(4));
	EXPECT_EQ(third.size(), size_t(3));
	EXPECT_EQ(fourth.size(), size_t(3));
	EXPECT_EQ(fifth.size(), size_t(6));
	EXPECT_EQ(third[2], 100);
	EXPECT_EQ(fifth.front(), 16);
	EXPECT_EQ(fifth.back(), 100);
	displayStatus("Constructors");
}

void Stack_Operator_TEST(void) {
	i = 0;
	ft::vector<int> a;
	a.push_back(10);
	a.push_back(20);
	a.push_back(30);
	ft::stack<int, ft::vector<int> > foo(a);
	ft::stack<int, ft::vector<int> > bar(a);
	ft::stack<int, ft::vector<int> > bob;
	bob.push(30);
	bob.push(20);
	bob.push(10);
	bar.push(0);
	EXPECT_FALSE(bob == bar);
	EXPECT_TRUE(bar != foo);
	EXPECT_TRUE(bar != bob);
	EXPECT_FALSE(foo > bar);
	EXPECT_TRUE(foo < bar);
	EXPECT_FALSE(foo >= bar);
	EXPECT_TRUE(foo <= bar);
	displayStatus("Stack Operator 1");
}

void Stack_Operator2_TEST(void) {
	int array[5] = {0, 1, 2, 3, 4};
	ft::stack<int, ft::vector<int> > stack(ft::vector<int>(array, array + 5));
	ft::stack<int, ft::vector<int> > stack2(stack);
	EXPECT_EQ(stack, stack2);
	EXPECT_TRUE(stack >= stack2);
	EXPECT_TRUE(stack <= stack2);
	stack2.push(50);
	EXPECT_TRUE(stack != stack2);
	EXPECT_TRUE(stack < stack2);
	EXPECT_TRUE(stack <= stack2);
	EXPECT_TRUE(stack2 > stack);
	EXPECT_TRUE(stack2 >= stack);
	stack.push(200);
	EXPECT_TRUE(stack != stack2);
	EXPECT_TRUE(stack > stack2);
	EXPECT_TRUE(stack >= stack2);
	EXPECT_TRUE(stack2 < stack);
	EXPECT_TRUE(stack2 <= stack);
	displayStatus("Stack Operator 2");
}

void Pair_Constructor_TEST() {
	i = 0;
	ft::pair<int, int> pair;
	pair = ft::make_pair(15, 'a');
	EXPECT_EQ(pair.first, 15);
	EXPECT_EQ(pair.second, 97);
	ft::pair<std::string, double> pair2("hello test", 21.5);
	EXPECT_EQ(pair2.first, static_cast<std::string>("hello test"));
	EXPECT_EQ(pair2.second, 21.5);
	displayStatus("Pair Works With Make Pair And With Constructor");
}

void Pair_OperatorEqual_TEST() {
	ft::pair<std::string, int> planet, homeplanet;
	planet = ft::make_pair("Earth", 6371);
	homeplanet = planet;
	EXPECT_EQ(planet.first, static_cast<std::string>("Earth"));
	EXPECT_EQ(planet.second, 6371);
	EXPECT_EQ(homeplanet.first, static_cast<std::string>("Earth"));
	EXPECT_EQ(homeplanet.second, 6371);
	displayStatus("Operator Equal");
}

void Pair_Relational_Operator_TEST() {
	ft::pair<int, char> foo(10, 'z');
	ft::pair<int, char> bar(90, 'a');
	EXPECT_EQ((foo == bar), false);
	EXPECT_EQ((foo == foo), true);
	EXPECT_EQ((foo != foo), false);
	EXPECT_EQ((foo > bar), false);
	EXPECT_EQ((foo < bar), true);
	EXPECT_EQ((foo >= bar), false);
	EXPECT_EQ((foo <= bar), true);
	displayStatus("Relational Operator");
}

	bool fncomp(char lhs, char rhs) { return lhs < rhs; }

	struct classcomp {
		bool operator()(const char &lhs, const char &rhs) const { return lhs < rhs; }
	};

void	Constructor_TEST(){

	ft::map<char, int> first;

	first['a'] = 10;
	first['b'] = 30;
	first['c'] = 50;
	first['d'] = 70;

	ft::map<char, int> second(first.begin(), first.end());

	ft::map<char, int> third(second);

	ft::map<char, int, classcomp> fourth;

	bool (*fn_pt)(char, char) = fncomp;
	ft::map<char, int, bool (*)(char, char)> fifth(fn_pt);
	displayStatus("Constructor");
}

void	Begin_End_TEST() {
	ft::map<char, int> mymap;
	std::map<char, int> map;


	mymap['b'] = 100;
	mymap['a'] = 200;
	mymap['c'] = 300;
	map['b'] = 100;
	map['a'] = 200;
	map['c'] = 300;

	// show content:
	ft::map<char, int>::iterator it = mymap.begin();
	std::map<char, int>::iterator it2 = map.begin();
	for (int i = 0; i < 3; i++) {
		EXPECT_EQ(it->first, it2->first);
		EXPECT_EQ(it->second, it2->second);
		it++;
		it2++;
	}
	displayStatus("Begin and End");
}

void	RBegin_REnd_TEST() {
	ft::map<char, int> mymap;
	std::map<char, int> map;


	mymap['b'] = 100;
	mymap['a'] = 200;
	mymap['c'] = 300;
	map['b'] = 100;
	map['a'] = 200;
	map['c'] = 300;

	// show content:
	ft::map<char, int>::reverse_iterator rit = mymap.rbegin();
	std::map<char, int>::reverse_iterator rit2 = map.rbegin();
	for (int i = 0; i < 3; i++) {
		EXPECT_EQ(rit->first, rit2->first);
		EXPECT_EQ(rit->second, rit2->second);
		rit++;
		rit2++;
	}
	displayStatus("RBegin and REnd");
}

//void 	Empty_Map_TEST(void){
//	ft::map<char, int> mymap;
//	ft::map<char, int> mymap;
//
//
//	mymap['a'] = 10;
//	mymap['b'] = 20;
//	mymap['c'] = 30;
//
//	while (!mymap.empty()) {
//		std::cout << mymap.begin()->first << " => " << mymap.begin()->second << std::endl;
//		mymap.erase(mymap.begin());
//	}
//}




int main(void) {
	std::cout << BLACKC << "\n/// Vector Test Container ///\n";
	Constructor_Operator_TEST();
	Reverse_Iterator_TEST();
	Const_Rev_Iterator_TEST();
	ConstIterator_TEST();
	Glagan_TEST();
	IteratorOP1_TEST();
	IteratorOP2_TEST();
	IteratorOP3_TEST();
	RelationalOperators_TEST();
	Clear_TEST();
	Swap_TEST();
	Erase_TEST();
	Insert_TEST();
	InsertPos_TEST();
	InsertN_TEST();
	InsertRange_TEST();
	PopBack_TEST();
	PushBack_TEST();
	Assign_TEST();
	VFrontBack_TEST();
	At_TEST();
	BracketOperator_TEST();
	Reserve_TEST();
	Empty_TEST();
	Capacity_TEST();
	Resize_TEST();
	MaxSize_TEST();
	Size_TEST();
	ReverseBegin_TEST();
	Begin_TEST();
	AssignOperator_TEST();
	Constructors_TEST();

	std::cout << BLACKC << "\n/// Stack Test Container ///\n";
	Stack_Operator_TEST();
	Stack_Operator2_TEST();

	std::cout << BLACKC << "\n/// Map Test Container ///\n";
	Pair_Constructor_TEST();
	Pair_OperatorEqual_TEST();
	Pair_Relational_Operator_TEST();
	Constructors_TEST();
	Begin_End_TEST();
	RBegin_REnd_TEST();

	return (0);
}