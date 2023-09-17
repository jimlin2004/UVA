#include <stdio.h>

int main()
{
    long int a, b, res;
    while (scanf("%ld %ld", &a, &b) != EOF)
    {
        res = b - a;
        if (res >= 0)
            printf("%ld\n", res);
        else
        {
            res *= -1;
            printf("%ld\n", res);
        }
    }
    return 0;
}