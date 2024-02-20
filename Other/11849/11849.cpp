#include <cstdio>
#include <cstring>

//如同merge sort的合併過程

#define maxn 1000005

int jack[maxn];
int jill[maxn];

int main()
{
    int n, m;
    while (scanf("%d %d", &n, &m) && (n != 0 && m != 0))
    {
        int res = 0;
        for (int i = 0; i < n; ++i)
            scanf("%d", &jack[i]);
        for (int i = 0; i < m; ++i)
            scanf("%d", &jill[i]);
        
        int i = 0, j = 0;
        while (i < n && j < m)
        {
            if (jack[i] == jill[j])
            {
                ++res;
                ++i, ++j;
            }
            else if (jack[i] < jill[j])
                ++i;
            else
                ++j;
        }

        printf("%d\n", res);
    }
    return 0;
}