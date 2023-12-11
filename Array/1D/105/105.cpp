#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int height[10005];

int main()
{
    int maxr = -1;
    int l, r, h;
    while (scanf("%d %d %d", &l, &h, &r) != EOF)
    {
        for (int i = l; i < r; ++i)
        {
            height[i] = max(height[i], h);
            maxr = max(maxr, r);
        }
    }

    int prevh = 0;
    for (int i = 1; i < maxr; ++i)
    {
        if (height[i] != prevh)
        {
            printf("%d %d ", i, height[i]);
            prevh = height[i];
        }
    }
    printf("%d %d\n", maxr, 0);
    return 0;
}