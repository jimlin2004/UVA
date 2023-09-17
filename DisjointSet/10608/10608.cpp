#include <cstdio>
#include <cstring>
#include <algorithm>

int parent[30005];

int findRoot(int x)
{
    if (parent[x] < 0)
        return x;
    return parent[x] = findRoot(parent[x]);
}

void Union(int a, int b)
{
    int r1 = findRoot(a);
    int r2 = findRoot(b);
    if (r1 == r2) return;
    if (parent[r1] < parent[r2])
    {
        parent[r1] += parent[r2];
        parent[r2] = r1;
    }
    else
    {
        parent[r2] += parent[r1];
        parent[r1] = r2;
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    int n, m;
    int p1, p2;
    while (T--)
    {
        scanf("%d %d", &n, &m);
        memset(parent, -1, sizeof(parent));
        for (int i = 0; i < m; ++i)
        {
            scanf("%d %d", &p1, &p2);
            Union(p1, p2);
        }
        int maxN = -1;
        for (int i = 1; i <= n; ++i)
            maxN = std::max(maxN, -(parent[i]));
        printf("%d\n", maxN);
    }
    return 0;
}