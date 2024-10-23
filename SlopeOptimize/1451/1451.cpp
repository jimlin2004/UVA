#include <cstdio>
#include <algorithm>
using namespace std;

#define maxn 100005
// #define maxn 1005

/*
    這題一開始看到可能以為是滑動窗戶之類的算法
    但事實上是考斜率的幾何題
    題意是要找出長度大於等於L的區間中是1的比例最大的區間
    比例越大越好，如果比例一樣則保留區間長度最短的答案

    如何轉為斜率問題，看推導1.png
    利用prefix sum可以找區間中共有幾個1
    則答案要的比例最大就是找出
    x軸為區間長度(點的個數，所以下面計算時是b - a + 1)
    y軸為1的個數
    那(y / x)其實就是斜率
    因此答案就是找斜率最大的區間

    這題數字範圍是1e5
    因此只能是O(n)或O(nlogn)的解法

    找斜率有一種單調隊列(deque)的優化方式，可以做到O(n)
    稱為"斜率優化"
    作法如下
    1. 看推導2.png
        當出現如x2這種點時，也就是出現x1->x2->x3的線呈現凸向上
        那x2就是可以被刪除的點，因為x1或x3會比x2好，x2就不需要考慮了
        所以在放新的點到單調隊列時，可以將所有的上凸點刪除
    2. 
        每次刪除凸上點後，放入新的點
        要掃一遍維護最好的答案
    3. 看推導3.png
        如何判斷是否出現上凸點，其實就是判斷斜率
        如圖中的點，當x1->d的斜率小於x2->d的斜率時，x2就是一個下凸點
        那x2就可以留著
        當斜率相同時，為共線，所以只要留新的點就行了

*/

char DNA[maxn];
//1的個數的prefix sum
int prefixSum[maxn];
//計算時用的queue，存的是可能可以作為答案區間左端點的座標x
int q[maxn];

//檢查是否為下凸點
inline int isConvex(int x1, int x2, int x3, int x4)
{
    //(x4 - x3 + 1)是因為要的是x3 ~ x4有幾個點個數，不是區間長度
    return (prefixSum[x2] - prefixSum[x1 - 1]) * (x4 - x3 + 1) - (prefixSum[x4] - prefixSum[x3 - 1]) * (x2 - x1 + 1);
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, L;
        scanf("%d %d", &n, &L);
        scanf("%s", DNA + 1);
        prefixSum[0] = 0;
        for (int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i - 1] + (DNA[i] - '0');
        
        //答案的left, right
        int l = 1, r = L;
        int qHead = 0, qTail = 0;
        //枚舉區間右端點
        for (int k = L; k <= n; ++k)
        {
            //刪除上凸的點
            while ((qTail - qHead > 1) && isConvex(q[qTail - 2], k - L, q[qTail - 1], k - L) >= 0)
                --qTail;
            //放入新的點
            q[qTail++] = k - L + 1;
            //找最好的答案，也就是刪除不是答案的點
            while ((qTail - qHead > 1) && isConvex(q[qHead], k, q[qHead + 1], k) <= 0)
                ++qHead;
            //更新最優解
            int res = isConvex(q[qHead], k, l, r);
            if (res > 0)
            {
                l = q[qHead];
                r = k;
            }
            else if ((res == 0) && (k - q[qHead] < r - l))
            {
                l = q[qHead];
                r = k;
            }
        }
        printf("%d %d\n", l, r);
    }
    return 0;
}