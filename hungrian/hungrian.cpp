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

const int N = 1000;
const int INF = (int)1e9;

int n;
int a[N][N];
int u[N], v[N], p[N], way[N];

int minv[N];
bool used[N];

int main()
{
#ifdef LOCAL
	freopen ("input.txt", "r", stdin);
#endif

	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			scanf("%d", &a[i][j]);
		}
	}

	int m = n;

	for (int i = 1; i <= n; i++)
	{
		p[0] = i;
		int j0 = 0;

		fill(minv, minv + m + 1, INF);
		fill(used, used + m + 1, false);

		do
		{
			used[j0] = true;
			int i0 = p[j0];
			int delta = INF;
			int j1 = 0;

			for (int j = 1; j <= m; j++)
			{
				if (!used[j])
				{
					int cur = a[i0][j] - u[i0] - v[j];
					
					if (cur < minv[j])
					{
						minv[j] = cur;
						way[j] = j0;
					}

					if (minv[j] < delta)
					{
						delta = minv[j];
						j1 = j;
					}
				}
			}

			for (int j = 0; j <= m; j++)
			{
				if (used[j])
				{
					u[p[j]] += delta;
					v[j] -= delta;
				}
				else
				{
					minv[j] -= delta;
				}
			}

			j0 = j1;

		} while (p[j0] != 0);

		do
		{
			int j1 = way[j0];
			p[j0] = p[j1];
			j0 = j1;
		} while (j0 != 0);
	}

	int ans = 0;
	for (int i = 1; i <= n; i++)
		ans += u[i];

	for (int j = 1; j <= n; j++)
		ans += v[j];

	//ans = -v[0];

	printf("%d\n", ans);

	return 0;
}
