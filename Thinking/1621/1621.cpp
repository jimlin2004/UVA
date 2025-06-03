#include <bits/stdc++.h>
using namespace std;

/*
    只能說很奇怪的題目
    似乎近幾年送出去UVA都是錯的?

    然後這題是思維題
    這題要找到一個解法(不唯一)
    但下方的解法網路上找不到證明

    可能的推導過程可以看 推導1 ~ 6.png
*/

#define maxn 15005

int res[maxn];

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        int m = 0; // 答案長度
        int pos = 0; // 當前位置
        
        res[m++] = pos;

        // 先將三站票優先用完
        if (c % 3 == 0)
        {
            for (int i = 0; i < c / 3; ++i)
                res[m++] = (pos += 3); // 向右用三站票c / 3張
            res[m++] = ++pos;          // 向右用一張一站票
            --a;
            for (int i = 0; i < c / 3; ++i)
                res[m++] = (pos -= 3); // 向左用三站票c / 3張
            res[m++] = ++pos;          // 向右用一張一站票
            --a;
            for (int i = 0; i < c / 3; ++i)
                res[m++] = (pos += 3); // 向右用三站票c / 3張
        }
        else if (c % 3 == 1)
        {
            for (int i = 0; i < c / 3 + 1; ++i)
                res[m++] = (pos += 3); // 向右用三站票c / 3 + 1張
            res[m++] = (pos -= 2);     // 向左用一張二站票
            --b;
            for (int i = 0; i < c / 3; ++i)
                res[m++] = (pos -= 3); // 向左用三站票c / 3張
            res[m++] = (++pos);        // 向右用一張一站票
            --a;
            for (int i = 0; i < c / 3; ++i)
                res[m++] = (pos += 3); // 向右用三站票c / 3張
            res[m++] = (pos += 2);     // 向右用一張二站票
            --b;
        }
        else if (c % 3 == 2)
        {
            for (int i = 0; i < c / 3 + 1; ++i)
                res[m++] = (pos += 3); // 向右用三站票c / 3 + 1張
            res[m++] = (--pos);        // 向左用一張一站票
            --a;
            for (int i = 0; i < c / 3; ++i)
                res[m++] = (pos -= 3); // 向左用三站票c / 3張
            res[m++] = (--pos);        // 向左用一張一站票
            --a;
            for (int i = 0; i < c / 3 + 1; ++i)
                res[m++] = (pos += 3); // 向右用三站票c / 3 + 1張
        }

        // 只剩下一站票與二站票
        while (a > 1)
        {
            --a;
            res[m++] = ++pos; // 向右連續用一站票到剩下一張
        }
        for (int i = 0; i < (b + 1) / 2; ++i) // (b + 1) / 2是ceil的概念
            res[m++] = (pos += 2); // 向右連續使用一半剩下的二站票
        if (b % 2)
            res[m++] = --pos; // 如果剩下的二站票是奇數，向左用一張一站票
        else
            res[m++] = ++pos; // 如果剩下的二站票是偶數，向右用一張一站票
        for (int i = b & 1; i < (b + 1) / 2; ++i) // (b + 1) / 2是ceil的概念
            res[m++] = (pos -= 2); // 向左連續使用一半剩下的二站票
        
        
        printf("%d", res[0]);
        for (int i = 1; i < m; ++i)
            printf(" %d", res[i]);
        puts("");
    }

    return 0;
}