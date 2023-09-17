/*
第1500個數一定是1499-th*2 or 1499-th * 3 or 1499-th * 5
*/

#include <stdio.h>

#define min(a, b) (a < b) ? a : b

unsigned long long int N[1505] = {0};

int main()
{
    int n;
    int p2 = 1, p3 = 1, p5 = 1;
    N[1] = 1;
    for (n = 2; n <= 1500; ++n)
    {
        while (N[p2] * 2 <= N[n - 1]) ++p2;
        while (N[p3] * 3 <= N[n - 1]) ++p3;
        while (N[p5] * 5 <= N[n - 1]) ++p5;
        N[n] = min(N[p2] * 2, N[p3] * 3);
        N[n] = min(N[n], N[p5] * 5);
    }
    printf("The 1500'th ugly number is %llu.\n",N[1500]);
    return 0;
}