#include <cstdio>

#define maxn 10005

//為fact[i]中保留最後不是0的8位數
//留8位是為了避免乘上數字後出現多個尾數0的情況
long long dp[maxn] = {1, 1};

int main()
{
    long long product;
    for (int i = 2; i < maxn; ++i)
    {
        product = dp[i - 1] * i;
        while (product % 10 == 0)
            product /= 10;
        dp[i] = (product % 100000000);
    }
    int n;
    while (scanf("%d", &n) != EOF)
    {
        printf("%5d -> %d\n", n, dp[n] % 10);
    }
    return 0;
}