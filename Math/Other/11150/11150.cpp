#include <cstdio>

int main()
{
//	freopen("./input.txt", "r", stdin);
//	freopen("./out.txt", "w", stdout);
	int n;
	while (scanf("%d", &n) != EOF)
	{
		int res = 0;
		while (n >= 3)
		{
			int count = n / 3;
			n %= 3;
			res += count * 3;
			n += count;
		}
		if (n == 2)
			++n;
		res += n;
		printf("%d\n", res);
	}
	return 0;
}