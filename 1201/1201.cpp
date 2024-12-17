#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

#define maxn 505

/*
    此題考的是DAG的最小path cover
    (路徑的點不重複，最少幾個路徑可以涵蓋所有的點)
    答案是會等於n(點數) - 二分圖最大匹配數
    原因大概跟 推導1.png 說明的有關
    在最大匹配中左邊的點對應到右邊點代表那條路徑的下一個點是誰
*/

struct Order
{
    int min, sx, sy, tx, ty;
    int dis;
};

Order orders[maxn];
vector<vector<int>> G;

// 曼哈頓距離
inline int getDis(int sx, int sy, int tx, int ty)
{
    return abs(tx - sx) + abs(ty - sy);
}

// 匈牙利演算法用
bool used[maxn];
int p[maxn];

// 匹配
bool match(int u)
{
    for (int v: G[u])
    {
        if (!used[v])
        {
            used[v] = true;
            if (p[v] == -1 || match(p[v]))
            {    
                p[v] = u;
                return true;
            }
        }
        
    }
    return false;
}

// 匈牙利演算法
int solve(int n)
{
    memset(p, -1, sizeof(p));
    int res = 0;
    for (int i = 0; i < n; ++i)
    {
        memset(used, 0, sizeof(used));
        if (match(i))
        {
            ++res;
        }
    }
    return res;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n;
        scanf("%d", &n);
        int h, m;
        for (int i = 0; i < n; ++i)
        {
            int& sx = orders[i].sx;
            int& sy = orders[i].sy;
            int& tx = orders[i].tx;
            int& ty = orders[i].ty;

            scanf("%d:%d %d %d %d %d", &h, &m, &sx, &sy, &tx, &ty);
            // 將時間統一轉成分鐘制
            orders[i].min = h * 60 + m;
            orders[i].dis = getDis(sx, sy, tx, ty);
        }

        G.assign(n + 5, vector<int>());

        // 建圖，可以來的及去載的就可以連一條單向邊
        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                int t = orders[i].dis + orders[i].min;
                // 記得要加上從上一次的終點到現在起點需要的時間
                t += getDis(orders[i].tx, orders[i].ty, orders[j].sx, orders[j].sy);
                if (t < orders[j].min)
                {
                    G[i].emplace_back(j);
                }
            }
        }

        printf("%d\n", n - solve(n));
    }
    return 0;
}

/*
2
2
08:00 10 11 9 16
08:07 9 16 10 11
2
08:00 10 11 9 16
08:06 9 16 10 11
*/