#include <bits/stdc++.h>
using namespace std;

/*
    World Final數論題
    本質上是一個用多項式p(n, k) [n最多k次的意思]
    檢查p(n + 1, k) - p(n, k)會得到一個多項式p'(n, k')
    使得p(n, k) + p'(n, k') = p(n + 1, k)
    之後就能利用mod的運算性質
    也就是說
    若p(n, k) % D是整數
    則只需檢查p'(n') % D是否是整數
    當目前多項式最多k次，只需檢查到p(n + 1) % D也是整數
    就能確認該多項式p(n) % D一定都是整數

    證明不明，紫書上有
    推導過程看 推導.png

    結論是
    當多項式最多maxk次
    需要檢查p(0) % D ~ p(maxk + 1) % D是否都為0
    即可知道多項式是否都是整數
*/


#define maxn 105

struct Term
{
    long long c;
    long long k;
};

Term poly[maxn];
char input[10005];

long long maxk; // 多項式最高次
int m; // poly[]的len
long long D; // 除數

void parse()
{
    maxk = 0;
    m = 0;
    D = 0;
    int len = strlen(input);
    // 狀態機處理法
    int state = 0; // state = 0 -> 係數，state = 1 -> 指數
    long long k = 0; // 當前處理的指數數字
    long long c = 0; // 當前處理的係數數字
    
    // 一開始假設為正(可能沒有符號)
    long long sign = 1; // 當前的sign

    int i = 1;
    // 第一個sign額外處理
    if (input[1] == '+')
    {
        sign = 1;
        ++i;
    }
    else if (input[1] == '-')
    {
        sign = -1;
        ++i;
    }
    
    for (i; i < len; ++i)
    {
        if ('0' <= input[i] && input[i] <= '9')
        {
            if (state == 0) c = c * 10 + input[i] - '0';
            else if (state == 1) k = k * 10 + input[i] - '0';
        }
        else if (input[i] == 'n') state = 1; // 要開始處理指數
        else if (input[i] == '^') continue;
        else if (input[i] == '/') break; // 要開始處理除數
        else if (input[i] == '+' || input[i] == '-' || input[i] == ')') // term的結束
        {
            if (c == 0) c = 1; // 可能沒有前導係數
            if (state == 1 && k == 0) k = 1; // 可能沒有指數
            maxk = max(maxk, k);
            poly[m++] = {sign * c, k};
            c = 0;
            k = 0;
            state = 0;
            if (input[i] == '+')
                sign = 1;
            else if (input[i] == '-')
                sign = -1;
        }
    }

    // 處理除數
    // i += 1 for 跳過'/'
    for (i += 1; i < len; ++i)
        D = D * 10 + (input[i] - '0');
}

long long qpow(long long x, long long k)
{
    long long res = 1;
    while (k)
    {
        if (k & 1)
            res = ((res % D) * (x % D)) % D;
        x = ((x % D) * (x % D)) % D;
        k >>= 1;
    }
    return res;
}

// 將n帶入poly進去算並且mod過
inline long long cal(long long n)
{
    long long res = 0;
    for (int i = 0; i < m; ++i)
    {
        res = (res + (poly[i].c * qpow(n, poly[i].k)) % D) % D;
    }
    return res;
}

bool judge()
{
    for (int i = 0; i <= maxk + 1; ++i)
    {
        if (cal(i) != 0)
            return false;
    }
    return true;
}

int main()
{
    int Case = 0;
    while (scanf("%s", input))
    {
        if (input[0] == '.')
            break;
        parse();
        printf("Case %d: ", ++Case);
        if (judge())
            puts("Always an integer");
        else
            puts("Not always an integer");
    }
    return 0;
}