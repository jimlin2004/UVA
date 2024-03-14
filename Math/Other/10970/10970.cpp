#include <cstdio>

/*
    簡單題，先對m行切成m條需要m - 1刀
    再對m條切n - 1刀分成n塊
    所以要(m - 1) + (m) * (n - 1)刀
*/

int main()
{
    int m, n;
    while (scanf("%d %d", &m, &n) != EOF)
    {
        printf("%d\n", (m - 1) + (m) * (n - 1));
    }
    return 0;
}