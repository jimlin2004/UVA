#include <bits/stdc++.h>
using namespace std;

/*
    題意要求的是:
    列舉所有非空子集，把子集內的數字相乘，再乘上2^{子集大小-1}，最後全部加總。
    Ans = Σ_{S ≠ Φ}( 2^{|S| - 1} Π_{x ∈ S} x )
    其中S是所有pure power set

    step 1: 讓2^{|S| - 1}變成2^{|S|}，所以兩邊同乘2

    2 x Ans = Σ_{S ≠ Φ}( 2^{|S|} Π_{x ∈ S} x )

    step 2: 將2放進去

    2 x Ans = Σ_{S ≠ Φ}( Π_{x ∈ S} 2x )

    此時要求的就是所有數字都先乘2，然後求所有非空子集的乘積總和

    接下來是離散數學時間
    首先
    建立子集時，要做的是對{a_1, a_2, a_3, ...}的每個元素都問a_i要不要選
    寫成數學上可以建構出(1 + a_1)(1 + a_2)(1 + a_3)...
    如果用1，就是不選a_i，用a_i，就是選了a_i
    建構出生成函數
    P(x) = (1 + a_1 x) (1 + a_2 x) ... (1 + a_n x)
    展開會得到
    P(x) = 1 + C_1 x + C_2 x^2 + ... + C_n x^n
    會發現係數
    C1就是所有大小為1的子集乘積和(a_1 + a_2 + ... + a_n)
    C2就是所有大小為2的子集乘積和(a_1 * a_2 + a_2 * a_3 + ...)
    ...
    C_k就是所有大小為k的子集乘積和
    
    所以只要將x = 1代入
    P(1) = 1 + C_1 + C_2 + ... + C_n
    P(1) = (1 + a_1) (1 + a_2) ... (1 + a_n)
    那個1是對應空集合
    所以
    所有非空子集乘積和 = Π^{n}_{i = 1}(1 + a_i) - 1

    step 3:
    所以目前
    2 x Ans = Π^{n}_{i = 1}(1 + 2 x_i) - 1
    移項
    Ans = ( Π^{n}_{i = 1}(1 + 2 x_i) - 1 ) / 2

    此時因為要mod，乘法跟減法簡單用mod性質處理，
    然後 除2 直接用費馬小定理得到2的模逆元即可
*/

long long qpow(long long a, int b, long long MOD)
{
    long long res = 1 % MOD;

    while (b)
    {
        if (b & 1)
            res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }

    return res;
}

int main()
{
    int T;
    scanf("%d", &T);

    const long long MOD = 1000000009;

    // 費馬小定理: a^(p - 1) % P = 1 % P when p is prime
    // 1000000009是已知prime，所以可以用
    // a^(p - 1) x a^{-1} % P = a^{-1} % P
    // -> a^{-1} % P = a^{p - 2} % P
    // 轉由快速冪求答案
    const long long two_inv = qpow(2, MOD - 2, MOD);

    while (T--)
    {
        int n;
        scanf("%d", &n);

        long long val;

        long long res = 1;

        for (int i = 0; i < n; ++i)
        {
            scanf("%lld", &val);

            // 利用生成函數的公式
            res = (res) * (1 + 2 * val) % MOD;
        }

        // 記得-1
        res = (res - 1 + MOD) % MOD;
        // 記得 / 2
        res = (res * two_inv) % MOD;

        printf("%lld\n", res);
    }
    return 0;
}