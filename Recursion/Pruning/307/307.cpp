#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

// 考遞迴加上很多技巧的剪枝加速，另外vector太慢，不會過
// 時間很緊，UVA 2.6 ~ 2.8秒

//1005題目沒講，又是試出來的數字
#define maxn 1005

//木棒長度
// vector<int> sticks; //vector太慢
int sticks[maxn];
//標記木棒有沒有被用過
// vector<int> used; //vector太慢，知識點: vector<int>比vector<bool>快很多
bool used[maxn];
int maxLen;
int n;

bool solve(int i, int len, int remain)
{
    if (len == maxLen)
    {
        //組合出長度為maxLen的stick，所以remain - maxLen
        remain -= maxLen;
        len = i = 0;
    }
    //當remain = 0代表全部用完了，且全部可以個別組合為長度為maxLen的stick，那就找到了
    if (remain == 0)
        return true;
    //嘗試後面有沒有stick可以和之前的stick合成，目標是合出長度為maxLen的stick
    for (int j = i; j < n; ++j)
    {
        if (used[j]) //用過就不能再用
            continue;
        //如果上一個stick的長度跟我一樣但上一個沒有被用到，那我也一定不會被用
        //否則上一個stick會先被用
        if (sticks[j] == sticks[j - 1] && !used[j - 1])
            continue;
        //嘗試去接成maxLen
        if (sticks[j] + len <= maxLen)
        {
            //我拿去接接看
            used[j] = true;
            //如果我接上去且我之後的人也能完成，那就能夠完成各自接成長度為maxLen的sticks
            if (solve(j + 1, len + sticks[j], remain))
                return true;
            //我接上去不能完成，那我就標記回沒用過
            used[j] = false;
            //到這裡且當len == 0代表其他sticks沒辦法組成長度為maxLen的stick，那就提前回傳false
            if (len == 0)
                return false;
        }
    }
    return false;
}

int main()
{
    while (scanf("%d", &n) && n)
    {
        // sticks.clear();
        int totalLen = 0;

        int len;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &len);
            // sticks.emplace_back(len);
            sticks[i] = len;
            totalLen += len;
        }

        //由大到小排序，可以增加遞迴搜尋速度
        sort(sticks, sticks + n, [](const int a, const int b) {
            return a > b;
        });
        // sort(sticks.begin(), sticks.end(), [](const int a, const int b) {
            // return a > b;
        // });

        bool ok = false;
        //枚舉答案，答案至少為sticks最長的
        for (maxLen = sticks[0]; maxLen <= totalLen / 2; ++maxLen)
        {
            //答案一定可以整除total len
            if (totalLen % maxLen != 0)
                continue;
            // used.assign(n + 5, false);
            memset(used, 0, sizeof(used));
            if (solve(0, 0, totalLen))
            {
                printf("%d\n", maxLen);
                ok = true;
                break;
            }
        }
        //如果上面找不到，答案就是全部sticks長度加起來
        //即所有木棒都合成一根
        if (!ok)
            printf("%d\n", totalLen);
    }
    return 0;
}