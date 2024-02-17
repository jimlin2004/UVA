#include <cstdio>

int height[55];

int main()
{
    int n;
    int Case = 0;
    while (scanf("%d", &n) && n)
    {
        int total = 0;
        int avg;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &height[i]);
            total += height[i];
        }
        avg = total / n;
        int res = 0;
        for (int i = 0; i < n; ++i)
        {
            if (height[i] > avg)
                res += (height[i] - avg);
        }
        printf("Set #%d\nThe minimum number of moves is %d.\n\n", ++Case, res);
    }
    return 0;
}