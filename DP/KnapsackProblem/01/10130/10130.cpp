#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int N;
int G;
int p[1005];
int w[1005];
int dp[31];

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		memset(p, 0, sizeof(p));
		memset(w, 0, sizeof(w));
		memset(dp, 0, sizeof(dp));
		
		scanf("%d", &N);
		for (int i = 0; i < N; ++i)
		{
			scanf("%d %d", &p[i], &w[i]);
		}
		
		//dp 0 1 knapsack
		for (int i = 0; i < N; ++i)
		{
			for (int remainW = 31 - 1; remainW >= w[i]; --remainW)
			{
				dp[remainW] = max(dp[remainW], dp[remainW - w[i]] + p[i]);
			}
		}
		
		int maxW;
		int res = 0;
		
		scanf("%d", &G);
		for (int i = 0; i < G; ++i)
		{
			scanf("%d", &maxW);
			res += dp[maxW];
		}
		printf("%d\n", res);
	}
	return 0;
}