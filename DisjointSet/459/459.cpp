#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int parent[30];

int find(int x)
{
    if (parent[x] < 0)
        return x;
    else
        return parent[x] = find(parent[x]);
}

void Union(int a, int b)
{
    int r1 = find(a);
    int r2 = find(b);

    if (r1 == r2)
        return;
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
    int Case;
    char input[10];
    int n;
    bool flag = false;
    scanf("%d", &Case);
    getchar(); // for \n
    getchar(); // for \n
    while (Case--)
    {
        fgets(input, 10, stdin); // for single char
        n = input[0] - 'A';

        memset(parent, -1, sizeof(parent));

        while (fgets(input, 10, stdin))
        {
            if (input[0] == '\n')
                break;
            Union(input[0] - 'A', input[1] - 'A');
        }

        int res = 0;
        for (int i = 0; i <= n; ++i)
        {
            if (parent[i] < 0)
                ++res;
        }

        if (flag)
            puts("");
        else
            flag = true;
        printf("%d\n", res);
    }
}