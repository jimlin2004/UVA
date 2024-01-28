#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

//01背包多一維的題目

//dp[n][k]
int dp[1150][20];
vector<int> primes;
bool isNotPrime[1150];

int main()
{
    primes.emplace_back(0);
    isNotPrime[0] = isNotPrime[1] = true;
    for (int i = 2; i <= 1125; ++i)
    {
        if (!isNotPrime[i])
        {
            primes.emplace_back(i);
            for (int j = i * i; j <= 1125; j += i)
                isNotPrime[j] = true;
        }
    }

    for (int i = 1; i < primes.size(); ++i)
    {
        for (int j = 1120; j >= primes[i]; --j)
        {
            if (j == primes[i])
                dp[j][1] = 1;
            for (int k = 2; k <= 14; ++k)
            {
                dp[j][k] += dp[j - primes[i]][k - 1];
            }
        }
    }

    int n, k;
    while (scanf("%d %d", &n, &k) && n && k)
    {
        printf("%d\n", dp[n][k]);
    }
    return 0;
}