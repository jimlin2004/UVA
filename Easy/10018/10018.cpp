#include <cstdio>

long long reverseInt(long long n)
{
    long long res = 0;
    while (n)
    {
        res = (res * 10) + n % 10;
        n  /= 10;
    }
    return res;
}

int main()
{
    int t;
    scanf("%d", &t);
    long long n;
    while (t--)
    {
        scanf("%lld", &n);
        long long reversedN;
        int count = 1;
        reversedN = reverseInt(n);
        n += reversedN;
        while (1)
        {
            reversedN = reverseInt(n);
            if (reversedN - n == 0)
            {
                printf("%d %lld\n", count, n);
                break;
            }
            else
                n += reversedN;
            ++count;
        }
    }
    return 0;
}