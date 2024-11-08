#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

/*
    這題是suffix array的題目
    此程式為網路實作版本
*/

#define maxn 40005

char str[maxn];
int Rank[maxn];
int SA[maxn]; //Suffix array
int cnt[maxn]; //count sort用
int n; //輸入字串長度
int height[maxn];
int temp[maxn];

void buildSA()
{
    static int maxAscii = 256 + 5;
    int mx = maxAscii;
    // 清空cnt[]
    for (int i = 0; i < mx; ++i)
        cnt[i] = 0;
    
    // counting sort，編號Rank[]、SA[]
    // counting sort第一步
    for(int i = 0; i < n; ++i)
    {
        Rank[i] = str[i];
        ++cnt[Rank[i]];
    }
    // counting sort第二步
    for (int i = 1; i < mx; ++i)
        cnt[i] += cnt[i - 1];
    // counting sort第三步
    for (int i = n - 1; i >= 0; --i)
        SA[--cnt[Rank[i]]] = i;
    
    // 倍增法排所有後綴字串(prefix-doubling algorithm) + counting sort
    for (int k = 1; k < n; k <<= 1)
    {
        // 一樣counting sort
        for (int i = 0; i < mx; ++i)
            cnt[i] = 0;
        for (int i = 0; i < n; ++i)
            ++cnt[Rank[i]];
        for (int i = 1; i < mx; ++i)
            cnt[i] += cnt[i - 1];
        int r = 0; //current rank
        for (int i = n - k; i < n; ++i)
            temp[r++] = i;
        for (int i = 0; i < n; ++i)
        {
            if (SA[i] >= k)
                temp[r++] = SA[i] - k;
        }

        // 計算這一回合的SA
        for (int i = n - 1; i >= 0; --i)
            SA[--cnt[Rank[temp[i]]]] = temp[i];
        
        // 計算這一回合的Rank
        temp[SA[0]] = r = 0;
        for (int i = 1; i < n; ++i)
        {
            if ((SA[i - 1] + k >= n) || (Rank[SA[i - 1]] != Rank[SA[i]]) || (Rank[SA[i - 1] + k] != Rank[SA[i] + k]))
                ++r;
            temp[SA[i]] = r;
        }
        for (int i = 0; i < n; ++i)
            Rank[i] = temp[i];
        
        mx = r + 1;
        if (mx == n)
            break;
    }
}

//build height[]
void buildHA()
{
    for (int i = 0; i < n; ++i)
        Rank[SA[i]] = i;
    int k = 0;
    for (int i = 0; i < n; ++i)
    {
        if (!Rank[i])
            continue;
        if (k)
            --k;
        while (str[i + k] == str[SA[Rank[i] - 1] + k])
            ++k;
        height[Rank[i]] = k;
    }
}

int main()
{
    int m;
    while (scanf("%d", &m) && m)
    {
        scanf("%s", str);
        n = (int)strlen(str);
        if (m == 1)
        {
            //如果m = 1，那最長符合題意的就是str整串本串
            printf("%d %d\n", n, 0);
            continue;
        }
        buildSA();
        buildHA();
        // 二分搜答案
        int l = 1, r = n;
        int mid;
        int res = -1, resPos;
        while (l <= r)
        {
            mid = (l + r) / 2;

            //檢查答案
            int c = 1, maxC = 0, maxPos = 0;
            for (int i = 0; i <= n; ++i)
            {
                if (i != n && height[i] >= mid)
                    ++c;
                else
                {
                    if (c > maxC)
                        maxC = c;
                    if (c >= m)
                    {
                        int j = i;
                        do
                        {
                            --j;
                            maxPos = max(maxPos, SA[j]);
                        } while (height[j] >= mid && j >= 0);
                    }
                    c = 1;
                }
            }

            if (maxC >= m)
            {
                l = mid + 1;
                res = mid;
                resPos = maxPos;
            }
            else
                r = mid - 1;
        }

        if (res == -1)
            puts("none");
        else
            printf("%d %d\n", res, resPos);
    }
    return 0;
}