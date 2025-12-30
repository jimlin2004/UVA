#include <bits/stdc++.h>
using namespace std;

/*
    一個腦筋急轉彎題
    可以觀察到螞蟻碰面轉向
    可以等同於螞蟻直接穿過彼此
    兩隻螞蟻交換要走的路程繼續計算 (這隻變那隻，那隻變這隻)
    (另一個性質是螞蟻的相對左右位置從始至終不會變(因為不會穿過彼此)，但這題用不到這個性質)

    所以得到結論:
        1. 最近距離就一定是max(每隻螞蟻往兩端中最小的距離)
            (因為每一隻走最小距離，仍然要等最久的那隻)
        2. 最長距離就一定是max(每隻螞蟻往兩端中最大的距離)
*/

int pos[1000005];

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int len, n;
        scanf("%d %d", &len, &n);

        int minRes = -1;
        int maxRes = -1;

        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &pos[i]);
        }

        for (int i = 0; i < n; ++i)
        {
            minRes = max(minRes, min(pos[i], len - pos[i]));
            maxRes = max(maxRes, max(pos[i], len - pos[i]));
        }

        printf("%d %d\n", minRes, maxRes);
    }

    return 0;
}