#include <cstdio>
#include <cmath>

/*
    數學解二元一次方程式
    設中空的兩個洞(正方形)邊長為a
    中空的兩個洞距離外矩形為b
    外矩形不管中空洞的面積為s(題目given)
    參考推導.png
    外矩形的長為3b+2a，寬為2b+a
    依題意可列式
    (3b + 2a)(2b + a) = s - 2 * a^2 (也就是全部面積 - 兩個洞的面積)
    => 6b^2 + 7ab + 2a^2 = s + 2a^2
    => 6b^2 + 7ab = s
    => a = (s - 6b^2) / (7b)

    所以枚舉即可(記得mod避免溢位)
*/

#define Mod 100000007

int main()
{
    long long s;
    while (scanf("%lld", &s) != EOF && s)
    {
        bool hasOutput = false;
        
        long long bLim = sqrt(s / 6.0);
        for (long long b = 1; b < bLim; ++b)
        {
            if ((s - 6 * b * b) % (7 * b) == 0)
            {
                //mod 避免溢位
                long long a = (s - 6 * b * b) / (7 * b) % Mod;
                hasOutput = true;
                a *= a;
                //先mod避免溢位
                a %= Mod;
                printf("Possible Missing Soldiers = %lld\n", (a * 2) % Mod);
            }
        }

        if (!hasOutput)
            puts("No Solution Possible");
        puts("");
    }
    return 0;
}