#include <cstdio>
#include <vector>
using namespace std;
#define maxn 60005

vector<int> primes;
bool isNotPrime[maxn];

int factCount;
int fact[maxn];
int expo[maxn];
vector<int> divisors;

void primeFactorization(int n)
{
    factCount = 0;
    for (int p: primes)
    {
        if (p > n)
            return;
        if (n % p == 0)
        {
            int count = 0;
            fact[factCount] = p;
            expo[factCount] = 0;
            while (n % p == 0)
            {
                ++expo[factCount];
                n /= p;
            }
            ++factCount;
        }
    }
}

void dfs(int x, int index, int n)
{
    //題目不要n本身
    if (index == factCount)
    {
        if (x != n)
            divisors.emplace_back(x);
        return;
    }
    dfs(x, index + 1, n);
    for (int i = 0; i < expo[index]; ++i)
    {
        x *= fact[index];
        dfs(x, index + 1, n);
    }
}

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

    puts("PERFECTION OUTPUT");

    int n;
    while (scanf("%d", &n) && n)
    {
        primeFactorization(n);
        divisors.clear();
        dfs(1, 0, n);

        int sum = 0;
        for (int d: divisors)
            sum += d;

        printf("%5d  ", n);
        if (sum == n)
            printf("PERFECT\n");
        else if (sum < n)
            printf("DEFICIENT\n");
        else
            printf("ABUNDANT\n");
    }

    puts("END OF OUTPUT");
    return 0;
}