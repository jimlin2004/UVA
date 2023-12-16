#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 100005

int nums[MAXN];
int st[4 * MAXN]; //-1 or 0 or 1

inline int pull(int l, int r)
{
    return st[l] * st[r];
}

void build(int l, int r, int i)
{
    if (l == r) 
    {
        st[i] = nums[l];
        return;
    }
    int mid = l + ((r - l) >> 1);
    build(l, mid, i * 2);
    build(mid + 1, r, i * 2 + 1);
    st[i] = pull(i * 2, i * 2 + 1);
}

int query(int ql, int qr, int l, int r, int i)
{
    if (ql <= l && r <= qr)
        return st[i];
    int mid = l + ((r - l) >> 1);
    int product = 1;
    if (ql <= mid)
        product *= query(ql, qr, l, mid, i * 2);
    if (qr > mid)
        product *= query(ql, qr, mid + 1, r, i * 2 + 1);
    return product;
}

void update(int ql, int qr, int l, int r, int i, int c)
{
    if (ql <= l && r <= qr)
    {
        st[i] = c;
        return;
    }
    int mid = l + ((r - l) >> 1);
    if (ql <= mid) update(ql, qr, l, mid, i * 2, c);
    if (qr > mid) update(ql, qr, mid + 1, r, i * 2 + 1, c);
    st[i] = pull(i * 2, i * 2 + 1);
}

inline int getSign(int val)
{
    if (val < 0) return -1;
    else if (val == 0) return 0;
    else return 1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    while (cin >> n >> k)
    {
        memset(st, 0, sizeof(st));
        int val;
        for (int i = 1; i <= n; ++i)
        {
            cin >> val;
            nums[i] = getSign(val);
        }
        char cmd;
        int x, y;
        int sign;
        build(1, n, 1);
        for (int i = 0; i < k; ++i)
        {
            cin >> cmd >> x >> y;
            if (cmd == 'C')
                update(x, x, 1, n, 1, getSign(y));
            else
            {
                sign = query(x, y, 1, n, 1);
                if (sign == 1)
                    cout << '+';
                else if (sign == 0)
                    cout << '0';
                else
                    cout << '-';
            }
        }
        cout << '\n';
    }
    return 0;
}