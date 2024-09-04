#include <cstdio>
#include <cmath>
using namespace std;

/*
    推導過程看 推導.png
    基本上公式分子是巴斯卡三角形作為係數呈上輸入的數字(C^{n - 1}_0 ~ C^{n - 1}_{n - 1})
    分母是2^{n - 1}
    但是數字太大
    所以借用log將數字縮小，同時一些遞迴關係要改成log的方式(及乘變加，除變減)
    由於用log縮放過，所以最後要用exp變回來

    C^n_r的關係式log版: C^n_{r + 1} = C^n_{r + 1} - log(r + 1) + log(n - r);
*/

#define maxn 50005

double log_fact[maxn];
double log_pow2[maxn];

int main()
{
    log_fact[0] = log(1);
    log_pow2[0] = log(1);
    for (int i = 1; i < maxn; ++i)
    {
        log_fact[i] = log_fact[i - 1] + log(i);
        log_pow2[i] = log_pow2[i - 1] + log(2);
    }

    int T;
    scanf("%d", &T);
    int Case = 0;
    while (T--)
    {
        int n;
        scanf("%d", &n);
        double input;
        double res = 0.0;
        double C = log(1);
        int r = 0;
        for (int i = 0; i < n; ++i)
        {
            scanf("%lf", &input);
            // log要特別處理負數
            if (input < 0)
                res -= exp(C + log(-input) - log_pow2[n - 1]);
            else
                res += exp(C + log(input) - log_pow2[n - 1]);
            C = C - log(r + 1) + log((n - 1) - r);
            ++r;
        }
        res = 
        printf("Case #%d: %.3lf\n", ++Case, res);
    }
    return 0;
}

/*
4
1
10.4
2
1.0 2.2
3
1 2 3
5
1 2 3 4 5
*/