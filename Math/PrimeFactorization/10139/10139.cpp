#include <bits/stdc++.h>
using namespace std;

#define maxp 100005

bool isNotPrime[maxp];
vector<long long> primes;

// 勒讓德公式
// 概念是在n! = 1 x 2 x 3 x .. x n裡
// p貢獻了n / p個人
// p ^ 2貢獻了 n / p ^ 2個人
// 以此類推
int count_p_in_factorial(long long n, long long p)
{
    int cnt = 0;
    long long power = p;
    while (power <= n)
    {
        cnt += n / power;
        power *= p;
    }

    return cnt;
}

int main()
{
    isNotPrime[0] = isNotPrime[1] = true;
    for (long long i = 2; i < maxp; ++i)
    {
        if (!isNotPrime[i])
        {
            primes.emplace_back(i);
            for (long long j = i * i; j < maxp; j += i)
            {
                isNotPrime[j] = true;
            }
        }
    }

    long long n, m;
    while (scanf("%lld %lld", &n, &m) != EOF)
    {
        bool ok = true;

        long long curr = m;

        for (long long p: primes)
        {
            if (curr < p * p)
                break;
            if (curr % p == 0)
            {
                int cnt = 0;
                while (curr % p == 0)
                {
                    curr /= p;
                    ++cnt;
                }

                if (count_p_in_factorial(n, p) < cnt)
                {
                    ok = false;
                    break;
                }
            }
        }

        if (curr > 1)
        {
            // curr是超大質數
            if (count_p_in_factorial(n, curr) < 1)
            {
                ok = false;
            }
        }

        if (ok)
            printf("%lld divides %lld!\n", m, n);
        else
            printf("%lld does not divide %lld!\n", m, n);
    }

    return 0;
}