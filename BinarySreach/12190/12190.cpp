/*
    x、y是用電量

    A = money(x + y)
    B = | money(x) - money(y) | -> money(x) = B +- money(y)

    x + y 已知 (可以直接換算)

    輸出 min(money(x), money(y))
*/
#include <bits/stdc++.h>
using namespace std;

// 將money轉成electric
int toElectric(int money)
{
    int electric = 0;
    if (money > 200) // 100 * 2
    {
        electric = 100;
        money -= 200;
    }
    else
    {
        electric += (money / 2);
        money = 0;
    }
    if (money > 29700) // 9900 * 3
    {
        electric = 10000;
        money -= 29700;
    }
    else
    {
        electric += (money / 3);
        money = 0;
    }
    if (money > 4950000) // 990000 * 5
    {
        electric = 1000000;
        money -= 4950000;
    }
    else
    {
        electric += (money / 5);
        money = 0;
    }
    
    electric += (money / 7);

    return electric;
}

// 將electric轉成money
int toMoney(int electric)
{
    int money = 0;
    if (electric > 1000000)
    {
        money += (electric - 1000000) * 7; 
        electric = 1000000;
    }
    if (electric > 10000)
    {
        money += (electric - 10000) * 5; 
        electric = 10000;
    }
    if (electric > 100)
    {
        money += (electric - 100) * 3; 
        electric = 100;
    }
    money += (electric * 2);

    return money;
}

int main()
{
    int A, B;
    while (scanf("%d %d", &A, &B))
    {
        if (A == 0 && B == 0)
            break;

        int electric_x_y = toElectric(A);
        // 一開始都是不可以的答案
        int l = -1, r = electric_x_y + 1;
        while (l + 1 < r) // 用二分搜搜出答案
        {
            int mid = (l + r) >> 1;
            int m1 = toMoney(mid);
            int m2 = toMoney(electric_x_y - mid);
            // 左半邊 m1 < m2，所以m1 - m2是負數，B >= 0，所以負數 <= B會是true
            if (m1 - m2 <= B)
                l = mid;
            else // 右半邊 m1 >= m2，m1 - m2會往右慢慢變大，直到 > B變成false
                r = mid;
        }
        printf("%d\n", min(toMoney(l), toMoney(electric_x_y - l)));
    }
    return 0;
}