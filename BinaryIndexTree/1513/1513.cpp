#include <cstdio>
#include <cstring>
using namespace std;

#define MAXN 100005
#define lowbit(x) ((x) & (-x))

/*
核心概念:
    用pos[]去紀錄每個電影的位置
    即一開始
    pos[]:
        index:      1 2 3 4 5 6 -> 電影編號
        pos[index]: 6 5 4 3 2 1 -> 在橫的stack中的index
                                            top
        相當於一個橫的 stack: [6, 5, 4, 3, 2, 1]
        用一個陣列A:          [1, 1, 1, 1, 1, 1]
        可以計算出3號電影以下(含自己)有4個電影(由上列陣列計算A[1 ~ pos[3]]的加總得出)
        所以對此題問的答案是n - 4(從top數過來是第幾個)
    假設搬移3號電影
                                    top
    在橫的stack中: [6, 5, 4,  , 2, 1, 3] 原3號電影位置留空
    陣列A:         [1, 1, 1, 0, 1, 1, 1]
    此時3號電影以下(含自己)有6個電影(由A[1 ~ pos[3]]的加總得出)
    此時pos[]:
        index:      1 2 3 4 5 6
        pos[index]: 6 5 7 3 2 1
    若下次依舊問3號電影則回答 n - 6(即 n - A[1 ~ pos[3]])

    所以整體是在處理前綴和 + 單點修改
    每次搬移時該點陣列A的陣列值 - 1 (即從1改成0)
    且新的A[topIndex] + 1 (即從0改成1)
    topIndex++
    用BIT去維護前綴和與單點修改
    達到每次查詢 O(log n)，單點修改 O(log n)
    詢問m次，整體複雜度 O(m log n) (不含初始化pos[]，BIT的複雜度)
    BIT需要n + m個空間
*/

int BIT[2 * MAXN];
int pos[MAXN]; // pos[index] -> index是電影編號，pos[index]是電影現在的位置

void add(int index, int val)
{
    while (index <= 2 * MAXN)
    {
        BIT[index] += val;
        index += lowbit(index);
    }
}

int prefixSum(int index)
{
    int res = 0;
    while (index > 0)
    {
        res += BIT[index];
        index -= lowbit(index);
    }
    return res;
}

int main()
{
    int t;
    int n, m;
    scanf("%d", &t);
    while (t--)
    {
        memset(BIT, 0, sizeof(BIT));

        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; ++i)
        {
            pos[i] = n - i + 1; //數字index大的是頭
            add(pos[i], 1); //一開始每個都是 1
        }

        int target;
        int topIndex = n;
        for (int i = 1; i <= m; ++i)
        {
            scanf("%d", &target);
            printf("%d", n - prefixSum(pos[target]));
            if (i == m)
                puts("");
            else
                putchar(' ');
            add(pos[target], -1);
            pos[target] = ++topIndex;
            add(pos[target], 1);
        }
    }
    return 0;
}