#include <bits/stdc++.h>
using namespace std;

/*
    可以用來練習SCC縮點的題目
*/

#define maxn 100005

vector<vector<int>> G;
int visTime = 0;
int dfn[maxn];
int low[maxn];
stack<int> sk;
bool inStack[maxn];
int cntSCC = 0;
int scc[maxn]; // 縮點
int indegree[maxn]; // 這裡的是縮點後的編碼

void tarjan(int u)
{
    dfn[u] = low[u] = visTime++;
    sk.push(u);
    inStack[u] = true;

    for (int v: G[u])
    {
        if (dfn[v] == -1)
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (inStack[v])
            low[u] = min(low[u], dfn[v]);
    }

    if (low[u] == dfn[u])
    {
        int v;
        do
        {
            v = sk.top();
            sk.pop();
            inStack[v] = false;
            scc[v] = cntSCC;
        } while (v != u);
        ++cntSCC;
    }
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n, m;
        scanf("%d %d", &n, &m);

        G.assign(n + 5, {});
        visTime = 0;
        memset(dfn, -1, sizeof(dfn));
        memset(low, -1, sizeof(low));
        memset(scc, -1, sizeof(scc));
        memset(indegree, 0, sizeof(indegree));
        cntSCC = 0;

        for (int i = 0; i < m; ++i)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            G[u].push_back(v);
        }

        for (int u = 1; u <= n; ++u)
        {
            if (dfn[u] == -1)
                tarjan(u);
        }

        // 由SCC縮成DAG後，沒有入度的點就是必須要推的點
        int res = 0;
        for (int u = 1; u <= n; ++u)
        {
            for (int v: G[u])
            {
                if (scc[u] != scc[v])
                {
                    ++indegree[scc[v]];
                }
            }
        }

        for (int u = 0; u < cntSCC; ++u)
        {
            if (indegree[u] == 0)
                ++res;
        }

        printf("%d\n", res);
    }

    return 0;
}