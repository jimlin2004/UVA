#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int pages[505];
int m, k;
long long totP;

//最多一人負責c頁的情況下，可以分幾份
int split(long long c)
{
    long long subtotal = 0; //當前那人分到幾頁
    int res = 1; //有幾份

    for (int i = 0; i < m; ++i)
    {
        if (subtotal + pages[i] <= c)
            subtotal += pages[i];
        else
        {
            ++res;
            subtotal = pages[i];
        }
    }

    return res;
}

bool needToSplit[505]; //要分不同份，也就是要輸出'/'
void printAns(long long c)
{
    //要字典序最小，所以必須greedy由右至左掃描
    long long subtotal = 0;
    memset(needToSplit, false, sizeof(needToSplit));

    int remain = k; //剩下的人
    for (int i = m - 1; i >= 0; --i)
    {
        //i + 1 < remain時代表剩下的組數一定要分，否則會有人沒有分到
        //每個人至少一本書
        if (subtotal + pages[i] > c || i + 1 < remain)
        {
            needToSplit[i] = true;
            --remain;
            subtotal = pages[i];
        }
        else
            subtotal += pages[i];
    }

    for (int i = 0; i < m - 1; ++i)
    {
        printf("%d ", pages[i]);
        if (needToSplit[i])
            printf("/ ");
    }
    printf("%d\n", pages[m - 1]);
}

/*
    用二分法對答案二分搜
    搜出最小的最多一人負責幾份，如此可以分配的最平均(由於同時抄寫，分的最平均代表完成的時間會最小)
    if (分出來的組數 < k) then 太大
    if (分出來的組數 > k) then 太小
    if (分出來的組數 = k) then 試試看可不可以更小
    二分用左閉右開，最後答案在 l
*/
void solve(int maxP)
{
    //[l, r)
    long long l = maxP, r = totP;
    long long mid;
    while (l < r)
    {
        mid = l + ((r - l) >> 1);
        if (split(mid) <= k)
            r = mid;
        else
            l = mid + 1;
    }

    printAns(l);
}

int main()
{
    int t;
    
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d %d", &m, &k);
        int maxP = -1;
        totP = 0;
        for (int i = 0; i < m; ++i)
        {
            scanf("%d", &pages[i]);
            maxP = max(maxP, pages[i]);
            totP += pages[i];
        }

        solve(maxP);
    }
    return 0;
}