#include <bits/stdc++.h>
using namespace std;

#define maxn 1005


char s[maxn];
int SA[maxn]; // 排名為第i個的suffix起始位置
int Rank[maxn]; // 起始為i的suffix排名
int C[maxn];
int tempRank[maxn];
int idBy2nd[maxn]; // 依照第二個關鍵字排序後的index排序
int height[maxn]; // 排名第i的suffix與排名第i - 1的suffix最常共同前綴長度(LCP)
int n; // s len


/*
    倍增法如何成立?
    當已經完成長度為k的排序時
    此時rank[i]代表s[i ~ i + k - 1]的子字串排名
    現在要求長度為2k的子字串s[i ~ i + 2k - 1]排名
    觀察到該子字串的
    左半部是s[i ~ i + k - 1]，此排名在rank[i]
    右半部是s[i + k ~ i + 2k - 1]，此排名在rank[i + k]
    所以比較i、j開始長度為2k的兩個字串時，只需要比較
    1. rank[i] vs rank[j]
    2. rank[i + k] vs rank[j + k]

    此概念跟radix sort一樣
*/
void buildSA()
{
    int m = 256; // 總共字元及的大小

    memset(C, 0, sizeof(C));
    // k = 0
    // sort後的順序直接等於原始suffix的第一個字的ASCII
    for (int i = 0; i < n; ++i) ++C[Rank[i] = s[i]];
    // Counting sort的前綴和
    for (int i = 1; i <= m; ++i) C[i] += C[i - 1];
    // 將排序後的結果放回去SA裡面
    for (int i = n - 1; i >= 0; --i) SA[--C[Rank[i]]] = i;

    // 倍增法，用k長度的排序結果推出2k長度的排序結果
    for (int k = 1; k <= n; k <<= 1)
    {
        // 先根據第二個關鍵字排序

        // 將所有的suffix依照第二個關鍵字的大小，從小到大放到idBy2nd裡

        // idBy2nd的長度
        int len = 0;
        // 這些suffix沒有第二個關鍵字(長度不夠)
        for (int i = n - k; i < n; ++i) idBy2nd[len++] = i; // 直接排在最前面
        // 遍歷上一輪的SA
        // 在上一輪中，SA[i]是在全部字串中，長度k排名第i小的位置
        // 那麼在長度為2k的字串中，誰的後半部是SA[i]，誰的後半部排名就是第i小
        // 那個字串就是SA[i] - k (即前面多出k個字的字串，後面接著SA[i])
        for (int i = 0; i < n; ++i)
        {
            if (SA[i] >= k)
            {
                idBy2nd[len++] = SA[i] - k;
            }
        }

        // 再依照第一個關鍵字排序
        
        memset(C, 0, sizeof(C));
        for (int i = 0; i < n; ++i) C[Rank[i]]++;
        for (int i = 1; i <= m; ++i) C[i] += C[i - 1];
        // 倒過來遍歷，保證第一個關鍵字相同時，第二關鍵字小的在前面(stable sort)
        for (int i = n - 1; i >= 0; --i) SA[--C[Rank[idBy2nd[i]]]] = idBy2nd[i];

        // 更新rank
        tempRank[SA[0]] = 0;
        int pos = 0;
        for (int i = 1; i < n; ++i)
        {
            auto firstKey = [&](int i) { return Rank[i]; };
            auto secondKey = [&](int i) { return (i + k < n) ? Rank[i + k] : -1; };

            if (firstKey(SA[i]) == firstKey(SA[i - 1]) && secondKey(SA[i]) == secondKey(SA[i - 1]))
                tempRank[SA[i]] = pos;
            else
                tempRank[SA[i]] = ++pos;
        }

        swap(Rank, tempRank);
        m = pos;
        if (pos == n - 1) // 已經完全排好，就能提早結束
            break;
    }
}


/*
    定理:
    height[Rank[i]] >= height[Rank[i - 1]] - 1
*/
void buildHA()
{
    int LCP_len = 0;

    for (int i = 0; i < n; ++i)
    {
        if (Rank[i] == 0)
        {
            height[0] = 0;
            continue;
        }

        // 定理說，下一位LCP至少是LCP_len - 1
        if (LCP_len > 0) LCP_len--;

        // 拿到SA排名中前一的suffix
        int j = SA[Rank[i] - 1];

        // 從當前LCP_len開始往後比對
        while(i + LCP_len < n && j + LCP_len < n && s[i + LCP_len] == s[j + LCP_len])
            ++LCP_len;
        
        height[Rank[i]] = LCP_len;
    }
}


int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", &s);

        n = strlen(s);

        memset(SA, 0, sizeof(SA));
        memset(height, 0, sizeof(height));
        memset(Rank, 0, sizeof(Rank));

        buildSA();
        buildHA();

        // 利用height找重複出現過至少一次的substring中最長的長度
        int maxHeight = *max_element(height, height + n);

        if (maxHeight == 0)
            printf("No repetitions found!\n");
        else
        {
            for (int i = 0; i < n; ++i)
            {
                // 第一個LCP是maxHeight的，字典序一定最小
                if (height[i] == maxHeight)
                {
                    for (int j = 0; j < maxHeight; ++j)
                        printf("%c", s[SA[i] + j]);
                    // 算重複次數
                    int cnt = 1; // 記得會少算一次
                    while (height[i] == maxHeight)
                    {
                        ++cnt;
                        ++i;
                    }
                    printf(" %d\n", cnt);

                    break;
                }
            }
        }
    }

    return 0;
}