#include <cstdio>
#include <cstring>
using namespace std;

//題目沒講N的上限，網路上說測試後N = 1500是夠的
//0 / 1背包，在加上打印選擇

#define maxn 1505

int dp[maxn];
bool used[25][maxn];
int weights[25];

void print(int remain, int index)
{
    if (index < 0)
        return;

    for (int i = index; i >= 0; --i)
    {
        if (used[i][remain])
        {
            print(remain - weights[i], i - 1);
            printf("%d ", weights[i]);
            return;
        }
    }
}

int main()
{
    int target, n;
    while (scanf("%d %d", &target, &n) != EOF)
    {
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &weights[i]);
        }

        memset(dp, 0, sizeof(dp));
        memset(used, false, sizeof(used));

        for (int i = 0; i < n; ++i)
        {
            for (int remain = target; remain >= weights[i]; --remain)
            {
                if (dp[remain] <= dp[remain - weights[i]] + weights[i])
                {
                    dp[remain] = dp[remain - weights[i]] + weights[i];
                    used[i][remain] = true;
                }
            }
        }

        print(target, n - 1);

        printf("sum:%d\n", dp[target]);
    }
    return 0;
}