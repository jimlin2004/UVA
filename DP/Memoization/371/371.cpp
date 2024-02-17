#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

//注: 題目騙人，題目的公式不是阿卡曼函式，實際為3n+1

//題目範圍到32bit，這邊只用dp優化到20bit
//注: 陷阱: 題目的32bit是unsigned int, int 會爆
const unsigned int dpLimit = 1 << 20;
//dp[n]是紀錄n去跑流程時到1的count
//注: dp[1]是終止條件，非實際count (dp[1] = 0, 但1去跑實際應為3)
unsigned int dp[dpLimit];

int solve(unsigned int n)
{
    if (n < dpLimit)
    {
        if (dp[n] != -1)
            return dp[n];
        if (n % 2 == 0)
            return dp[n] = solve(n / 2) + 1;
        else
            return dp[n] = solve(3 * n + 1) + 1;
    }
    if (n % 2 == 0)
            return solve(n / 2) + 1;
    else
        return solve(3 * n + 1) + 1;
}

int main()
{
    memset(dp, -1, sizeof(dp));
    dp[0] = dp[1] = 0;
    unsigned int a, b;
    unsigned int l, h;
    while (scanf("%d %d", &a, &b) && a && b)
    {   
        //a, b大小不一定
        l = min(a, b);
        h = max(a, b);

        unsigned int res = 0, maxCount = 0;
        unsigned int count;
        for (unsigned int i = l; i <= h; ++i)
        {
            //1要特別判斷，dp[1]是終止條件，非正確解答
            if (i == 1)
                count = 3;
            else
                count = solve(i);
            if (count > maxCount)
            {
                res = i;
                maxCount = count;
            }
        }
        printf("Between %d and %d, %d generates the longest sequence of %d values.\n", l, h, res, maxCount);
    }
    return 0;
}