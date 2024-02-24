#include <cstdio>

//直接模擬

int main()
{
    int n, k;
    while (scanf("%d %d", &n, &k) != EOF)
    {
        int res = 0;
        while (n >= k)
        {
            int newCigarettes = n / k;
            n %= k;
            n += newCigarettes;
            res += newCigarettes * k;
        }
        res += n;
        printf("%d\n", res);
    }
    return 0;
}