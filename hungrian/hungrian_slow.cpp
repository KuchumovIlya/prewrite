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

const int N = 2000;
const int INF = (int)1e8;

int n;
int a[N][N];
int u[N], v[N];

bool used_l[N], used_r[N];
int mt_l[N], mt_r[N];

bool dfs(int i)
{
	used_l[i] = true;

	for (int j = 0; j < n; j++)
	{
		if (u[i] + v[j] != a[i][j])
			continue;

		if (used_r[j])
			continue;

		used_r[j] = true;

		if (mt_r[j] == -1 || (!used_l[mt_r[j]] && dfs(mt_r[j])))
		{
			mt_l[i] = j;
			mt_r[j] = i;
			return true;
		}
	}

	return false;
}

int main()
{
#ifdef LOCAL
	freopen ("input.txt", "r", stdin);
#endif

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &a[i][j]);
		}
	}

	fill(mt_l, mt_l + n, -1);
	fill(mt_r, mt_r + n, -1);
	int mt_size = 0;

	fill(u, u + n, INF);
	fill(v, v + n, INF);

	int it = 0;

	while (true)
	{
		it++;
		
		fill(used_l, used_l + n, false);
		fill(used_r, used_r + n, false);

		for (int i = 0; i < n; i++)
		{
			if (mt_l[i] != -1)
				continue;

			if (used_l[i])
				continue;

			if (dfs(i))
				mt_size++;
		}

		if (mt_size == n)
			break;
		
		int delta = -INF;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (used_l[i] && !used_r[j])
					delta = min(delta, -a[i][j] + u[i] + v[j]);
		
		for (int i = 0; i < n; i++)
			if (used_l[i])
			{
				u[i] -= delta;
			}

		for (int j = 0; j < n; j++)
			if (used_r[j])
			{
				v[j] += delta;
			}
	}
	
	int ans = 0;

	for (int i = 0; i < n; i++)
		ans += u[i];
	
	for (int j = 0; j < n; j++)
		ans += v[j];

	printf("%d\n", ans);

	return 0;
}
