#include <cstdio>
#include <vector>
#include <cstdlib>
using namespace std;

/*
    核心概念:
        為了保證move次數最小
        我的子樹有缺的只能從我拿
        而我的子樹有多的也只能交給我
        以此用dfs紀錄moveNum
        每次把我的marbles變成1
        把我的父節點的marbles更新上我與我的子樹需要marbles(有正有負)
*/

struct Edge
{
    int u, v;
};

vector<vector<Edge>> G;
int marbles[10005];

int moveNum;

void dfs(int u, int p)
{
    for (Edge& edge: G[u])
    {
        if (edge.v == p)
            continue;
        dfs(edge.v, u);
    }
    //與1顆marble的差(有正有負)
    int marblesDiff = marbles[u] - 1;
    moveNum += abs(marblesDiff);
    marbles[u] = 1;
    marbles[p] += marblesDiff;
}

int main()
{
    int n;
    while (scanf("%d", &n) && n)
    {
        int v, d, numOfChild, child;
        bool needTosetRoot = true;
        int root;
        moveNum = 0;
        G.assign(n + 5, vector<Edge>());
        for (int i = 0; i < n; ++i)
        {
            scanf("%d %d %d", &v, &d, &numOfChild);
            if (needTosetRoot)
            {
                root = v;
                needTosetRoot = false;
            }
            marbles[v] = d;
            for (int j = 0; j < numOfChild; ++j)
            {
                scanf("%d", &child);
                G[v].emplace_back(Edge{v, child});
                G[child].emplace_back(Edge{child, v});
            }
        }
        dfs(root, -1);
        printf("%d\n", moveNum);
    }
    return 0;
}