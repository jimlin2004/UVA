#include <cstdio>
#include <algorithm>
using namespace std;

/*
解題概念:
    1x1時，要考慮的是該格向上還是向左比較好
    到2x1時，要考慮的是向上好還是與[1][1]一起向左好
    1x2、2x2...同理，
    但是不能交叉
    所以我們可以先將y礦與b礦用類似prefixSum的思維預處理
    由於y[i][j]只能一路向左，b[i][j]只能一路向上
    所以經過prefixSum後，
    y[i][j]代表的是在[i][j]時一路向左加起來的y礦數量
    b[i][j]代表的是在[i][j]時一路向上加起來的b礦數量
    定義
    dp[i][j]代表是到[i][j]時能夠運出的最大礦物總和
    如果[i][j]這格運y礦，由於只能一路向左，
    所以state是dp[i - 1][j] + y[i][j] 
    -> 不能考慮dp[i][j - 1]，因為可能會有交叉的情況出現，
    同理，如果[i][j]這格運b礦，由於只能一路向上，
    所以state是dp[i][j - 1] + b[i][j]
    因此對於dp[i][j]，
    轉移式為dp[i][j] = max(dp[i - 1][j] + y[i][j], dp[i][j - 1] + b[i][j])
    最後答案在dp[n][m]
    O(N ^ 2)
*/

#define maxn 505

int dp[maxn][maxn];
int y[maxn][maxn];
int b[maxn][maxn];

int main()
{
    int n, m;
    while (scanf("%d %d", &n, &m) && (n != 0 && m != 0))
    {
        //讀y礦同時計算y礦從[i][j]的位置一路向左加起來的prefix sum
        int x;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                scanf("%d", &y[i][j]);
                y[i][j] += y[i][j - 1];
            }
        }

        //讀b礦同時計算b礦從[i][j]的位置一路向上加起來的prefix sum
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                scanf("%d", &b[i][j]);
                b[i][j] += b[i - 1][j];
            }
        }

        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                dp[i][j] = max(dp[i - 1][j] + y[i][j], dp[i][j - 1] + b[i][j]);
            }
        }
        printf("%d\n", dp[n][m]);
    }
    return 0;
}