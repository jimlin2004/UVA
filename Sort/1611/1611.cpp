#include <bits/stdc++.h>
using namespace std;


/*
    比較不一樣的題目
    每次只能搬移[l, r](偶數區間)，前一半後一半交換，求搬移過程
    但重要的是，不要求最少步數，只要求搬移次數小於531441次
    資料數 n < 10000
    所以可能有非常多種方式可以過這題，只是要確定不會超過搬移次數
    答案也會有非常多種(測資特判題)
    一種解法是利用selection sort(每次目標讓一個nums[k] = i回到i)
    可以確定搬移次數 <= 2n 次(可通過規定)
    方法是:
    如果已經就定位，完全不用搬移
    case 1: i + 2 * (pos - i) - 1 <= n
        這樣的情況可以一步將i搬回i
        (參考case1.png)
    case 2: i + 2 * (pos - i) - 1 > n 且 [i, j]個數是偶數
        這樣的情況需要兩步
        (參考case2.png)
    case 3: i + 2 * (pos - i) - 1 > n 且 [i, j]個數是奇數
        這樣的情況需要兩步
        (參考case3.png)
    整體過程就是不斷模擬
*/


#define maxn 10005

int nums[maxn];


// 直接模擬[l, r]前一半與後一半交換
void change(int l, int r)
{
    for (int i = l, j = (int)ceil((l + r) / 2.0); j <= r; ++i, ++j)
    {
        swap(nums[i], nums[j]);
    }
}


int main()
{
    int T;
    scanf("%d", &T);
    int n;
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &nums[i]);
        // 記錄過程
        vector<pair<int, int>> history;

        // 目標，每次讓i就定位
        for (int i = 1; i <= n; ++i)
        {
            int pos; // 現在i在哪裡
            for (int j = i; j <= n; ++j)
            {
                if (nums[j] == i)
                {
                    pos = j;
                    break;
                }
            }

            if (pos == i) // 已經就定位，不用調
                continue;
            
            // 開始搬
            if (i + 2 * (pos - i) - 1 <= n) // case 1
            {
                history.emplace_back(i, i + 2 * (pos - i) - 1);
                change(i, i + 2 * (pos - i) - 1);
            }
            else // 這裡的都需要兩次才能定位
            {
                if ((pos - i + 1) % 2 == 0) // case 2
                {
                    history.emplace_back(i, pos);
                    change(i, pos);
                }
                else // case 3
                {
                    history.emplace_back(i + 1, pos);
                    change(i + 1, pos);
                }

                --i; // 因為i還沒就定位，還需要一次搬移
            }
        }

        printf("%d\n", history.size());
        for (auto& record: history)
            printf("%d %d\n", record.first, record.second);
    }

    return 0;
}