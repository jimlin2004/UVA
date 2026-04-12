#include <bits/stdc++.h>
using namespace std;

/*
    題意很簡單: 問m^n個位數是多少
    但 0 <= m, n <= 10^101

    解法:
    因為只問個位數，所以其實是在解 m^n mod 10

    所以m有多少位都不重要，只要管m的個位數即可
    但n在指數次需要額外處理
    因為數字的冪次數在mod 10的情況下數字會有循環

    如 2^1 mod 10 = 2, 2^2 mod 10 = 4, 2^3 mod 10 = 8, 2^4 mod 10 = 6, 2^5 mod 10 = 2 ...
    循環長度為4

    所以我們只需要知道 n mod (循環長度) = 多少即可回答

    但n很大，事實上作法也很簡單
    直接模擬長除法，因為現在商不重要，長除法就很好寫

    看下方
*/

string m, n;

bool used[15];
vector<int> remains;

// 長除法
int getRemain(int q, string& p)
{
    // 長除法裡目前的數字
    int curr = 0;

    for (int i = 0; i < p.size(); ++i)
    {
        // 就跟長除法一樣，每次先 x 10 加上新的一個數字
        curr = curr * 10 + p[i] - '0';

        // 只要管餘數
        curr %= q;
    }

    return (curr == 0) ? q : curr;
}

int main()
{
    while (cin >> m >> n)
    {
        memset(used, 0, sizeof(used));
        remains.clear();

        if (m == "0" && n == "0")
            break;
        if (n == "0")
        {
            puts("1");
            continue;
        }

        // m只需要個位數
        m = m.back();

        int curr = m[0] - '0';
        while (!used[curr])
        {
            remains.push_back(curr);
            used[curr] = true;
            curr = curr * (m[0] - '0') % 10;
        }

        printf("%d\n", remains[getRemain(remains.size(), n) - 1]);
    }

    return 0;
}