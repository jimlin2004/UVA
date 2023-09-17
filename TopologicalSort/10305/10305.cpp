#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
using namespace std;

vector<int> G[105];
bool hasInDeg[105];
bool visited[105];
stack<int> sk;

void dfs(int u)
{
    if (visited[u]) return;
    visited[u] = true;
    for (int v: G[u])
        dfs(v);
    sk.push(u);
}

int main()
{
    int m, n, u, v;

    while (scanf("%d %d", &n, &m) != EOF && (m || n))
    {
        fill(G, G + 105, vector<int>());
        memset(hasInDeg, false, sizeof(hasInDeg));
        memset(visited, false, sizeof(visited));
        while (m--)
        {
            scanf("%d %d", &u, &v);
            G[u].emplace_back(v);
            hasInDeg[v] = true;
        }
        for (int i = 1; i <= n; ++i)
        {
            if (!hasInDeg[i])
                dfs(i);
        }
        bool flag = false;
        while (!sk.empty())
        {
            if (flag) printf(" ");
            else flag = true;
            printf("%d", sk.top());
            sk.pop();
        }
        puts("");
    }
    return 0;
}