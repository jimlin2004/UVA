#include <cstdio>
using namespace std;

//簡單Greedy

int eggs[35];

int main()
{
    int t;
    int Case = 0;
    scanf("%d", &t);
    while (t--)
    {
        int sum = 0;
        int res = 0;
        int n, p, q;
        scanf("%d %d %d", &n, &p, &q);
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &eggs[i]);
        }
        for (int i = 0; i < n; ++i)
        {
            if (sum + eggs[i] <= q && res < p)
            {
                sum += eggs[i];
                ++res;
            }
            else
                break;
        }
        printf("Case %d: %d\n", ++Case, res);
    }
    return 0;
}