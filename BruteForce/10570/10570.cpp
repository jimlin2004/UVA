#include <cstdio>
#include <algorithm>
using namespace std;

#define maxn 505

/*
    暴搜
    先將環形陣列變成兩倍長的陣列以方便計算
    同時所有的輸入數字先-1以方便後續計算
    同時每次將以第i個起頭，n個數字放入window[]用以計算最小變順時針的交換數

    舉例:
        2 3 1 4 -> 1 2 0 3
        變兩倍長的陣列後分別檢查->
        1 2 0 3 1 2 0 3
        x x x x
          x x x x
            x x x x
              x x x x
        1 2 0 3 -> 0 1 2 3 要交換2次
        2 0 3 1 -> 0 1 2 3 要交換3次
        0 3 1 2 -> 0 1 2 3 要交換2次
        3 1 2 0 -> 0 1 2 3 要交換1次
        所以目前最小是1次
        我們還要檢查逆時針，所以整個nums reverse
        3 0 2 1 3 0 2 1
        x x x x
          x x x x
            x x x x
              x x x x
        3 0 2 1 -> 0 1 2 3 要交換2次
        0 2 1 3 -> 0 1 2 3 要交換1次
        2 1 3 0 -> 0 1 2 3 要交換2次
        1 3 0 2 -> 0 1 2 3 要交換3次
        所以最小還是1次

    細節:
    如何快速交換
    例: 1 2 0 3 -> 0 1 2 3
    利用一個pos[]去紀錄0的位置、1的位置、2的、3的
    也就是
    index: 0 1 2 3
    pos[]: 2 0 1 3
    如此當window[i] != i可知i的位置不對
    window[i]要跟window[pos[i]]交換
    交換完後要記得更新pos[]
    如此可在O(n)完成一次的交換

    最後變O(n ^ 2)
*/

//為了方便，將圓形陣列轉為兩倍長的陣列，
//0 ~ (n - 1)是原本的，n ~ (2n - 1)是複製一遍的
int nums[maxn * 2];
int pos[maxn];
int window[maxn];

int solve(int n)
{
    int res = 0x3f3f3f3f;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            window[j] = nums[i + j];
            pos[window[j]] = j;
        }
        int cnt = 0;
        for (int j = 0; j < n; ++j)
        {
            if (window[j] != j)
            {
                swap(window[j], window[pos[j]]);
                //更新pos[]
                pos[window[pos[j]]] = pos[j];
                pos[j] = j;
                ++cnt;
            }
        }

        res = min(res, cnt);
    }

    return res;
}

int main()
{
    int n;
    while (scanf("%d", &n) && n)
    {
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &nums[i]);
            --nums[i];
            nums[i + n] = nums[i];
        }

        int res = solve(n);
        reverse(nums, nums + 2 * n);
        res = min(res, solve(n));
        printf("%d\n", res);
    }
    return 0;
}