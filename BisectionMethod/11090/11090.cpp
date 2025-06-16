#include <bits/stdc++.h>
using namespace std;

/*

    要找到環有最小的mean weight
    方法是用二分搜
    將所有的邊 - mid
    如果有負環 -> mid太大
    沒有負環 -> mid太小

    這是因為假設一個環的mean是mid時
    環上所有權重 - mid總和為0

    負環用Floyd-Warshall判斷

*/


#define maxn 55

struct Edge
{
    int u, v;
    double w;
};

vector<Edge> edges;
double dis[maxn][maxn];
int n, m;

bool check(double mid)
{
    fill(&dis[0][0], &dis[0][0] + maxn * maxn, 1e12);

    for (int i = 1; i <= n; ++i)
        dis[i][i] = 0;

    for (Edge& edge: edges)
        dis[edge.u][edge.v] = min(dis[edge.u][edge.v], edge.w - mid);

    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (dis[i][k] + dis[k][j] < dis[i][j])
                {
                    dis[i][j] = dis[i][k] + dis[k][j];
                    if (i == j && dis[i][j] < 0)
                        return false; // 有負環，mid太大
                }
            }
        }
    }

    return true; // 沒有負環，mid太小
}

int main()
{
    int tc = 0;

    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d %d", &n, &m);

        edges.clear();
        for (int i = 0; i < m; ++i)
        {
            int u, v;
            double w;
            scanf("%d %d %lf", &u, &v, &w);
            edges.emplace_back(Edge{u, v, w});
        }

        double l = 0, r = 1e9;
        while (r - l > 1e-7)
        {
            double mid = (r + l) / 2;
            if (check(mid))
                l = mid;
            else
                r = mid;
        }

        printf("Case #%d: ", ++tc);
        if (l >= 1e9)
            puts("No cycle found.");
        else
            printf("%.2lf\n", l);
    }

    return 0;
}