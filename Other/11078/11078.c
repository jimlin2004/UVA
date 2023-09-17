#include <stdio.h>
#define max(a, b) (a > b) ? a : b

int main()
{
    int ans, Max, Case, n, temp;
    scanf("%d", &Case);
    while (Case--)
    {
        scanf("%d", &n);
        scanf("%d", &Max);
        scanf("%d", &temp);
        ans = Max - temp;
        Max = max(Max, temp);
        for (int i = 2; i < n; i++)
        {
            scanf("%d", &temp);
            ans = max(ans, Max - temp);
            Max = max(Max, temp);
        }
        printf("%d\n", ans);
    }
    return 0;
}