#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

/*
    (配合例圖.png)
    考最大流建模
    題目提供每一行每一列的和
    想像有一個s(node 0)與t(node (r + c + 1))
    s流到每個R(列節點，node 1 ~ r)(cap = Rsum)，
    每個R node再流向每個C node((r + 1) ~ (r + c))(cap後面討論)
    每個C node再流向t(cap = Csum)

    如此當水流流過s到u(1 <= u <= r, 也就是R node)到v(r + 1 <= v <= r + c)再到t
    設流過flow的水量
    意義就好像在Matrix的mat[u][v]貢獻flow的值，
    所以最大流可以解決這題

    但題目說mat中的元素在[1, 20]之間
    但最大流必須要從0開始流
    所以做平移[1, 20] - 1到[0, 19]，相當於我們已經在mat的每個位置填上1
    因此上面推導的G中的cap要改

    首先，s流到每個R node的cap變成(cap = Rsum - c)
    因為假設R node是1 -> 對應mat中的第1列，由於mat必須先填上1
    所以mat[1][r + 1] ~ mat[1][r + c]先被填上1
    相當於水流從s到node 1到每個C node已經流過1了(對應mat中第1列都貢獻了1)
    C node共有c個，所以需要cap = Rsum - c

    每個C node流到t的cap也是同理，要改成(cap = Csum - r)

    再來每個R node到C node的flow自然被限制在[0, 19]，所以cap = 19

    最後mat[i][j]的答案在node i(R node)到node j(C node)那條Edge上的flow
    輸出時每個matrix元素記得加上最一開始的1即可

    最大流用Dinic
*/

#define maxn 55

struct Edge
{
    int u, v, cap, flow;
};

vector<Edge> edges;
//存的是對應edges的index
vector<vector<int>> G;
//mat[i][j]存的是對應edges[]的index，那條edge從i到j的flow + 1即為最後mat[i][j]的答案
int mat[maxn][maxn];
int d[maxn];
bool visited[maxn];
int s, t;
int cur[maxn];

void addEdge(int u, int v, int cap)
{
    edges.push_back(Edge{u, v, cap, 0});
    edges.push_back(Edge{v, u, 0, 0});
    int si = edges.size();
    G[u].emplace_back(si - 2);
    G[v].emplace_back(si - 1);
}

bool bfs()
{
    memset(visited, 0, sizeof(visited));
    queue<int> q;
    d[s] = 0;
    q.push(s);
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        visited[curr] = true;
        for (int index: G[curr])
        {
            Edge& edge = edges[index];
            if (edge.cap - edge.flow > 0)
            {
                if (!visited[edge.v])
                {
                    d[edge.v] = d[curr] + 1;
                    q.push(edge.v);
                }
            }
        }
    }
    return visited[t];
}

int dfs(int u, int flow)
{
    if (u == t)
        return flow;

    int outFlow;
    int totalFlow = 0;
    for (int& index = cur[u]; index < G[u].size(); ++index)
    {
        Edge& edge = edges[G[u][index]];
        if ((d[edge.v] == d[u] + 1) && (edge.cap - edge.flow > 0))
        {
            if ((outFlow = dfs(edge.v, min(flow, edge.cap - edge.flow))) > 0)
            {
                edges[G[u][index]].flow += outFlow;
                edges[G[u][index] ^ 1].flow -= outFlow;
                flow -= outFlow;
                totalFlow += outFlow;
                if (flow == 0)
                    break;
            }
        }
    }
    return totalFlow;
}

void dinic()
{
    int maxFlow = 0;
    while (bfs())
    {
        memset(cur, 0, sizeof(cur));
        maxFlow += dfs(s, 0x3f3f3f3f);
    }
    return;
}

int main()
{
    int Case = 0;
    int k;
    scanf("%d", &k);
    while (k--)
    {
        int r, c;
        scanf("%d %d", &r, &c);
        s = 0;
        t = r + c + 1;

        edges.clear();
        G.assign(r + c + 1 + 5, vector<int>());

        int prev = 0;
        int rsum = 0;
        for (int i = 1; i <= r; ++i)
        {
            scanf("%d", &rsum);
            addEdge(s, i, rsum - prev - c);
            prev = rsum;
        }

        prev = 0;
        int csum = 0;
        for (int i = r + 1; i <= r + c; ++i)
        {
            scanf("%d", &csum);
            addEdge(i, t, csum - prev - r);
            prev = csum;
        }

        for (int i = 1; i <= r; ++i)
        {
            for (int j = r + 1; j <= r + c; ++j)
            {
                addEdge(i, j, 19);
                mat[i][j - r] = edges.size() - 2;
            }
        }

        dinic();

        printf("Matrix %d\n", ++Case);

        for (int i = 1; i <= r; ++i)
        {
            printf("%d", edges[mat[i][1]].flow + 1);
            for (int j = 2; j <= c; ++j)
            {
                printf(" %d", edges[mat[i][j]].flow + 1);
            }
            puts("");
        }
        puts("");
    }
    return 0;
}