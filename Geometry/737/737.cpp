#include <cstdio>
#include <algorithm>
using namespace std;

/*
    算三個軸的分別區間的重疊範圍
    再相乘即可
    如果乘積<0
    則輸出0
*/

int main()
{
    int n;
    while (scanf("%d", &n) && n)
    {
        int xmin = -0x3f3f3f3f, xmax = 0x3f3f3f3f;
        int ymin = -0x3f3f3f3f, ymax = 0x3f3f3f3f;
        int zmin = -0x3f3f3f3f, zmax = 0x3f3f3f3f;
        int x, y, z, l;
        while (n--)
        {
            scanf("%d %d %d %d", &x, &y, &z, &l);
            xmin = max(xmin, x);
            xmax = min(xmax, x + l);
            ymin = max(ymin, y);
            ymax = min(ymax, y + l);
            zmin = max(zmin, z);
            zmax = min(zmax, z + l);
        }
        int v = (xmax - xmin) * (ymax - ymin) * (zmax - zmin);
        printf("%d\n", (v > 0) ? v : 0);
    }
    return 0;
}