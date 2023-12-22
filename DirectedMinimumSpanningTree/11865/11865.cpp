#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

/*
    用bitsect method去二分搜lowestBandwidth
    再用朱劉算法去算算看每個edge.cap >= lowestBandwidth的情況下
    能不能找出Directed MST
    最後輸出題目給予的預算下最好的lowestBandwidth
*/

#define maxn 65
#define maxM 10005
#define INF 0x3f3f3f3f

struct Edge
{
    int u, v, cap, cost;
};

Edge originEdge[maxM];
Edge edges[maxM];

int in[maxn]; //in[i] -> i的indegree中目前選擇的
int pre[maxn]; //pre[v] = u -> v從u來的
int id[maxn]; //縮點後的編號
int vis[maxn];

//朱劉算法求directed MST
int Chu_Liu_Edmonds(int root, int n, int m, int lowestBandwidth)
{
    int res = 0;
    while (1)
    {
        //將所有in edge初始化為INF
        memset(in, 0x3f, sizeof(int) * n);
        //找出所有點的in edge
        for (int i = 0; i < m; ++i)
        {
            if (edges[i].u != edges[i].v && edges[i].cap >= lowestBandwidth && edges[i].cost < in[edges[i].v])
            {
                in[edges[i].v] = edges[i].cost;
                pre[edges[i].v] = edges[i].u;
            }
        }
        //除了root，若有點的in edge仍為INF，代表那個點走不到，MST就不存在
        for (int i = 0; i < n; ++i)
        {
            if (i == root)
                continue;
            if (in[i] == INF)
                return -1;
        }

        //縮點後的node數
        int newNodeNum = 0;
        memset(id, -1, sizeof(id));
        memset(vis, -1, sizeof(vis));
        in[root] = 0;
        //找出所有cycle
        for (int i = 0; i < n; ++i)
        {
            res += in[i];
            int v = i;
            //類似dfs去找cycle
            while (vis[v] != i && id[v] == -1 && v != root)
            {
                vis[v] = i;
                v = pre[v];
            }
            //cycle縮點
            if (v != root && id[v] == -1)
            {
                for (int j = pre[v]; j != v; j = pre[j])
                    id[j] = newNodeNum;
                id[v] = newNodeNum++;
            }
        }

        //newNodeNum == 0代表沒有cycle，朱劉完成
        if (newNodeNum == 0)
            break;

        //將沒有cycle的個別點給予新的id
        for (int i = 0; i < n; ++i)
            if (id[i] == -1)
                id[i] = newNodeNum++;

        //將edges中的edge更新成縮點後的圖上的邊
        for (int i = 0; i < m; ++i)
        {
            int u = edges[i].u;
            int v = edges[i].v;
            edges[i].u = id[u];
            edges[i].v = id[v];
            if (id[u] != id[v])
                edges[i].cost -= in[v];
        }

        n = newNodeNum;
        root = id[root];
    }

    return res;
}

int main()
{
    int t;
    int n, m, c;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d %d %d", &n, &m, &c);
        int maxCap = -1;
        for (int i = 0; i < m; ++i)
        {
            scanf("%d %d %d %d", &originEdge[i].u, &originEdge[i].v, &originEdge[i].cap, &originEdge[i].cost);
            maxCap = max(maxCap, originEdge[i].cap);  
        }
        int L = 0, R = maxCap, res = -1;
        //bitsect搜出最好的答案[L, R]
        while (L <= R)
        {
            int mid = (L + R) / 2;
            copy(originEdge, originEdge + m, edges);
            int temp = Chu_Liu_Edmonds(0, n, m, mid);
            if (temp == -1 || temp > c)
                R = mid - 1;
            else
            {
                L = mid + 1;
                res = mid;
            }
        }

        if (res == -1)
            printf("streaming not possible.\n");
        else
            printf("%d kbps\n", res);
    }
    return 0;
}