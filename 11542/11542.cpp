#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> primes;
bool isNotPrime[505];
int A[505][505];
int maxP;

//埃氏篩
void getPrimes()
{
    isNotPrime[0] = isNotPrime[1] = true;
    for (int i = 2; i <= 500; ++i)
    {
        if (!isNotPrime[i])
        {
            primes.emplace_back(i);
            for (int j = i * i; j <= 500; j += i)
            {
                isNotPrime[j] = true;
            }
        }
    }
}

int main()
{
    getPrimes();
    int t;
    scanf("%d", &t);
    while (t--)
    {
        memset(A, 0, sizeof(A));
        int n;
        long long x;
        maxP = 0;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
        {
            scanf("%lld", &x);
            //質因數分解
            for (int j = 0; j < primes.size(); ++j)
            {
                while (x % primes[j] == 0)
                {
                    maxP = max(maxP, j);
                    x /= primes[j];
                    A[j][i] ^= 1;
                }
            }
        }
    }
    return 0;
}