#include <cstdio>

/*
純數學題
    n = 1 -> 1等分 -> 等於沒切 球面積是4pi * r ^ 2
    n = 2 -> 2等分 -> 原本外面的表面積不變 + 剖面多出來的兩個圓 2 * pi * r^2 -> 多50%
    n = 3 -> 3等分 -> 用"補"的概念，那三等份中的一等分會多出2個半圓 -> 所以3等分多出3個圓 -> 3 * pi * r^2 -> 多75%
    ...以此類推
*/

int main()
{
    int n;
    while (scanf("%d", &n) && n > 0)
    {
        if (n == 1)
            puts("0%");
        else
            printf("%lld%\n", 25LL * n);
    }
    return 0;
}