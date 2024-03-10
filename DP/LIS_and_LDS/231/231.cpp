#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

/*
題目很長: 有一個導彈系統，當它攔截一個導彈後，下一次就不能超過這個高度，
        求最多攔截幾個

也就是LDS
*/

int main()
{
    vector<int> LDS;
    int height;
    int Case = 0;
    bool first = true;
    while (scanf("%d", &height) && height != -1)
    {
        LDS.clear();
        LDS.emplace_back(height);
        while (scanf("%d", &height) && height != -1)
        {
            if (LDS.back() >= height)
                LDS.emplace_back(height);
            else
                *lower_bound(LDS.begin(), LDS.end(), height, [](int a, int b) {
                    return a >= b;
                }) = height;
        }

        if (first)
            first = false;
        else
            puts("");

        printf("Test #%d:\n", ++Case);
        printf("  maximum possible interceptions: %d\n", LDS.size());
    }
    return 0;
}