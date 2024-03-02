#include <cstdio>
#include <vector>
using namespace std;

#define maxn 10000005

bool isNotPrime[maxn];
vector<int> primes;

void findPair(int n)
{
    int size = primes.size();
    for (int i = 0; i < size; ++i)
    {
        if (!isNotPrime[n - primes[i]])
        {
            printf("%d %d\n", primes[i], n - primes[i]);
            break;
        }
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
                isNotPrime[j] = true;
        }
    }

    int n;
    while (scanf("%d", &n) != EOF)
    {
        //小於8不可能
        if (n < 8)
        {
            printf("Impossible.\n");
            continue;
        }
        //如果n是偶數 -> 拆成2 + 2 + (N - 4)
        //如果n是奇數 -> 拆成2 + 3 + (N - 5)
        //再配合哥德巴赫猜想即可
        if (n % 2 == 0)
        {
            printf("2 2 ");
            findPair(n - 4);
        }
        else
        {
            printf("2 3 ");
            findPair(n - 5);
        }
    }
    return 0;
}