#include <stdio.h>
#include <math.h>

#define max(a, b) ((a > b) ? a : b)

int f(int n)
{
    int len = 0;
    while (n != 1)
    {
        if (n & 1)
            n = 3 * n + 1;
        else
            n /= 2;
        len++;
    }
    return ++len; // 包含 n == 1
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}

int main()
{
    int a, b, res;
    while (scanf("%d %d", &a, &b) != EOF)
    {
        res = 0;
        printf("%d %d ", a, b);
        if (a > b)
            swap(&a, &b);
        for (int i = a; i <= b; i++)
        {
            res = max(res, f(i));
        }
        printf("%d\n", res);
    }
    return 0;
}