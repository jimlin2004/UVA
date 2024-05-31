#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

#define maxn 1005

int parent[maxn];
int t[maxn], c[maxn], w[maxn];
bool existed[maxn];

int main()
{
    int n;
    int root;

    while (scanf("%d %d", &n, &root) && (n && root))
    {
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &c[i]);

            t[i] = 1;
            existed[i] = true;
            w[i] = c[i];
        }

        int u, v;
        for (int i = 1; i < n; ++i)
        {
            scanf("%d %d", &u, &v);
            parent[v] = u;
        }

        for (int i = 1; i < n; ++i)
        {
            int k = -1;
            double maxW = -1;
            for (int j = 1; j <= n; ++j)
            {
                if (j != root && existed[j])
                {
                    if (maxW < ((double)w[j] / t[j]))
                    {
                        maxW = ((double)w[j] / t[j]);
                        k = j;
                    }
                }
            }

            for (int j = 1; j <= n; ++j)
            {
                if (parent[j] == k)
                {
                    parent[j] = parent[k];
                }
            }

            w[parent[k]] += w[k];
            c[parent[k]] += t[parent[k]] * w[k] + c[k];
            t[parent[k]] += t[k];
            existed[k] = false;
        }

        printf("%d\n", c[root]);
    }
    return 0;
}
