#include <cstdio>
#include <vector>
using namespace std;

#define maxn 20000005

bool isNotPrime[maxn];
vector<pair<int, int>> twinPrimes;

int main()
{
    isNotPrime[0] = isNotPrime[1] = true;
    for (long long i = 2; i < maxn; ++i)
    {
        if (!isNotPrime[i])
        {
            if (!isNotPrime[i - 2])
            {
                twinPrimes.push_back({i - 2, i});
            }
            for (long long j = i * i; j < maxn; j += i)
            {
                isNotPrime[j] = true;
            }
        }
    }

    int n;
    while (scanf("%d", &n) != EOF)
    {
        pair<int, int>& p = twinPrimes[n - 1];
        printf("(%d, %d)\n", p.first, p.second);
    }
    return 0;
}