#include <cstdio>
#include <vector>
using namespace std;

const int maxn = (1 << 15) + 5;
bool isNotPrime[maxn] = {};
vector<int> primes;

int main()
{
    isNotPrime[0] = isNotPrime[1] = true;
    for (int i = 2; i < maxn; ++i)
    {
        if (!isNotPrime[i])
        {
            primes.emplace_back(i);
            for (int j = i * i; j < maxn; j += i)
            {
                isNotPrime[j] = true;
            }
        }
    }

    int n;
    while (scanf("%d", &n) && n)
    {
        int count = 0;
        int p1, p2;
        for (int i = 0; i < primes.size(); ++i)
        {
            if (primes[i] >= n)
                break;
            p1 = primes[i];
            p2 = n - p1;
            if (p1 > p2)
                break;
            if (!isNotPrime[p2])
                ++count;
        }
        printf("%d\n", count);
    }
    return 0;
}