/*

題意:
組合遊戲，互相放一顆石頭，如果造成三顆連線就贏了
SG，細節看下方

SG(x) = mex{SG(y) | x -> y}
SG(0) = 0
SG(1) = 1
SG(2) = 1
SG(3) = mex{SG(0)} = 1
*/

#include <bits/stdc++.h>
using namespace std;

char s[205];

int SG[205];
bool vis[205];
int ans[205];
int ansCnt = 0;

void buildSG(int n)
{
    memset(SG, 0, sizeof(SG));
    SG[0] = 0;
    SG[1] = 1;
    SG[2] = 1;
    SG[3] = 1;

    // 枚舉所有n個格子時的next state
    // 然後用vis O(n)處理mex
    // 概念是放了一個X之後，前後兩格會變成危險格子，不能放

    // 枚舉有i個格子
    for (int i = 4; i <= n; ++i)
    {
        memset(vis, 0, sizeof(vis));

        // 枚舉在每一格放石頭，1-based
        for (int j = 1; j + 2 <= i; ++j)
        {
            // 當j <= 3時，左邊沒有地方可以放石頭
            // 0 ^ SG[i - j - 2] = SG[i - j - 2]
            // i - j - 2是剩下的空格數
            if (j <= 3) 
                vis[SG[i - j - 2]] = 1; 
            else // j > 3時，會分成左右兩邊安全空格，所以要做SG XOR
                vis[SG[j - 3] ^ SG[i - j - 2]] = 1;
        }

        for (int j = 0; j <= i; ++j)
        {
            if (!vis[j])
            {
                SG[i] = j;
                break;
            }
        }
    }
}

// 看看i放下去之後會不會直接造成3個XXX
inline bool checkWin(int i)
{
    return (strstr(s, "XXX") != NULL);
}

// 檢查是否有XX或X.X，此時對手會直接獲勝
inline bool hasThreat(int len)
{
    return (strstr(s, "XX") != NULL) || (strstr(s, "X.X") != NULL);
}

int getSGSum(int len)
{
    int sg_xor = 0;

    // 看安全的連續 . 有多長
    int curr_len = 0;

    for (int i = 0; i < len; ++i)
    {
        // 檢查第i格是否是安全的 . (前後兩格以內沒有 X )

        // 目前這段連續的 . 是不是還是安全的
        bool safe = true;
        if (s[i] != '.')
            safe = false;
        
        // 檢查前後兩格有沒有石頭了
        for (int d = 1; d <= 2; ++d)
        {
            // 往前看
            if (i - d >= 0 && s[i - d] == 'X')
                safe = false;
            // 往後看
            if (i + d < len && s[i + d] == 'X')
                safe = false;
        }

        if (safe)
            ++curr_len;
        else
        {
            // 這裡是組合遊戲的一局
            if (curr_len > 0)
            {
                // 把目前長度 SG xor 起來
                sg_xor ^= SG[curr_len];
                curr_len = 0;
            }
        }
    }

    // 邊界檢查(不漏掉邊界)
    if (curr_len > 0)
    {
        sg_xor ^= SG[curr_len];
    }

    return sg_xor;
}

int main()
{
    int T;
    scanf("%d", &T);

    buildSG(200);

    while (T--)
    {
        scanf("%s", s);

        int len = strlen(s);

        ansCnt = 0;

        for (int i = 0; i < len; ++i)
        {
            if (s[i] == '.')
            {
                // 放放看
                s[i] = 'X';
                if (checkWin(i))
                    ans[ansCnt++] = i + 1; // 答案要1-based
                // 如果對手沒有直接贏，就需要用SG找答案
                else if (!hasThreat(len))
                {
                    // 因為我放了i的位置導致版面SG XOR總和為0，此時對手必敗
                    if (getSGSum(len) == 0)
                    {
                        ans[ansCnt++] = i + 1;
                    }
                }
                // 回復原狀
                s[i] = '.';
            }
        }

        if (ansCnt == 0)
        {
            puts("LOSING\n"); // 注意這裡要多一個換行
        }
        else
        {
            puts("WINNING");
            printf("%d", ans[0]);
            for (int i = 1; i < ansCnt; ++i)
            {
                printf(" %d", ans[i]);
            }
            puts("");
        }
    }

    return 0;
}