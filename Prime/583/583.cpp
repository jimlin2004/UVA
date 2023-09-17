#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 47000 // sqrt(2^31) = 46,340...

bool isPrime[MAXN];
int prime[MAXN];
int primeSize = 0;

void getPrimes() // 歐拉篩O(n)
{
    memset(isPrime, true, sizeof(isPrime));
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i < MAXN; i++)
    {
        if (isPrime[i])
            prime[primeSize++] = i;
        for (int j = 0; j < primeSize && i * prime[j] <= MAXN; ++j)
        {
            isPrime[i * prime[j]] = false;
            if (i % prime[j] == 0) break;
        }
    }
}

int main()
{
    long long n;
    bool flag;
    getPrimes();
    while (scanf("%lld", &n) != EOF && n)
    {
        flag = false;
        printf("%lld = ", n);
        if (n < 0)
        {
            printf("-1");
            n *= -1;
            flag = true;
        }
        for (int i = 0; i < primeSize && n > 1; ++i)
        {
            while (n % prime[i] == 0 && n > 1)
            {
                if (flag)
                {
                    printf(" x %d", prime[i]);
                }
                else
                {
                    printf("%d", prime[i]);
                    flag = true;
                }
                n /= prime[i];
            }
        }
        if (n != 1)
        {
            if (flag)
                printf(" x %lld", n);
            else
                printf("%lld", n);
        }
        printf("\n");
    }
    return 0;
}