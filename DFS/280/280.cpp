#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

vector<int> G[105];
bool visited[105];
int visitedNum;

void dfs(int u)
{
    for (int v: G[u])
    {
        if (!visited[v])
        {
            visited[v] = true; // 起點不算visited
            ++visitedNum;
            dfs(v);
        }
    }
}

int main()
{
    int n;
    int u, v;
    int len;
    while (scanf("%d", &n) != EOF && n)
    {
        fill(G, G + 105, vector<int>());
        while (scanf("%d", &u) != EOF && u)
        {
            while (scanf("%d", &v) != EOF && v)
                G[u].emplace_back(v);
        }
        scanf("%d", &len);
        while (len--)
        {
            memset(visited, false, sizeof(visited));
            visitedNum = 0;
            scanf("%d", &u);
            dfs(u);
            printf("%d", n - visitedNum);
            for (int i = 1; i <= n; ++i)
            {
                if (!visited[i])
                    printf(" %d", i);
            }
            puts("");
        }
    }
    return 0;
}