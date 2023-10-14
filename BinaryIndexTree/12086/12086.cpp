#include <cstdio>
#include <cstring>

// binary index tree靶題，區間和，單點修改

#define lowbit(x) ((x) & (-x))

int val[200005];
int BIT[200005];

void add(int index, int c)
{
    while (index <= 200005)
    {
        BIT[index] += c;
        index += lowbit(index);
    }
}

int prefixSum(int index)
{
    int res = 0;
    while (index > 0)
    {
        res += BIT[index];
        index -= lowbit(index);
    }
    return res;
}

int rangeSum(int l, int r)
{
    return prefixSum(r) - prefixSum(l - 1);
}

int main()
{
    int n;
    int Case = 1;
    bool first = true;
    char cmd[10];
    int x, y;

    while (~scanf("%d", &n) && n)
    {
        memset(val, 0, sizeof(val));
        memset(BIT, 0, sizeof(BIT));

        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &x);
            val[i] = x;
            add(i, x);
        }

        if (first)
            first = false;
        else
            puts("");
        printf("Case %d:\n", Case++);

        while (scanf("%s", cmd))
        {
            if (cmd[0] == 'M')
            {
                scanf("%d %d", &x, &y);
                printf("%d\n", rangeSum(x, y));
            }
            else if (cmd[0] == 'S')
            {
                scanf("%d %d", &x, &y);
                add(x, y - val[x]);
                val[x] = y;
            }
            else
                break;
        }
    }
    return 0;
}