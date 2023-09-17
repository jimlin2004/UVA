#include <iostream>
#include <cmath>

int main()
{
    unsigned int n;
    while(scanf("%u", &n) != EOF)
    {
        if (n == 0) break;
        printf("%s\n", (((unsigned int)sqrt(n) * (unsigned int)sqrt(n)) == n) ? "yes" : "no");
    }
    return 0;
}