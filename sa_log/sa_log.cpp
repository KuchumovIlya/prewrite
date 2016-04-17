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

typedef long long int int64;

const int N = (int)1e6 + 1000;

int add(int a, int b, int m)
{
	a += b;
	return a < m ? a : a - m;
}

int str[N];
int tmp[5][N];
int cnt[N];
int lcp[N];
int revArr[N];
int *pos = tmp[0];
int *arr = tmp[1], *narr = tmp[2];
int *col = tmp[3], *ncol = tmp[4];

void buildSA(int n)
{
	int classes = 0;
	memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i < n; i++)
	{
		cnt[str[i]]++;
		classes = max(classes, str[i] + 1);	
	}
	pos[0] = 0;
	for (int i = 1; i < classes; i++)
		pos[i] = pos[i - 1] + cnt[i - 1];
	for (int i = 0; i < n; i++)
	{
		col[i] = str[i];
		arr[pos[col[i]]++] = i;
	}

	pos[0] = 0;
	for (int i = 1; i < classes; i++)
		pos[i] = pos[i - 1] + cnt[i - 1];

	for (int shift = 1; shift < n; shift *= 2)
	{
		for (int i = 0; i < n; i++)
		{
			int npos = arr[i] - shift;
			if (npos < 0)
				npos += n;
			narr[pos[col[npos]]++] = npos;
		}

		pos[0] = 0;
		ncol[narr[0]] = 0;
		for (int i = 1; i < n; i++)
		{
			ncol[narr[i]] = ncol[narr[i - 1]];
			if (col[narr[i]] != col[narr[i - 1]] || col[add(narr[i], shift, n)] != col[add(narr[i - 1], shift, n)])
				pos[++ncol[narr[i]]] = i;
		}

		swap(col, ncol);
		swap(arr, narr);

		if (col[arr[n - 1]] == n - 1)
			break;
	}
}

int main()
{
	freopen("input.txt", "r", stdin);

	int len;
	scanf("%d", &len);
	for (int i = 0; i < len; i++)
		scanf("%d", &str[i]);
	str[len++] = 0;
	buildSA(len);
	for (int i = 1; i < len; i++)
		printf("%d ", arr[i]);
	printf("\n");

	return 0;
}

