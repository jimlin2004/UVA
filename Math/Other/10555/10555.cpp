#include <bits/stdc++.h>
using namespace std;

/*
    用無線小數轉分數的公式即可

    無窮小數轉分數:
    分子: 全部 - 不重複的數字
    分母: 有幾個重複的數字就有幾個9 乘上 有幾個部重複的數字就有幾個0

    另外輸入要處理一下
    由於一定是0.abcde(不斷下去)...
    所以當作字串從index 2開始，到總長度 - 3的位置
*/

string str;

long long gcd(long long a, long long b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

int main()
{
    while (cin >> str)
    {
        int m = str.size();
        if (m == 1 && str[0] == '0')
            break;
        m -= 5;

        long long total = stoll(str.substr(2, m));

        long long p;
        long long q;

        long long resp = 0x3f3f3f3f3f3f3f3f;
        long long resq = 0x3f3f3f3f3f3f3f3f;
        
        // 不重複的長度
        int nore = 0;
        // 此題要枚舉所有可能的無窮小數中分母最小的是答案
        for (int i = 0; i < m; ++i)
        {
            if (nore)
                p = total - stoll(str.substr(2, nore));
            else
                p = total; // stoll裡如果是空字串會報錯
            q = 0;
            for (int j = 0; j < m - nore; ++j)
            {
                q = q * 10 + 9;
            }
            for (int j = 0; j < nore; ++j)
                q = q * 10;
            
            long long g = gcd(p, q);

            p /= g;
            q /= g;

            if (resq > q)
            {
                resp = p;
                resq = q;
            }

            nore++;
        }

        printf("%lld/%lld\n", resp, resq);
    }

    return 0;
}