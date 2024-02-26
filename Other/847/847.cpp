#include <cstdio>

/*
觀察
    2 <= n <= 9 -> Stan
    10 <= n <= 18 -> Ollie
    19 <= n <= 162 -> Stan
    ...
    一直*2 * 9檢查就知道誰贏了
    一點點博弈的狀態轉移味道
*/

int main()
{
    long long n;
    while (scanf("%lld", &n) != EOF)
    {
        long long p = 1;
        while (1)
        {
            p *= 9;
            if (p >= n)
            {
                puts("Stan wins.");
                break;
            }
            p *= 2;
            if (p >= n)
            {
                puts("Ollie wins.");
                break;
            }
        }
    }
    return 0;
}