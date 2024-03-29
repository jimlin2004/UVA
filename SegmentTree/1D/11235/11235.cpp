#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

/*
    可參考 範例.png

    由於題目給的是上升序列，所以可以有切割的方法
    index:         1  2  3  4  5  6  7  8  9 10
    values[]:     -1 -1  1  1  1  1  3 10 10 10

    維護一個type[]去紀錄values[i]是第幾種出現的數字
    type[]:        0  0  1  1  1  1  2  3  3  3
    並且多一個陣列cnt[]去紀錄每個type的數量
    index:         0  1  2  3
    cnt[]:         2  4  1  3

    如此當詢問的區間ql, qr符合(type[ql] == type[qr])
    此時代表[ql ~ qr]都是同一種數字，
    此時可以直接輸出(qr - ql + 1)即為答案

    但運氣總是不好，可能ql~qr會將兩端點的連續相同數字打斷
    所以要做不同處理
    準備兩個陣列
    index:         1  2  3  4  5  6  7  8  9 10
    leftBound[]:   1  1  3  3  3  3  7  8  8  8
    rightBound[]:  2  2  6  6  6  6  7 10 10 10
    
    leftBound[i]代表type[i]那一種最左邊那個元素的index
    rightBound[i]代表type[i]那一種最右邊那個元素的index

    如此當詢問[ql ~ qr]
    分三段處理(左，中，右)
    左段: 
        最左邊的端點type是type[ql]，
        在[ql, qr]的範圍中同為type[ql]的有(rightBound[ql] - ql + 1)個
        O(1)
    右段:
        最右邊的端點type是type[qr]，
        在[ql, qr]的範圍中同為type[qr]的有(qr - leftBound[qr] + 1)個
        O(1)
    中段([rightBound[ql] + 1 ~ leftBound[qr] - 1]):
        由於中段可能有很多種不同的連續相同type子區段，
        如果直接一個個數會需要O(n)的時間
        由於中段是我們已經去掉左右段的區間，
        所以不會有被切斷的連續相同type子區段
        此時就可以用sparse table或segment tree去維護
        [rightBound[ql] + 1 ~ leftBound[qr] - 1]中cnt[]的最大值
    最後三段(左、中、右)合併答案時選三段中最大的即可

    總結:
        1. 
            若type[ql] == type[qr]代表是一個連續相同type子區段
            直接輸出(qr - ql + 1)即為答案
        2.
            若type[ql] != type[qr]則分三段
            左段: 有(rightBound[ql] - ql + 1)個
            右段: 有(qr - leftBound[qr] + 1)個
            中段: 用segment tree或sparse table求max cnt[[rightBound[ql] + 1 ~ leftBound[qr] - 1]]
            最後輸出三段最大值即為答案
*/

#define maxn 100005

int values[maxn];
int st[maxn * 4];
int type[maxn];
//index對應type，cnt[type]是該type有幾個
int cnt[maxn];
int leftBound[maxn];
int rightBound[maxn];

void build(int index, int l, int r)
{
    if (l == r)
    {
        st[index] = cnt[type[l]];
        return;
    }
    int mid = l + ((r - l) >> 1);
    build(index * 2, l, mid);
    build(index * 2 + 1, mid + 1, r);
    st[index] = max(st[index * 2], st[index * 2 + 1]);
}

int query(int index, int l, int r, int ql, int qr)
{
    if (ql <= l && qr >= r)
        return st[index];
    int mid = l + ((r - l) >> 1);
    int res = -0x3f3f3f3f;
    if (ql <= mid)
        res = max(res, query(index * 2, l, mid, ql, qr));
    if (mid < qr)
        res = max(res, query(index * 2 + 1, mid + 1, r, ql, qr));
    return res;
}

int main()
{
    int n, q;
    while (scanf("%d", &n) && n)
    {
        scanf("%d", &q);
        
        int prev = -0x3f3f3f3f;
        int typeLast = -1;
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &values[i]);
            if (values[i] != prev)
            {
                ++typeLast;
                cnt[typeLast] = 1;
                type[i] = typeLast;
            }
            else
            {
                ++cnt[typeLast];
                type[i] = type[i - 1];
            }
            prev = values[i];
        }

        leftBound[1] = 1;
        rightBound[n] = n;
        for (int i = 2, j = n - 1; i <= n; ++i, --j)
        {
            if (type[i] == type[i - 1])
                leftBound[i] = leftBound[i - 1];
            else
                leftBound[i] = i;
            
            if (type[j] == type[j + 1])
                rightBound[j] = rightBound[j + 1];
            else
                rightBound[j] = j;
        }

        build(1, 1, n);

        int ql, qr;
        while (q--)
        {
            scanf("%d %d", &ql, &qr);
            //代表詢問的區間都是同一個數
            if (type[ql] == type[qr])
            {
                printf("%d\n", qr - ql + 1);
            }
            //要分段討論
            else
            {
                int leftSide = rightBound[ql] - ql + 1;
                int rightSide = qr - leftBound[qr] + 1;
                int mid = query(1, 1, n, rightBound[ql] + 1, leftBound[qr] - 1);
                printf("%d\n", max({leftSide, rightSide, mid}));
            }
        }
    }
    return 0;
}