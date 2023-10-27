#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

int parent[20005];
int dis[20005]; //dis[u] -> u到最上級祖先的距離

int findRoot(int x)
{
    if (parent[x] < 0)
        return x;
    int root = findRoot(parent[x]);
    dis[x] += dis[parent[x]]; //更新距離並壓縮路徑
    return parent[x] = root;
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        scanf("%d", &n);
        memset(parent, -1, sizeof(parent));
        memset(dis, 0, sizeof(dis));

        char cmd;
        int u, v;
        while (scanf("%c", &cmd) && cmd != 'O')
        {
            if (cmd == 'E')
            {
                scanf("%d", &u);
                findRoot(u);
                printf("%d\n", dis[u]);
            }
            else if (cmd == 'I')
            {
                scanf("%d %d", &u, &v);
                parent[u] = v;
                dis[u] = abs(u - v) % 1000;
            }
        }
    }
    return 0;
}