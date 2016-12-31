#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <cmath>
#include <ctime>
#include <functional>
#include <sstream>
#include <fstream>
#include <valarray>
#include <complex>
#include <queue>
#include <cassert>
#include <bitset>
using namespace std;

#ifdef LOCAL
#define debug_flag 1
#else
#define debug_flag 0
#endif

	template <class T1, class T2 >
std::ostream& operator << (std::ostream& os, const pair<T1, T2> &p) 
{
	os << "[" << p.first << ", " << p.second << "]";
	return os;
}

	template <class T >
std::ostream& operator << (std::ostream& os, const std::vector<T>& v) 
{
	os << "[";
	bool first = true;
	for (typename std::vector<T>::const_iterator it = v.begin(); it != v.end(); ++it)
	{
		if (!first)
			os << ", ";
		first = false;
		os << *it;
	}
	os << "]";
	return os;
}

#define dbg(args...) { if (debug_flag) { _print(_split(#args, ',').begin(), args); cerr << endl; } else { void(0);} }

vector<string> _split(const string& s, char c) {
	vector<string> v;
	stringstream ss(s);
	string x;
	while (getline(ss, x, c))
		v.emplace_back(x);
	return v;
}

void _print(vector<string>::iterator) {}
template<typename T, typename... Args>
void _print(vector<string>::iterator it, T a, Args... args) {
	string name = it -> substr((*it)[0] == ' ', it -> length());
	if (isalpha(name[0]))
		cerr << name  << " = " << a << " ";
	else
		cerr << name << " ";
	_print(++it, args...);
}

typedef long long int int64;
typedef long double ldouble;

const ldouble EPS = 1e-9;
const ldouble ldouble_INF = 1e20;
const ldouble PI = acosl(-1.0);

bool eq(ldouble a, ldouble b)
{
	return fabsl(a - b) < EPS;
}

bool ls(ldouble a, ldouble b)
{
	return a < b && !eq(a, b);
}

bool gr(ldouble a, ldouble b)
{
	return a > b && !eq(a, b);
}

bool ls_eq(ldouble a, ldouble b)
{
	return a < b || eq(a, b);
}

bool gr_eq(ldouble a, ldouble b)
{
	return a > b || eq(a, b);
}

ldouble sqr(ldouble a)
{
	return a * a;
}

ldouble safe_sqrt(ldouble a)
{
	assert(gr_eq(a, 0));
	if (a < 0)
		return 0;
	return sqrtl(a);
}

struct Point
{
	int64 x, y;

	Point() : x(), y() {}
	Point(int64 _x, int64 _y) : x(_x), y(_y) {}

	void scan()
	{
		scanf("%lld%lld", &x, &y);
	}

	Point operator + (const Point &p) const
	{
		return Point(x + p.x, y + p.y);
	}

	Point operator - (const Point &p) const
	{
		return Point(x - p.x, y - p.y);
	}

	Point operator * (const int64 &k) const
	{
		return Point(x * k, y * k);
	}

	int64 operator % (const Point &p) const
	{
		return x * p.x + y * p.y;
	}

	int64 length2() const
	{
		return *this % *this;
	}

	ldouble length() const
	{
		return safe_sqrt(length2());
	}

	ldouble dist_to(const Point &p) const
	{
		return (*this - p).length();
	}

	int64 operator * (const Point &p) const
	{
		return x * p.y - y * p.x;
	}

	ldouble dist_to_seg(const Point &A, const Point &B) const
	{
		Point C = *this;
		if ((C - A) % (B - A) < 0)
			return C.dist_to(A);
		if ((C - B) % (A - B) < 0)
			return C.dist_to(B);
		return (A - C) * (B - C) / A.dist_to(B);
	}
};

std::ostream& operator << (std::ostream& os, const Point &p) 
{
	os << "(" << p.x << ", " << p.y << ")";
	return os;
}

bool cmp_by_cords(const Point &A, const Point &B)
{
	if (A.y != B.y)
		return A.y < B.y;
	return A.x < B.x;
}

vector<Point> get_minkowski_sum(const vector<Point> &list1, const vector<Point> &list2)
{
	//list1 and list2 are sorted by angle with positive direction
	int start1 = min_element(list1.begin(), list1.end(), cmp_by_cords) - list1.begin();
	int start2 = min_element(list2.begin(), list2.end(), cmp_by_cords) - list2.begin();

	dbg(list1, list2);
	dbg(start1, start2);

	int ptr1 = 0;
	int ptr2 = 0;

	int n = (int)list1.size();
	int m = (int)list2.size();

	vector<Point> res;
	res.reserve(n + m);

	while (ptr1 < n || ptr2 < m)
	{
		Point A = list1[(start1 + ptr1) % (int)list1.size()];
		Point B = list1[(start1 + ptr1 + 1) % (int)list1.size()];

		Point C = list2[(start2 + ptr2) % (int)list2.size()];
		Point D = list2[(start2 + ptr2 + 1) % (int)list2.size()];

		res.push_back(A + C);

		dbg(ptr1, ptr2, res.back());

		Point v1 = B - A;
		Point v2 = D - C;

		int64 mul = v1 * v2;

		if (mul > 0)
			ptr1++;
		else if (mul < 0)
			ptr2++;
		else
		{
			ptr1++;
			ptr2++;
		}
	}

	return res;
}

int main()
{
#ifdef LOCAL
	freopen ("input.txt", "r", stdin);
#endif

	return 0;
}
