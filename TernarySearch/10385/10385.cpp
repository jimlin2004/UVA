#include <bits/stdc++.h>
using namespace std;

/*
    比賽有跑步與騎腳踏車
    每個人的跑速、騎速不同
    所以想問能不能透過調整跑步、腳踏車路程
    讓最後一個人贏，且要贏越多越好

    可以想像這題是一個單峰函數且有最高點
    所以就是要搜出最高點
    用三分搜
*/

struct Player
{
    double running; // 跑速
    double cycling; // 騎速
};

Player players[25];
int N;
double total; // 總長

// 要算出最後一個人比最快的那個人快幾秒
double cal(double r)
{
    double bestSec = 1e8;
    double k = total - r;
    
    for (int i = 0; i < N - 1; ++i)
    {
        double sec = r / players[i].running + k / players[i].cycling;
        bestSec = min(bestSec, sec);
    }

    double lastPlayerSec = r / players[N - 1].running + k / players[N - 1].cycling;
    return bestSec - lastPlayerSec;
}

// double cal(double r)
// {
//     double res = 1e8;
//     double k = total - r;
    
//     double lastPlayerSec = r / players[N - 1].running + k / players[N - 1].cycling;
    
//     for (int i = 0; i < N - 1; ++i)
//     {
//         double sec = r / players[i].running + k / players[i].cycling;
//         res = min(res, sec - lastPlayerSec);
//     }

//     return res;
// }


int main()
{
    while (scanf("%lf", &total) != EOF)
    {

        scanf("%d", &N);

        for (int i = 0; i < N; ++i)
        {
            scanf("%lf %lf", &players[i].running, &players[i].cycling);
        }

        double l = 0, r = total;
        for (int i = 0; i < 100; ++i)
        {
            double lp = l + (r - l) / 3;
            double rp = r - (r - l) / 3;

            // 右邊比左邊大，所以斜率向右上，所以更新左端點
            if (cal(lp) <= cal(rp))
                l = lp;
            else
                r = rp;
        }
        
        double ans = cal(l);

        if (ans < 0.0)
            puts("The cheater cannot win.");
        else
        {
            printf("The cheater can win by %.0lf seconds with r = %.2lfkm and k = %.2lfkm.\n", ans * 3600, l, total - l);
        }
    }

    return 0;
}