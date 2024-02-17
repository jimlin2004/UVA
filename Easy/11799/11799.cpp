#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
    int t;
    scanf("%d", &t);
    int Case = 0;
    while (t--)
    {
        int n;
        int maxSpeed = -1;
        scanf("%d", &n);
        int speed;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &speed);
            maxSpeed = max(maxSpeed, speed);
        }
        printf("Case %d: %d\n", ++Case, maxSpeed);
    }
    return 0;
}