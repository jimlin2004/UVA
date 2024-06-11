#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

/*
    最小費用最大流MCMF
    首先，建模
    
    參考 建模1.png
    這樣的建模比較容易想的到
    創一個源點s及終點t
    node 1 有邊指到t代表銷售
    node 1 有邊指到node 2代表month 1囤貨到month2
    node 2, node 3 ...一路建下去
    
    然而這樣的有個主要的問題是
    沒辦法分辨出
    如month 1囤貨到month 2再由month 2銷售出去的量
    以及month 2製造且month 2當月即銷售的量
    這兩種量的意義，cost不同
    所以需要換一種建法

    拆點(參考 建模2.png)
    node 1拆出一個node 1'
    node 2拆出一個node 2'
    node 3...
    node 1有邊連向node 1', node 2'...(根據題目的E_i決定連向多少個node)
    node 2...
    統一由node 1', node 2'...連向t代表每個月的銷售量
    但與 建模1.png不同的在於可以分辨出囤多少的貨到那些月份
    如 建模2.png中node 1 -> node 2' -> t即代表month 1囤貨到month 2且在month 2銷售

    邊上屬性(參考 建模3.png)
    首先，s到month 1, 2 ...的邊代表那個月的生產
    它們的屬性是<最多那個month能生產多少, 每單位生產成本>
    再者，month 1到month 1'的邊代表1月生產且在1月就銷售出去
    它們的屬性是<無限大, 0>，cost = 0是因為本來1月生產1月賣就沒有額外的限制及成本
    其他相似的邊邏輯一樣
    而如month 1 到 month 2'的邊代表1月囤貨到2月
    它們的屬性是<無限大, 每單位囤貨成本>，無限大是因為囤貨沒有上限
    其他相似的邊邏輯一樣
    最後如month 1'到t的邊代表1月的銷售量
    它們的屬性是<銷售上限, 每單位的售價>
    注意因為是MCMF，考慮的是最低成本，所以銷售一單位的錢假設為p
    對於成本的觀點來說是-p
    所以這些邊上的售價是負值
    其他相似的邊邏輯一樣

    最後只剩MCMF去跑一遍最後答案是-minCost，負號是因為當初銷售被視為-cost，
    所以最小的minCost是負數時代表實際上是賺了，
    也因此當MCMF跑的過程中是正數代表根本不賺還倒賠，要提早停掉加速運算

    MCMF: 
        基本上因為要求最小成本，所以maxFlow在流之前先用最短路徑算法求cost最小的路徑，
        並用那些路徑去找maxFlow，如此得到的maxFlow同時也會是minCost，
        在這題中cost會有負的，所以最短路只好用SPFA

    Node 編號規則:
        s = 0
        month 1, 2, ... , M就是1, 2, 3, ... , M
        month 1', 2', ..., M'是1 + M, 2 + M, 3 + M, ..., M + M
        t = M + M + 1
*/

#define maxn 225
#define INF 0x3f3f3f3f

struct Edge
{
    int u, v, cap, flow, cost;
};

//node size, edge size, source, target
int n, m, s, t;
vector<vector<int>> G;
vector<Edge> edges;
//SPFA用
bool inqueue[maxn];
//SPFA用的dis[]
long long dis[maxn];
//maxFlow一路扣回去時要知道parent
//<注> 在這題因為G[][]中存的是edgeIndex in edges[]
//     所以parent存的也是對應edges[]中的edgeIndex(主要是方便)
int parent[maxn];
//maxFlow時需要紀錄到node u時的bottleneck
//同時也代表著u該次流出去的量
long long outFlow[maxn];

void addEdge(int u, int v, int cap, int cost)
{
    edges.emplace_back(Edge{u, v, cap, 0, cost});
    edges.emplace_back(Edge{v, u, 0, 0, -cost});
    m = edges.size();
    G[u].emplace_back(m - 2);
    G[v].emplace_back(m - 1);
}

//一邊求最短路的同時一邊MaxFLow
bool SPFA(long long& maxFlow, long long& minCost)
{
    // memset(outFlow, 0x3f, sizeof(outFlow));
    memset(dis, 0x3f, sizeof(dis));
    memset(inqueue, false, sizeof(inqueue));

    queue<int> q;
    q.push(s);
    dis[s] = 0;
    inqueue[s] = true;
    outFlow[s] = INF;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        inqueue[u] = false;
        for (const int edgeIndex: G[u])
        {
            const Edge& edge = edges[edgeIndex];
            if ((edge.cap > edge.flow) && (dis[edge.v] > dis[u] + edge.cost))
            {
                dis[edge.v] = dis[u] + edge.cost;
                parent[edge.v] = edgeIndex;
                outFlow[edge.v] = min(outFlow[u], (long long)(edge.cap - edge.flow));
                if (!inqueue[edge.v])
                {
                    q.push(edge.v);
                    inqueue[edge.v] = true;
                }
            }
        }
    }

    //如果dis[t] > 0代表根本不賺還倒賠
    if (dis[t] > 0)
        return false;

    maxFlow += outFlow[t];
    minCost += dis[t] * outFlow[t];
    //一路更新回去這次最短路流完後要維護的MaxFlow演算法相關(如反向邊等)
    int curr = t;
    while (curr != s)
    {
        edges[parent[curr]].flow += outFlow[t];
        edges[parent[curr] ^ 1].flow -= outFlow[t];
        curr = edges[parent[curr]].u;
    }

    return true;
}

long long MCMF()
{
    long long maxFlow = 0;
    long long minCost = 0;
    while (SPFA(maxFlow, minCost))
        ;

    return minCost;
}

int main()
{
    int T;
    scanf("%d", &T);
    for (int Case = 1; Case <= T; ++Case)
    {
        //總共幾個月，囤貨成本
        int M, I;
        scanf("%d %d", &M, &I);
        //node size
        n = M + M + 2;

        G.assign(n + 5, vector<int>());
        edges.clear();

        s = 0;
        t = M + M + 1;

        for (int i = 1; i <= M; ++i)
        {
            int produceCost, produceMax, sellPrice, sellMax, inventoryMonth;
            scanf("%d %d %d %d %d", &produceCost, &produceMax, &sellPrice, &sellMax, &inventoryMonth);

            //s 到 month 1, 2, 3, ...
            addEdge(s, i, produceMax, produceCost);
            //month 1', 2', 3', ... 到 t
            addEdge(M + i, t, sellMax, -sellPrice);
            
            //同時建month 1 -> month 1', month 2 -> month 2', ...
            //以及month 1 -> month 2'代表1月囤貨到2月賣
            //month 1 -> month 3' 代表1月囤貨到3月賣...
            //取決於可以囤多久就有多少邊
            for (int j = 0; j <= inventoryMonth; ++j)
            {
                if (i + j <= M)
                    addEdge(i, M + i + j, INF, I * j);
            }
        }


        printf("Case %d: %lld\n", Case, -MCMF());
    }
    return 0;
}