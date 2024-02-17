#include <cstdio>
#include <vector>
using namespace std;

#define maxn 1000005

bool isNotPrime[maxn] = {};
vector<int> primes;

int main()
{
    isNotPrime[0] = isNotPrime[1] = true;
    for (long long i = 2; i < maxn; ++i)
    {
        if (!isNotPrime[i])
        {
            primes.emplace_back(i);
            for (long long j = i * i; j < maxn; j += i)
            {
                isNotPrime[j] = true;
            }
        }
    }
    int n;
    int p1, p2;
    bool ok = false;
    while (scanf("%d", &n) && n)
    {
        for (int i = 0; i < primes.size(); ++i)
        {
            if (primes[i] < n)
            {
                p1 = primes[i];
                p2 = n - primes[i];
                if (p1 > p2)
                    break;
                if (!isNotPrime[p2])
                {
                    printf("%d = %d + %d\n", n, p1, p2);
                    ok = true;
                    break;
                }
            }
            else
                break;
        }
        if (!ok)
            puts("Goldbach's conjecture is wrong.\n");
    }
    return 0;
}