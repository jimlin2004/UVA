#include <cstdio>
#include <cstring>

/*
很簡單，只要二進制轉10進制再看兩數是否互質
*/

char str1[35];
char str2[35];

int gcd(int a, int b)
{
	if (a == 0)
		return b;
	return gcd(b % a, a);
}

int main()
{
	int t;
	scanf("%d", &t);
	int Case = 0;
	while (t--)
	{
		scanf("%s", str1);
		scanf("%s", str2);
		int n1 = 0;
		int n2 = 0;
		int base = 1;
		for (int i = strlen(str1) - 1; i >= 0; --i)
		{
			n1 += (str1[i] - '0') * base;
			base <<= 1;
		}
		base = 1;
		for (int i = strlen(str2) - 1; i >= 0; --i)
		{
			n2 += (str2[i] - '0') * base;
			base <<= 1;
		}
		
		printf("Pair #%d: ", ++Case);
		puts((gcd(n1, n2) == 1) ? "Love is not all you need!" : "All you need is love!");
	}
	return 0;
}