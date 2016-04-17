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
	#define debug_flag true
#else
	#define debug_flag false
#endif

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

#ifdef LOCAL
    #define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
    #define eprintf(...) 42;
#endif

typedef long long int int64;

int slow(string s)
{
	set<string> ss;
	for (int i = 0; i < (int)s.length(); i++)
		for (int j = i; j < (int)s.length(); j++)
			ss.insert(s.substr(i, j - i + 1));
	return (int)ss.size();
}

const int mod = 1e9 + 7;
const int p1 = 31;
const int p2 = 239;
const int K = 2;
const int N = (int)1e5;

int pow_p[K][N];

int add(int a, int b)
{
	int64 res = a + b;
	if (res >= mod)
		res -= mod;
	return res;
}

int sub(int a, int b)
{
	int64 res = a - b;
	if (res < 0)
		res += mod;
	return res;
}

int mul(int a, int b)
{
	return (int64)a * b % mod;
}

void init_hash()
{
	pow_p[0][0] = pow_p[1][0] = 1;
	pow_p[0][1] = p1;
	pow_p[1][1] = p2;
	for (int k = 0; k < K; k++)
		for (int i = 2; i < N; i++)
			pow_p[k][i] = mul(pow_p[k][i - 1], pow_p[k][1]);
}

struct Hash
{
	int h1, h2;

	Hash()
	{
		h1 = h2 = 0;
	}

	Hash(char c)
	{
		h1 = h2 = (int)(c - 'a' + 1);
	}

	Hash(int _h1, int _h2) : h1(_h1), h2(_h2) {}

	bool operator == (const Hash &other) const
	{
		return h1 == other.h1 && h2 == other.h2;
	}

	bool operator < (const Hash &other) const
	{
		if (h1 != other.h1)
			return h1 < other.h1;
		return h2 < other.h2;
	}

	Hash operator + (const Hash &other) const
	{
		return Hash(add(h1, other.h1), add(h2, other.h2));
	}

	Hash operator - (const Hash &other) const
	{
		return Hash(sub(h1, other.h1), sub(h2, other.h2));
	}

	Hash up(int deg) const
	{
		int new_h1 = mul(h1, pow_p[0][deg]);
		int new_h2 = mul(h2, pow_p[1][deg]);
		return Hash(new_h1, new_h2);
	}
};

Hash get_h(Hash pref_sum[], int l, int r, int n)
{
	Hash res = pref_sum[r];
	if (l != 0)
		res = res - pref_sum[l - 1];
	return res.up(n - 1 - l);
}

int main()
{
#ifdef LOCAL
	freopen ("input.txt", "r", stdin);
#endif

	init_hash();

	string s = "abacaba";
	int n = (int)s.length();

	Hash pref_sum[N];
	for (int i = 0; i < n; i++)
		pref_sum[i] = Hash(s[i]).up(i); 
	for (int i = 1; i < n; i++)
		pref_sum[i] = pref_sum[i - 1] + pref_sum[i];
	
	set<Hash> all_hash;
	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++)
			all_hash.insert(get_h(pref_sum, i, j, n));


	int slow_ans = slow(s);
	int ans = (int)all_hash.size();
	assert(slow_ans == ans);

	return 0;
}
