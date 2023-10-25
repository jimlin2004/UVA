#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

/*
核心概念:
    利用貪婪的想法
    對於距離server > k的client，由距離最遠的clients(假設一點為u)到距離為k + 1的點，找到u的前k個父節點
    並在其前k個父節點建立新的server，如此新的server能夠有更多機會覆蓋到更多的點，使需要新蓋的server數最少
*/

int n;
int server, k;

//parent[u] -> u從哪裡來的
int parent[1005];
vector<vector<int>> G;
//distances[d] -> 與server距離為d的節點們
vector<vector<int>> distances;
bool visited[1005];
int maxDis = -1;

//算出每一點與server的距離及它的parent
void dfs1(int u, int p, int dis)
{
    maxDis = max(maxDis, dis);
    //葉子->client
    if (G[u].size() == 1)
    {
        if (dis > k)
            distances[dis].push_back(u);
        return;
    }

    for (int v: G[u])
    {
        if (v == p)
            continue;
        parent[v] = u;
        dfs1(v, u, dis + 1);
    }
}

//將未覆蓋的點用新的server消除
void dfs2(int u, int p, int dis)
{
    if (dis >= k)
        return; //新的server到這一點距離>=k，就不能再往後覆蓋了
    for (int v: G[u])
    {
        if (v == p)
            continue;
        visited[v] = true;
        dfs2(v, u, dis + 1);
    }
}

void solve()
{
    dfs1(server, -1, 0);

    int res = 0;
    for (int dis = maxDis; dis > k ; --dis)
    {
        for (int v: distances[dis])
        {
            if (!visited[v])
            {
                visited[v] = true;
                int p = v;
                for (int step = 0; step < k; ++step)
                {
                    //找到距離server為k的祖先
                    p = parent[p];
                }
                visited[p] = true;
                ++res;
                dfs2(p, -1, 0);
            }
        }
    }

    printf("%d\n", res);
}


int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        scanf("%d %d", &server, &k);
        G.assign(n + 5, vector<int>());
        distances.assign(n + 5, vector<int>());
        memset(parent, -1, sizeof(parent));
        memset(visited, false, sizeof(visited));
        maxDis = -1;

        int u, v;
        for (int i = 0; i < n - 1; ++i)
        {
            scanf("%d %d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }

        solve();
    }
    return 0;
}