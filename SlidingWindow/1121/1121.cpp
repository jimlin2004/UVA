#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

/*
    求連續區間相加起來 >= s且要求區間最短
    用雙指標(毛毛蟲滑動窗戶即可)
    O(n)
*/

#define maxn 100005

int A[maxn];

int main()
{
    int n, s;
    while (scanf("%d %d", &n, &s) != EOF)
    {
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &A[i]);
        }
        //雙指標
        int l = 0, r = 0;
        int res = 0x3f3f3f3f;
        //窗戶和
        int sum = 0;
        while (r < n)
        {
            //先往右擴
            while (r < n && sum < s)
            {
                sum += A[r];
                ++r;
            }
            //紀錄一下答案
            if (sum >= s)
            {
                res = min(res, r - l);
            }
            //嘗試左邊減少讓區間長度更小
            while (l <= r && sum >= s)
            {
                sum -= A[l];
                ++l;
                if (sum >= s) //紀錄一下答案
                {
                    res = min(res, r - l);
                }
            }
        }
        //這題有可能找不到區間>=s的，就回答0
        if (res == 0x3f3f3f3f)
            puts("0");
        else
            printf("%d\n", res);
    }
    return 0;
}