#include <cstdio>

//會溢位，只好py

unsigned long long fib[5005];

int main()
{
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i < 5005; ++i)
        fib[i] = fib[i - 1] + fib[i - 2];
    
    int n;
    while (scanf("%d", &n) != EOF)
    {
        printf("The Fibonacci number for %d is %llu\n", n, fib[n]);
    }
    return 0;
}