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
using namespace std;

int main(int, char **argv)
{
	int seed = atoi(argv[1]);
	srand(seed);

	const int N = 2;
	const int X = 2;

	int n = rand() % N + 1;

	printf("%d\n", n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%d ", rand() % X - X / 2);
		printf("\n");
	}

	return 0;
}
