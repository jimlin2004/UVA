#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

#define maxn 505

struct Edge
{
    int u, v, w;
    Edge(int u, int v, int w)
        : u(u), v(v), w(w)
    {}
};

/*
    dp[u][k][b] = d是
    起點為u
    在子樹中共走了k個node
    b只有0 or 1代表是否回到u
    case 1.
        dp[u][k][0] = d代表從u點出發經過k個點後不回到u
        ，這樣的路徑最小總距離為d
    case 2.
        dp[u][k][1] = d代表從u點出發經過k個點後回到u
        ，這樣的路徑最小總距離為d
    
    轉移式分
    (以下v泛指u的child，w指的是u -> v的距離)
    case 1. 
        dp[u][j][1] = min(dp[u][j][1], dp[u][j - k][1] + dp[v][k][1] + 2w)
    case 2.
        dp[u][j][0] = min(dp[u][j][0], dp[u][j - k][1] + dp[v][k][0] + w)
    case 3.
        dp[u][j][0] = min(dp[u][j][0], dp[u][j - k][0] + dp[v][k][1] + 2w)
*/
int dp[maxn][maxn][2];
vector<vector<Edge>> G;
//subtreeSize[u]即以u為root的subtree有多大(包含)
int subtreeSize[maxn];
int n;

//重點
void dfs(int u, int p)
{
    //先求出subtreeSize[]
    subtreeSize[u] = 1;
    for (const Edge& edge: G[u])
    {
        if (edge.v == p)
            continue;
        dfs(edge.v, u);
        subtreeSize[u] += subtreeSize[edge.v];
    }

    //這兩個是邊界條件
    dp[u][1][0] = dp[u][1][1] = 0;
    
    for (const Edge& edge: G[u])
    {
        if (edge.v == p)
            continue;
        // 這裡倒著做的理由跟背包問題是一樣的
        for (int j = subtreeSize[u]; j > 1; --j)
        {
            for (int k = 1; k < j && k <= subtreeSize[edge.v]; ++k)
            {
                dp[u][j][1] = min(dp[u][j][1], dp[u][j - k][1] + dp[edge.v][k][1] + 2 * edge.w);
                dp[u][j][0] = min(dp[u][j][0], dp[u][j - k][1] + dp[edge.v][k][0] + edge.w);
                dp[u][j][0] = min(dp[u][j][0], dp[u][j - k][0] + dp[edge.v][k][1] + 2 * edge.w);
            }
        }
    }
}

int main()
{
    int Case = 0;
    while (scanf("%d", &n) != EOF && n)
    {
        memset(dp, 0x3f, sizeof(dp));
        G.assign(n + 5, vector<Edge>());

        int u, v, w;
        for (int i = 1; i < n; ++i)
        {
            scanf("%d %d %d", &v, &u, &w);
            G[u].emplace_back(u, v, w);
            G[v].emplace_back(v, u, w);
        }

        dfs(0, -1);

        int q;
        int x;
        scanf("%d", &q);
        printf("Case %d:\n", ++Case);
        while (q--)
        {
            scanf("%d", &x);
            //這裡可以二分搜
            for (int k = n; k >= 1; --k)
            {
                if (dp[0][k][0] <= x || dp[0][k][1] <= x)
                {
                    printf("%d\n", k);
                    break;
                }
            }
        }
    }
    return 0;
}