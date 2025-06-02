#include <bits/stdc++.h>
using namespace std;

/*
    博弈論的組合遊戲
    這題其實石頭數量不是重點，而是位置與奇偶性
    遊戲每次從i拿走一顆石頭，放一顆石頭到j、k(可以同一堆)
    石頭數量其實是不斷增加的
    而遊戲結束於石頭只剩下第n堆，此時不能操作者輸
    所以遊戲的重點其實是位置而不是數量

    一堆石頭中如果是偶數顆，此時對手只要鏡像操作就不會改變遊戲的奇偶性，
    所以偶數石頭對於遊戲是完全沒有貢獻度
    重點在於奇數的石頭堆

    這題要轉化問題 (參考推導.png)
    原本石頭堆 1      2      3        ...  n - 1  n
    變成剩下   n - 1  n - 2  n - 3         1      0 個石頭的遊戲
    這是源自於將 第i堆石頭我們可以看成玩SG(n - i)的子遊戲
    在SG(n - i)操作時會與SG(n - j)、SG(n - k) (其中i < j <= k) 有關
    也就是說你現在有n - i顆石頭，拿掉一顆後會變成有n - j以及n - k顆石頭兩個小遊戲

    為何這樣轉化合理？
    因為你只能把石頭從 i 堆移動到更右邊的 j 和 k 堆。
    這意味著石頭會從左往右「往更高編號的堆」不斷流動。
    把狀態想成一排石頭，原本第 i 堆有 n - i 顆石頭，拿掉一顆後會拆分成兩個更往右的堆（n - j 和 n - k）分別多一顆石頭。

    回顧SG(x) = mex{SG(y) | y是x可以轉移到的狀態}
    所以這題處理時SG(x)用枚舉的(O(n ^ 2))，枚舉SG(i) = mex{所有SG(j) ^ SG(k)}
*/

#define maxn 30

int piles[maxn];
int SG[maxn];
int vis[1005]; // 其實不用開這麼大，只要保證XOR不超過即可

// 其實getSG可以只算一次，所有位置，答案不變
void getSG(int n)
{
    memset(vis, -1, sizeof(vis));

    // SG邊界狀態，剩餘0顆石頭自然先手必輸
    // 對應回本題，只剩第n堆時遊戲先手必輸
    SG[0] = 0;

    // 枚舉SG(i)
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            for (int k = 0; k <= j; ++k)
            {
                vis[SG[j] ^ SG[k]] = i; // 這裡用i可以省掉memset
            }
        }
        
        int mex = 0;
        while (vis[mex] == i)
            ++mex;
        
        SG[i] = mex;
    }
}

int main()
{
    int n;
    int tc = 0;
    while (scanf("%d", &n) && n)
    {
        for (int i = 1; i <= n; ++i)
            scanf("%d", &piles[i]);
        
        getSG(n);

        int res = 0;

        for (int i = 1; i <= n; ++i)
        {
            if (piles[i] & 1) // 只考慮奇數石堆
                res ^= SG[n - i];
        }

        if (res == 0)
            printf("Game %d: -1 -1 -1\n", ++tc);
        else
        {
            bool ok = false;
            // 暴力枚舉第一步的操作
            for (int i = 1; i <= n; ++i)
            {
                if (piles[i] == 0)
                    continue;
                for (int j = i + 1; j <= n; ++j)
                {
                    for (int k = j; k <= n; ++k)
                    {
                        // 第i堆拿走放到j、k變成SG(n - i) ^ SG(n - j) ^ SG(n - k)
                        if ((SG[n - i] ^ SG[n - j] ^ SG[n - k]) == res)
                        {
                            printf("Game %d: %d %d %d\n", ++tc, i - 1, j - 1, k - 1); // -1是因為題目是從0開始
                            ok = true;
                            break;
                        }
                    }
                    if (ok)
                        break;
                }
                if (ok)
                    break;
            }
        }
    }

    return 0;
}