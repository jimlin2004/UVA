#include <bits/stdc++.h>
using namespace std;

/*
    滾動hash靠運氣

    下方hash是用unsigned long long自動做到 mod 2^64

    正確解法 suffix array + 單調陣列二分搜
*/

const int maxn = 400005;
const unsigned long long P1 = 131;
const unsigned long long P2 = 137;

// 由右到左建的hash suffix sum
unsigned long long H1[maxn];
unsigned long long H2[maxn];
unsigned long long powP1[maxn];
unsigned long long powP2[maxn];

string s;

void rollingHash(const string& s)
{
    int n = s.size();

    H1[n] = 0;
    H2[n] = 0;

    for (int i = n - 1; i >= 0; --i)
    {
        H1[i] = H1[i + 1] * P1 + (s[i] - 'a');
        H2[i] = H2[i + 1] * P2 + (s[i] - 'a');
    }

    powP1[0] = 1;
    powP2[0] = 1;

    for (int i = 1; i <= n; ++i)
    {
        powP1[i] = powP1[i - 1] * P1;
        powP2[i] = powP2[i - 1] * P2;
    }
}

inline pair<unsigned long long, unsigned long long> getHash(int l, int r)
{
    return {
        H1[l] - H1[r + 1] * powP1[r - l + 1],
        H2[l] - H2[r + 1] * powP2[r - l + 1]
    };
}

// mp容易發生碰撞
// int check(int len, int m)
// {
//     int last = -1;
//     mp.clear();

//     for (int i = 0; i < s.size() - len + 1; ++i)
//     {
//         int l = i;
//         int r = i + len - 1;

//         int& cnt = mp[getHash(l, r)];
//         ++cnt;
//         if (cnt >= m)
//         {
//             last = i;
//         }
//     }

//     return last;
// }

pair<unsigned long long, unsigned long long> ha[maxn];
int pos[maxn];

int check(int len, int m)
{
    if (len == 0)
        return -1;

    int last = -1;

    for (int i = 0; i < s.size() - len + 1; ++i)
    {
        pos[i] = i;
        ha[i] = getHash(i, i + len - 1);
    }

    sort(pos, pos + s.size() - len + 1, [](const int a, const int b) {
        if (ha[a] == ha[b])
            return a < b;
        return ha[a] < ha[b];
    });

    int cnt = 0;

    for (int i = 0; i < s.size() - len + 1; ++i)
    {
        if (i == 0 || ha[pos[i]] != ha[pos[i - 1]])
            cnt = 1;
        else
            ++cnt;
        if (cnt >= m)
        {
            last = max(last, pos[i]);
        }
    }

    return last;
}


int main()
{
    cin.sync_with_stdio(0);
    cin.tie(0);

    int m;
    while (cin >> m && m)
    {
        cin >> s;

        rollingHash(s);

        int res = -1;
        int l = 0, r = s.size() + 1;

        while (l + 1 < r)
        {
            int mid = (l + r) >> 1;
            int last = check(mid, m);

            if (last != -1)
            {
                l = mid;
                res = last;
            }
            else
                r = mid;
        }

        if (s.size() == 1 && m == 1)
            cout << "1 0\n";
        else if (l == 0)
            cout << "none\n";
        else
            cout << l << ' ' << res << '\n';
    }

    return 0;
}

