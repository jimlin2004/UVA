#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define MAXN 100005
// (index << 1) + 1 == (index << 1) | 1

struct Node
{
    int l, r;
    int val;
};

Node ST[MAXN << 2];
int val[MAXN];
int shiftNum[MAXN];

void pushUp(int i)
{
    ST[i].val = min(ST[i << 1].val, ST[(i << 1) | 1].val);
}

void build(int l, int r, int index)
{
    ST[index].l = l;
    ST[index].r = r;
    if (l == r)
    {
        ST[index].val = val[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, index << 1);
    build(mid + 1, r, (index << 1) | 1);
    pushUp(index);
}

int query(int l, int r, int index)
{
    if (l <= ST[index].l && r >= ST[index].r)
        return ST[index].val;
    int mid = (ST[index].l + ST[index].r) >> 1;
    if (l > mid)
        return query(l, r, (index << 1) | 1);
    if (r <= mid)
        return query(l, r, index << 1);
    return min(query(l, r, index << 1), query(l, r, (index << 1) | 1)); 
}

void update(int pos, int index, int val)
{
    if (ST[index].l == pos && ST[index].r == pos)
    {
        ST[index].val = val;
        return;
    }
    int mid = (ST[index].l + ST[index].r) >> 1;
    if (pos <= mid)
        update(pos, index << 1, val);
    if (pos > mid)
        update(pos, (index << 1) | 1, val);
    ST[index].val = min(ST[index << 1].val, ST[(index << 1) | 1].val);
}

int main()
{
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &val[i]);
    }
    build(1, n, 1);
    char command[100];
    while (q--)
    {
        scanf("%s", command);
        if (command[0] == 'q')
        {
            int i, ql = 0, qr = 0;
            for (i = 6; command[i] != ','; ++i)
                ql = ql * 10 + (command[i] - '0');
            for (i++; command[i] != ')'; ++i)
                qr = qr * 10 + (command[i] - '0');
            printf("%d\n", query(ql, qr, 1));
        }
        else
        {
            memset(shiftNum, 0, sizeof(shiftNum));
            int j = 1;
            for (int i = 6; i < strlen(command) - 1; ++i)
            {
                if (command[i] == ',')
                {
                    ++j;
                    continue;
                }
                shiftNum[j] = shiftNum[j] * 10 + (command[i] - '0');
            }
            int temp = val[shiftNum[1]];
            for (int i = 1; i < j; ++i)
            {
                val[shiftNum[i]] = val[shiftNum[i + 1]];
                update(shiftNum[i], 1, val[shiftNum[i + 1]]);
            }
            val[shiftNum[j]] = temp;
            update(shiftNum[j], 1, temp);
        }
    }
    return 0;
}