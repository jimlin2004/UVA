#include <iostream>
#include <cstring>
using namespace std;

/*
    簡單推格子算路徑數
    <注>: cin過，printf不知錯哪
*/

#define maxn 35

long long dp[maxn][maxn];
//disconnect[i][j][k] -> k == 0 -> W, k == 1 -> N不能走
int disconnect[maxn][maxn][2];

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        memset(dp, 0, sizeof(dp));
        memset(disconnect, 0, sizeof(disconnect));

        int n;
        cin >> n;
        int sx, sy, ex, ey;
        cin >> sx >> sy;
        cin >> ex >> ey;
        int m;
        cin >> m;
        int x, y;
        char D;
        for (int i = 0; i < m; ++i)
        {
            cin >> x >> y >> D;
            if (D == 'S')
            {
                disconnect[x][y - 1][1] = 1;
            }
            else if (D == 'W')
            {
                disconnect[x - 1][y][0] = 1;
            }
            else if (D == 'E')
            {
                disconnect[x][y][0] = 1;
            }
            else if (D == 'N')
            {
                disconnect[x][y][1] = 1;
            }
        }

        dp[sx][sy] = 1;

        for (int i = sx; i <= ex; ++i)
        {
            for (int j = sy; j <= ey; ++j)
            {
                if (!disconnect[i][j - 1][1])
                    dp[i][j] += dp[i][j - 1];
                if (!disconnect[i - 1][j][0])
                    dp[i][j] += dp[i - 1][j];
            }
        }

        cout << dp[ex][ey] << '\n';
    }
    return 0;
}