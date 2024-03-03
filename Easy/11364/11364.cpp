#include <cstdio>
using namespace std;

#define max(a, b) ((a < b) ? b : a)
#define min(a, b) ((a < b) ? a : b)

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n, maxPos = -1, minPos = 0x3f3f3f3f;
        int pos;
        scanf("%d", &n);
        while (n--)
        {
            scanf("%d", &pos);
            maxPos = max(maxPos, pos);
            minPos = min(minPos, pos);
        }
        printf("%d\n", (maxPos - minPos) * 2);
    }
    return 0;
}