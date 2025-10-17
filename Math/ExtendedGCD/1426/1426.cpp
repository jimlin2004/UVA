#include <bits/stdc++.h>
using namespace std;

/*
    題意:
        給定x, N, r_1

        求所有滿足 r^2 = x (mod N) 的r，r < N
        其中r_1是某個r
    
    題解:
        r^2 = x   (mod N)
        r_1^2 = x (mod N)

        所以可以寫作
        r^2 + k_1 * N = x    --- (1)
        r_1^2 + k_2 * N = x  --- (2)

        (1) - (2)
        => r^2 - r_1^2 + (k_1 - k_2) * N = 0
        => r^2 - r_1^2 = -(k_1 - k_2) * N [移項]
        => r^2 - r_1^2 = k * N [假設 -(k_1 - k_2) = k]
        => (r + r1) * (r - r1) = k * N [等式左項因數分解]

        假設
        N = P * Q  [P與Q是N的因數]
        r + r_1 = 0 (mod P)
        r - r_1 = 0 (mod Q)
        則
        r + r_1 = k'_1 * P
        r - r_1 = k'_2 * Q
        移項
        r = k'_1 * P - r_1
        r = k'_2 * Q + r_1
        由上兩式可得
        k'_1 * P - r_1 = k'_2 * Q + r_1 = r
        移項
        k'_1 * P - k_2 * Q = 2r_1
        透過mod定義可得
        P * k'_1 = 2r_1 (mod Q)
        上式滿足
        ax = b (mod m)
        此式若引入 gcd(a, m)
        則
        (a / gcd(a, m))x = (b / gcd(a, m)) (mod (m / gcd(a, m)))
        x有唯一解
        使用ex_gcd(a / gcd(a, m), m / gcd(a, m))可以得到x_0
        此時x的通解為
        x = x_0 + (m / gcd(a, m)) * t

        利用ex_gcd得到的通解可以得到k'_1
        此時可以帶回去前面的等式
        k'_1 * P - r_1 = r
        
        k'_1用算得拿到
        r_1已知 (題目有給)
        則P我們可以用枚舉的
*/

set<long long> res;
long long X, N, r1;

long long ex_gcd(long long a, long long b, long long& x, long long& y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }

    long long gcd = ex_gcd(b, a % b, x, y);
    long long temp = x;
    x = y;
    y = temp - a / b * y;

    return gcd;
}

// 對應   ax = b (mod m)
// 又對回 P * k'_1 = 2r_1 (mod Q)
void solve(long long a, long long b, long long m)
{
    long long x, y;
    long long gcd = ex_gcd(a, m, x, y);

    // ax = b (mod m)有解的條件是 gcd(a, m) | b
    if (b % gcd == 0)
    {
        // ex_gcd得到 ax + my = gcd(a, m)的基本解
        // 兩邊同乘 b / gcd(a, m)
        // 得到 a (x * (b / gcd(a, m))) + m (y * (b / gcd(a, m))) = b
        // 在mod m的情況下
        // 得到   a (x * (b / gcd(a, m))) = b (mod m)
        // 對應回 ax_0 = b (mod m)
        // 所以取 x_0 = x * b / gcd(a, m)
        long long x_0 = x * b / gcd;

        // 由於當前知道 ax_0 = b (mod m)
        // 通解是: x = x_0 + t * (m / gcd(a, m))
        // 為了讓x_0是通解裡面最小的正整數
        // 要 x_0去mod (m / gcd(a, m))
        // 但是因為現在x_0可能是負的
        // 所以mod (m / gcd(a, m))的時候要 加上 (m / gcd(a, m))
        x_0 = (x_0 % (m / gcd) + m / gcd) % (m / gcd);

        // 由於之前 r = k'_1 * P - r_1
        // 且求得k'_1 = x_0 + t * (m / gcd(a, m))
        // 代入可得
        // r = P( x_0 + t * (m / gcd(a, m)) ) - r_1
        // 對應回來 a = P, b = 2 * r_1
        // 則 r = a (x_0 + t * (m / gcd(a, m))) - b / 2
        // => r = ax_0 + t * (am / gcd(a, m)) - b / 2
        // => r = ax_0 + t * lcm(a, m) - b / 2
        // 所以下方利用累加lcm做到枚舉t的效果
        long long r = a * x_0 - b / 2;
        long long lcm = a / gcd * m;
        for (; r < N; r += lcm)
        {
            if (r >= 0 && (r * r) % N == X)
                res.insert(r);
        }
    }
}

int main()
{
    int testcase = 0;

    while (scanf("%lld %lld %lld", &X, &N, &r1))
    {
        if (X == 0 && N == 0 && r1 == 0)
            break;
        
        printf("Case %d:", ++testcase);

        res.clear();

        long long top = sqrt(N) + 1;
        for (long long P = 1; P <= top; ++P)
        {
            // 枚舉P，N = P * Q，同時P只需要枚舉到sqrt(N)
            // 另一半直接用 N / P算出來
            if (N % P == 0)
            {
                solve(P, 2 * r1, N / P);
                solve(N / P, 2 * r1, P);
            }
        }

        for (long long ans: res)
            printf(" %lld", ans);
        puts("");
    }

    return 0;
}