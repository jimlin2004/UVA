#include <bits/stdc++.h>
using namespace std;

/*
    有N張票，編號是1 ~ N，隨意選M個數，將每張票的數字去除這M個數字，
    只要有任一個可以整除，那張票就會丟棄
    問剩下的數字有幾個

    利用數學概念
    1 ~ 10中有 10 / 2 = 5個數字會被2整除
    1 ~ 10中有 10 / 3 = 3個數字會被3整除
    但是還要補回去被6整除的 10 / 6 = 1個

    所以總共有
    10 - 5 - 3 + 1 = 3個數字會被留下

    這就是排容原理的出現

    最後答案是
    res = 
    N - (所有一個數字的最小公倍數整除個數) + (所有兩個數字的最小公倍數整除個數) 
      - (所有三個數字的最小公倍數整除個數) + ...

    因此下方的作法就是利用dfs做出所有subset的最小公倍數，利用這個最小公倍數算出整除個數
    然後記在表中，之後排容原理公式計算答案
*/

long long nums[20];

// table[i] = {...} -> 所有用i個數字的最小公倍數有多少整除個數
vector<vector<long long>> table;
// dfs用的中間產物
vector<long long> currVec;
long long n;
int m;

// 算出整個vector中數字的最小公倍數
long long getLCM(const vector<long long>& vec)
{
    long long gcd;
    long long lcm = vec[0];

    for (int i = 1; i < vec.size(); ++i)
    {
        gcd = __gcd(lcm, vec[i]);
        lcm = (lcm * vec[i]) / gcd;
    }

    return lcm;
}

// 枚舉所有subset
void dfs(int i)
{
    if (i == m)
    {
        if (currVec.size() > 0)
        {
            long long lcm = getLCM(currVec);
            table[currVec.size()].emplace_back(lcm);
        }

        return ;
    }

    dfs(i + 1);
    currVec.emplace_back(nums[i]);
    dfs(i + 1);
    currVec.pop_back();
}

int main()
{
    while (scanf("%lld %d", &n, &m) != EOF)
    {
        table.assign(m + 5, {});

        for (int i = 0; i < m; ++i)
        {
            scanf("%lld", &nums[i]);
        }

        dfs(0);

        // 利用排容原理公式
        long long res = n;
        int scale = -1; // 一下 加 一下 減
        for (int i = 1; i <= m; ++i) // 一個數字組成、兩個數字組成...
        {
            for (long long v: table[i])
                res += scale * n / v;
            scale *= -1;
        }

        printf("%lld\n", res);
    }

    return 0;
}