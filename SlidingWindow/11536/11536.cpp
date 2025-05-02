#include <bits/stdc++.h>
using namespace std;

/*

    一個簡單的滑動窗戶題
    找到涵蓋1 ~ k的窗戶後
    嘗試縮L使窗戶變短
    過程中維護答案即可

*/


#define maxn 1000005
#define maxk 2000

int arr[maxn];
int cnt[maxk];

int main()
{
    int Case = 0;
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, m, k;
        scanf("%d %d %d", &n, &m, &k);

        arr[1] = 1;
        arr[2] = 2;
        arr[3] = 3;
        for (int i = 4; i <= n; ++i)
        {
            arr[i] = (arr[i - 3] + arr[i - 2] + arr[i - 1]) % m + 1;
        }

        memset(cnt, 0, sizeof(cnt));
    
        int res = 0x3f3f3f3f;

        int found = 0; // 計算當前窗戶涵蓋多少1 ~ k(重複不算)
        int l = 1, r = 1;
        while (r <= n)
        {
            if (cnt[arr[r]] == 0) // 有新的 1 ~ k
            {
                if (1 <= arr[r] && arr[r] <= k)
                {
                    ++found;
                }
            }
            ++cnt[arr[r]];
            while ((found == k) && (l <= r)) // 涵蓋1 ~ k了
            {
                res = min(res, r - l + 1);
                if (1 <= arr[l] && arr[l] <= k && cnt[arr[l]] == 1)
                {
                    break;
                }
                --cnt[arr[l]];
                ++l;
            }
            ++r;
        }

        printf("Case %d: ", ++Case);
        if (res == 0x3f3f3f3f)
            puts("sequence nai");
        else
            printf("%d\n", res);
    }

    return 0;
}