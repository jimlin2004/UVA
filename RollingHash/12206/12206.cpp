#include <bits/stdc++.h>
using namespace std;

// 以下送出還沒過QQ

const int maxn = 400005;
const long long MOD1 = 1e9 + 7;
const long long MOD2 = 1e9 + 9;
const long long P1 = 131;
const long long P2 = 137;

// 像prefix一樣index右移1
long long H1[maxn];
long long H2[maxn];
long long powP1[maxn];
long long powP2[maxn];

struct pair_hash
{
    size_t operator()(const pair<long long, long long>& p) const
    {
        return p.first * 1000000009LL + p.second;
    }
};

string s;
unordered_map<pair<long long, long long>, int, pair_hash> mp;


void rollingHash(const string& s)
{
    H1[0] = 0;
    H2[0] = 0;
    powP1[0] = 1;
    powP2[0] = 1;

    for (int i = 1; i <= s.size(); ++i)
    {
        H1[i] = (H1[i - 1] * P1 % MOD1 + s[i - 1]) % MOD1;
        H2[i] = (H2[i - 1] * P2 % MOD2 + s[i - 1]) % MOD2; 
        powP1[i] = (powP1[i - 1] * P1) % MOD1;
        powP2[i] = (powP2[i - 1] * P2) % MOD2;
    }
}

pair<long long, long long> getHash(int l, int r)
{
    long long hash1 = (H1[r] - (H1[l - 1] * powP1[r - l + 1] % MOD1) + MOD1) % MOD1;
    long long hash2 = (H2[r] - (H2[l - 1] * powP2[r - l + 1] % MOD2) + MOD2) % MOD2;

    return {hash1, hash2};
};

int check(int len, int m)
{
    int last = -1;
    mp.clear();

    for (int i = 0; i < s.size() - len + 1; ++i)
    {
        int l = i;
        int r = i + len - 1;

        int& cnt = mp[getHash(l + 1, r + 1)];
        ++cnt;
        if (cnt >= m)
        {
            last = i;
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
    
        int res;
        int l = 0, r = s.size();

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

