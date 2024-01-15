#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

// (a + b) % k = [(a % k) + (b % k)] % k

int n, k;
int nums[10005];
//dp[i][j] -> 利用前i個數字能不能加減出餘數為j
//轉移式在底下(O(n * k))
bool dp[10005][105];

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d %d", &n, &k);
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &nums[i]);
        }

        memset(dp, false, sizeof(dp));
        //邊界條件
        dp[0][0] = true;

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < k; ++j)
            {
                if (dp[i][j])
                {
                    //轉移式
                    //+k為了避免負值
                    dp[i + 1][(j + k + (abs(nums[i]) % k)) % k] = true;
                    dp[i + 1][(j + k - (abs(nums[i]) % k)) % k] = true;
                }
            }
        }

        printf("%s\n", (dp[n][0]) ? "Divisible" : "Not divisible");
    }
    return 0;
}