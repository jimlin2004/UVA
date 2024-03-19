#include <cstdio>

int qpow(int a, int b, int mod)
{
	int res = 1;
	while (b)
	{
		if (b & 1)
			res = ((res % mod) * (a % mod)) % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}

int main()
{
//	freopen("./input.txt", "r", stdin);
//	freopen("./out.txt", "w", stdout);
	int t;
	while (scanf("%d", &t) && t)
	{
		while (t--)
		{
			int x, y, n;
			scanf("%d %d %d", &x, &y, &n);
			printf("%d\n", qpow(x % n, y, n));
		}
	}
	return 0;
}