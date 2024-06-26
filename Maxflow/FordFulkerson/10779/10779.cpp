#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

/*
概念:
    考maxFlow建模
    n是人數，m是貼紙種類
    將Bob訂為Node 0
    朋友訂為 1 ~ n - 1
    貼紙訂為 n ~ n + m - 1
    再訂終點t為 Node (n + m)

    視人到貼紙的邊代表可以供交換的
    貼紙到人代表那位沒有該貼紙所以可交換的
    再將貼紙建一個到終點t的邊(cap = 1)
    <注> 
        Bob希望有最多種貼紙，所有只要他有的貼紙都可以拿去換換看
        有沒有辦法越多種越好。
        其他朋友可以與Bob交換，但擁有的貼紙至少要留一張，
        否則沒理由要跟Bob換而犧牲自己
        且朋友只會想多換一張新的，如果已經交換到了就不會再考慮換到一樣的

    剩下就是maxFlow問題
    在此用Ford-Fulkerson(主要是邊的cap不大，最大也就20，因為貼紙最多20種)
*/

//最大節點數
const int maxn = 10 + 25 + 5; 
int s, t;
int n, m;
bool visited[maxn];
//G[u][v]存的是u到v這個edge的剩餘流量
int G[maxn][maxn];
//stickers[i][j] -> 第i位第j種sticker的數量(第0位是Bob)
int stickers[15][30];

int dfs(int u, int flow)
{
    if (u == t)
        return flow;
    visited[u] = true;
    int minFlow;
    for (int v = 0; v < maxn; ++v)
    {
        if (G[u][v] > 0 && !visited[v] && (minFlow = dfs(v, min(G[u][v], flow))) != -1)
        {
            G[u][v] -= minFlow;
            G[v][u] += minFlow;
            return minFlow;
        }
    }
    return -1;
}

int FF()
{
    int maxFlow = 0;
    int flow;
    while (flow = dfs(s, 0x3f3f3f3f) != -1)
    {
        memset(visited, 0, sizeof(visited));
        maxFlow += flow;
    }
    return maxFlow;
}

int main()
{
    int CaseN;
    scanf("%d", &CaseN);
    for (int Case = 1; Case <= CaseN; ++Case)
    {
        memset(G, 0, sizeof(G));
        memset(stickers, 0, sizeof(stickers));
        memset(visited, 0, sizeof(visited));
        scanf("%d %d", &n, &m);
        s = 0;
        t = n + m;
        for (int i = 0; i < n; ++i)
        {
            int num;
            scanf("%d", &num);
            int sticker;
            while (num--)
            {
                scanf("%d", &sticker);
                ++stickers[i][sticker];
            }
        }

        //Bob建圖(Bob可以不管有沒有剩下都拿去與別人交換，Bob只想要越多越好)
        for (int i = 1; i <= m; ++i)
        {
            if (stickers[0][i] > 0)
            {
                G[0][i + n - 1] = stickers[0][i];
            }
        }

        //其他人建圖(其他人要至少保留一張)
        for (int i = 1; i < n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                if (stickers[i][j] > 1)
                {
                    G[i][j + n - 1] = stickers[i][j] - 1;
                }
                if (stickers[i][j] == 0)
                {
                    G[j + n - 1][i] = 1;
                }
            }
        }

        //sticker節點與終點要有cap為1的邊
        for (int i = n; i < m + n; ++i)
        {
            G[i][t] = 1;
        }

        printf("Case #%d: %d\n", Case, FF());
    }
    return 0;
}