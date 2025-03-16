#include <bits/stdc++.h>
using namespace std;


/*
    題意: 
        給定 a, b, k，求[a, b]之間數字和被k整除同時數值本身也被k整除的個數
        其中 1 <= a <= b < 2 ^ 31, 0 < k < 10000
    看到a與b的區間就知道不可能從a ~ b搜一遍
    能做是用數字和這一項，也就是湊數字

    想辦法設計出function sumf(n)計算0 ~ n - 1數字和與數值能被k整除的數
    此時輸入 a, b, k答案即為 sumf(b + 1) - sumf(a) <- 前綴和的概念

    sumf(n)如何實作，只好想辦法由左至右湊數字檢查
    ex: 23*** 五位數，k = 7
    數字和已知左邊固定 (2 + 3) % 7 = 5
    此時***的數字和一定要是 數字和(***) % 7 = 2
    才能使 數字和(23***) % 7 = 0
    同時數值和也是一樣的概念
    數值和已知左邊固定 (23000) % 7 = 4
    此時***的數值和一定要是 (***) % 7 = 3
    才能使 (23***) % 7 = 0

    所以當左邊位數枚舉時，對於右邊還沒搜尋的位數也是做一樣的邏輯
    設計遞迴函式 dfs(d, m1, m2) = cnt代表
    現在需要d位數字，數字和 % k = m1，數值和 % k = m2有多少種
    利用dfs(d, m1, m2)完成sumf(n)的計算

    利用上面的23***例子，可以看出遞迴式
    dfs(d, m1, m2) = sum{ f(d - 1, (m1 - x) mod k, (m2 - x * 10 ^ (d - 1))) | x = 0 ~ 9 }
    也就是枚舉現在的數字為x，轉交下個位數繼續搜尋
    同時邊界條件為當d == 0(需要0位數字)，m1 == 0與m2 == 0就是找到了，回傳1
    否則為0

    有了dfs，就能實作sumf(n)
    ex: n = 54321
    第一層搜
    4****
    3****
    2****
    1****
    0****
    注意不用搜 5**** !!!
    因為下個位數會搜
    53***
    52***
    51***
    50***
    接下來搜
    542**
    541**
    540**
    搜
    5431*
    5430*
    最後
    54320

    如此就能夠搜完0 ~ n - 1所有被k整除的數有幾個

    另外由於1 <= a <= b < 2 ^ 31, 0 < k < 10000
    2 ^ 31 = 2147483648
    最多10位數，數字和最多 2 + 9 * 9 = 83(估算)
    只要 k > 83 就不可能存在[a, b]之間 mod k = 0
    所以一定是0

    最後是遞迴式需要dp記憶化搜尋加速
*/


int Pow10[10]; // pow10[]，用大寫因為cpp有built-in function 'pow10'
// dp[d][m1][m2] -> 這數字有d位數，數字和 mod k = m1且數值 mod k = m2
int dp[15][90][90];

inline int mod(int n, int k)
{
    // 避免負數 mod 的錯誤
    // 確保範圍一定是 0 ~ k - 1
    return (n % k + k) % k; 
}

int dfs(int d, int m1, int m2, int k)
{
    if (d == 0)
        return (m1 == 0 && m2 == 0) ? 1 : 0;
    
    if (dp[d][m1][m2] != -1)
        return dp[d][m1][m2];
    int res = 0;
    for (int x = 0; x <= 9; ++x)
    {
        res += dfs(d - 1, mod(m1 - x, k), mod(m2 - x * Pow10[d - 1], k), k);
    }

    return dp[d][m1][m2] = res;
}

int sumf(int n, int k)
{
    string digits = to_string(n);
    int nd = digits.size(); // 幾位數
    
    int leftVal = 0; // 目前枚舉到的位數左邊數值
    int leftDigitsSum = 0; // 目前枚舉到的位數左邊數字和
    int res = 0;

    for (int i = 0; i < nd; ++i)
    {
        int m = nd - 1 - i; // 右邊位數
        for (int d = 0; d < digits[i] - '0'; ++d)
        {
            // res += dfs(m, mod(-leftDigitsSum - d, k), mod(-leftVal - d * pow10[m], k), k);
            res += dfs(m, (k - mod(leftDigitsSum + d, k)) % k, (k - mod(leftVal + d * Pow10[m], k)) % k, k);
        }
        leftVal += (digits[i] - '0') * Pow10[m];
        leftDigitsSum += (digits[i] - '0');
    }
    return res;
}

int main()
{
    Pow10[0] = 1;
    for (int i = 1; i < 10; ++i)
        Pow10[i] = 10 * Pow10[i - 1];

    int T;
    scanf("%d", &T);
    int a, b, k;
    while (T--)
    {
        scanf("%d %d %d", &a, &b, &k);
        memset(dp, -1, sizeof(dp));
        if (k > 85)
            puts("0");
        else
            printf("%d\n", sumf(b + 1, k) - sumf(a, k));
    }
    return 0;
}