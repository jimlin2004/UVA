#include <stdio.h>
#include <stdbool.h>

int main()
{
    int n;
    int f;
    int i;
    long long int area, animal, ef;
    long long int sum;
    scanf("%d", &n);
    while (n--)
    {
        sum = 0;
        scanf("%d", &f);
        for (i = 0; i < f; ++i)
        {
            scanf("%lld %lld %lld", &area, &animal, &ef);
            sum += area * ef;
        }
        printf("%lld\n", sum);
    }
    
    return 0;
}