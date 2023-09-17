#include <cstdio>
#include <cstring>
using namespace std;

int parentF[10005];
int parentE[10005];

int findF(int x)
{
    if (parentF[x] < 0)
        return x;
    return parentF[x] = findF(parentF[x]);
}

int findE(int x)
{
    if (parentE[x] < 0)
        return x;
    return parentE[x] = findE(parentE[x]);
}

void UnionF(int a, int b)
{
    int r1 = findF(a);
    int r2 = findF(b);

    if (r1 == r2)
        return;
    if (parentF[r1] < parentF[r2])
    {
        parentF[r1] += parentF[r2];
        parentF[r2] = r1;
    }
    else
    {
        parentF[r2] += parentF[r1];
        parentF[r1] = r2;
    }
}

void UnionE(int a, int b)
{
    int r1 = findE(a);
    int r2 = findE(b);

    if (r1 == r2)
        return;
    if (parentE[r1] < parentE[r2])
    {
        parentE[r1] += parentE[r2];
        parentE[r2] = r1;
    }
    else
    {
        parentE[r2] += parentE[r1];
        parentE[r1] = r2;
    }
}

int main()
{
    int n;
    int cmd, x, y;
    memset(parentF, -1, sizeof(parentF));
    memset(parentE, -1, sizeof(parentE));
    
    scanf("%d", &n);
    while (scanf("%d %d %d", &cmd, &x, &y) != EOF && (cmd + x + y))
    {
        if (cmd == 1)
        {
            int r1 = findE(x);
            int r2 = findE(y);
            if (r1 == r2)
                printf("-1\n");
            else
            {
                UnionF(x, y);
            }
        }
        else if (cmd == 2)
        {
            int r1 = findF(x);
            int r2 = findF(y);
            if (r1 == r2)
                printf("-1\n");
            else
                UnionE(x, y);
        }
        else if (cmd == 3)
        {
            int r1 = findF(x);
            int r2 = findF(y);
            if (r1 == r2)
                printf("1\n");
            else
                printf("0\n");
        }
        else if (cmd == 4)
        {
            int r1 = findE(x);
            int r2 = findE(y);
            if (r1 == r2)
            {
                printf("1\n");
            }
            else
                printf("0\n");
        }
    }

    return 0;
}