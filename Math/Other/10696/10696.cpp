// #include <cstdio>
// #include <cstring>

// int dp[200];

// int solve(int n)
// {
//     if (n >= 101)
//         return n - 10;
    
//     if (dp[n] != -1)
//         return dp[n];
//     return dp[n] = solve(solve(n + 11));
// }

// int main()
// {
//     memset(dp, -1, sizeof(dp));
//     int n;
//     while (scanf("%d", &n) && n)
//     {
//         printf("f91(%d) = %d\n", n, solve(n));
//     }
//     return 0;
// }

//上面可以過
//但其實經過觀察與計算就會發現
//n <= 100最後都=91

//神奇的是
//上面dp用了0.080s
//底下卻用了0.120s

#include <cstdio>

int main()
{
    int n;
    while (scanf("%d", &n) && n)
    {
        if (n >= 101)
            printf("f91(%d) = %d\n", n, n - 10);
        else
            printf("f91(%d) = 91\n", n);
    }
    return 0;
}