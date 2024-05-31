#include <cstdio>
#include <cmath>

#define Mod 100000007

int main()
{
    long long s;
    while (scanf("%lld", &s) != EOF && s)
    {
        bool hasOutput = false;
        
        long long bLim = sqrt(s / 6.0);
        for (long long b = 1; b < bLim; ++b)
        {
            if ((s - 6 * b * b) % (7 * b) == 0)
            {
                //mod 避免溢位
                long long a = (s - 6 * b * b) / (7 * b) % Mod;
                hasOutput = true;
                a *= a;
                //先mod避免溢位
                a %= Mod;
                printf("Possible Missing Soldiers = %lld\n", (a * 2) % Mod);
            }
        }

        if (!hasOutput)
            puts("No Solution Possible");
        puts("");
    }
    return 0;
}