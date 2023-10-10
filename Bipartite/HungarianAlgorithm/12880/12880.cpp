#include <iostream>
#include <cstring>

bool line[10005][10005] = {false};
bool used[10005] = {false};
int match[10005];
int n, m;

bool find(int x)
{
    for (int i = 0; i < n; i++)
    {
        if (line[x][i] && used[i] == false)
        {
            used[i] = true;
            if (match[i] == -1 || find(match[i]))
            {
                match[i] = x;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    while (scanf("%d %d", &n, &m) != EOF)
    {
        int a, b;
        for (int i = 0; i < n; ++i)
        {
            memset(line[i], 0, sizeof(bool) * n);
        }
        memset(match, -1, sizeof(match));
        for (int i = 0; i < m; ++i)
        {
            scanf("%d %d", &a, &b);
            line[a][b] = true;
        }
        int all = 0;
        for (int i = 0; i < n; ++i)
        {
            memset(used, 0, sizeof(used));
            if (find(i))
                ++all;
        }
        printf("%s\n", (all == n) ? "YES" : "NO");
    }
    return 0;
}