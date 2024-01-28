#include <cstdio>
#include <cstdlib>
using namespace std;

int nums[1005];

int main()
{
    int n, qNum, q;
    int Case = 1;
    while (scanf("%d", &n) && n)
    {
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &nums[i]);
        }
        int res = 0x3f3f3f3f;
        scanf("%d", &qNum);
        printf("Case %d:\n", Case++);
        while (qNum--)
        {
            scanf("%d", &q);
            for (int i = 0; i < n; ++i)
            {
                for (int j = i + 1; j < n; ++j)
                {
                    if (abs(nums[i] + nums[j] - q) < abs(res - q))
                        res = nums[i] + nums[j];
                }
            }
            printf("Closest sum to %d is %d.\n", q, res);
        }
    }
    return 0;
}