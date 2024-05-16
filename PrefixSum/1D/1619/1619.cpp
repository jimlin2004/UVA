#include <cstdio>
#include <cstring>

#define maxn 100005

/*
    概念就是既然只有正數
    所以問題轉成
    枚舉nums[i]作為區間最小的時候，最大可以到多少
    然後再取值最大，區間最短最左邊的(老師的測資要求)即可

    值要最大，最小值已經固定，且不會有負值，
    所以就是看以nums[i]為最小值最左邊、最右邊能到多長(越長代表算起來會更大)

    問題變成如何比較有效率的找最左邊最右邊
    其實我試過一個個找(也就是每次O(n))
    是有機會過得，
    但其實可以觀察到
    當由左往右建left[]時
    其實不用一個個搜
    發現在找left[i]時可以利用left[i - 1]之前算過的結果跳大步一點
    也就是當i - 1的left比我還要大，此時代表left[i - 1] ~ (i - 1)之間的所有數字都不可能比nums[i]小
    否則之前的left[i - 1]就算錯了
    此時我們不必再檢查那些一定比我大的數字，直接跳到left[i - 1] - 1繼續找下去即可

    right[]也是同理，但記得是要由右往左建

    最後枚舉就能找到答案
    實際的left[]，right[]建法參考下方
*/

long long nums[maxn];
long long prefixSum[maxn];
int left[maxn];
int right[maxn];

//枚舉以nums[i]作為最小值時，最大可以到多少
void solve(int n)
{
    /*
        不能用
        long long res = -0x3f3f3f3f;
        int resL = -1;
        int resR = -1;
        以防
        6
        0 0 0 0 0 0
        輸出
        0
        1 6
        而不是
        0
        1 1
    */

    long long res = 0;
    int resL = 1;
    int resR = 1;

    for (int i = 1; i <= n; ++i)
    {
        long long total = nums[i] * (prefixSum[right[i]] - prefixSum[left[i] - 1]);
        if (total > res)
        {
            res = total;
            resL = left[i];
            resR = right[i];
        }
        else if (total == res)
        {
            //找最短且最左邊的
            if ((right[i] - left[i]) < (resR - resL))
            {
                res = total;
                resL = left[i];
                resR = right[i];
            }
            else if ((right[i] - left[i]) == (resR - resL))
            {
                if (left[i] < resL)
                {
                    res = total;
                    resL = left[i];
                    resR = right[i];
                }
            }
        }
    }

    printf("%lld\n", res);
    printf("%d %d\n", resL, resR);
}

int main()
{
    bool first = true;
    int n;
    while (scanf("%d", &n) != EOF)
    {
        for (int i = 1; i <= n; ++i)
        {
            scanf("%lld", &nums[i]);
            prefixSum[i] = prefixSum[i - 1] + nums[i];
            left[i] = i;
            right[i] = i;
        }

        //為了建立left、right時的邊界條件
        nums[0] = -1;
        nums[n + 1] = -1;

        //建立left array(由左至右)
        for (int i = 1; i <= n; ++i)
        {
            while (nums[left[i] - 1] >= nums[i])
                left[i] = left[left[i] - 1];
        }

        //建立right array(由右至左)
        for (int i = n; i >= 1; --i)
        {
            while (nums[right[i] + 1] >= nums[i])
                right[i] = right[right[i] + 1];
        }

        if (first)
            first = false;
        else 
            puts("");
        
        solve(n);
    }
    return 0;
}