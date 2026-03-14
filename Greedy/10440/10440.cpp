#include <bits/stdc++.h>
using namespace std;

/*
題意: 有m台車要過河，船每次能載最多n台車，船過去要t的時間，回來也要t的時間，求最少趟數時得最少時間
解法: 貪婪(不好想，也沒看到證明)
首先最少趟數一定是m / n + (m % n != 0)不用想，
但最少時間呢?
舉個例子
n = 2, m = 3, t = 10, 車來的時間是10/40/50
需要兩趟
可以選先滿載:
-> 70
或是先在一台
-> 60
有個想法是
反正最後如果都需要多一趟，那麼就優先將那一次載餘數個車早點用掉，這樣最有機會可以把這趟等船回來的
時間與後續等車的時間抵銷，讓最後一台車可以剛到就滿載出發

所以做法是從最後一台車開始n個n個滿載，只有第一趟只載m % n台車就先出發
可以得到最短時間
*/

int cars[1500];

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n, t, m;
        scanf("%d %d %d", &n, &t, &m);

        for (int i = 0; i < m; ++i)
            scanf("%d", &cars[i]);
        
        int trips = m / n + (m % n != 0);
        
        int remain = m % n;

        int totalTime = (remain == 0) ? 0 : cars[remain - 1] + 2 * t;
        int cnt = 0;
        for (int i = remain; i < m; ++i)
        {
            ++cnt;
            if (totalTime < cars[i])
            {
                totalTime = cars[i];    
            }
            if (cnt == n)
            {
                totalTime += 2 * t;
                cnt = 0;
            }
        }

        printf("%d %d\n", totalTime - t, trips);
    }

    return 0;
}