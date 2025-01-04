#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

#define maxn 10005

/*
    這題就是LIS
    在可以接上去的垃圾中選長度最長的
    LIS需要O(n ^ 2)
*/

struct Garbage
{
    int row, col;
    int id;

    // 可以接 這個關係當作<用
    bool operator < (const Garbage& other) const
    {
        return (this->row <= other.row) && (this->col <= other.col);
    }
};

Garbage A[maxn];
int LIS[maxn];
// 存那條LIS當前的長度
int cnt[maxn];
int path[maxn];
int n, m;

int needToRemoveLast;

void printPath(int index)
{
    if (index == -1)
        return;
    printPath(path[index]);
    printf(" %d", A[index].id);
}

int main()
{
    int Case = 0;
    while (scanf("%d %d", &n, &m))
    {
        if (n < 0 && m < 0)
            break;
        memset(LIS, 0, sizeof(LIS));
        memset(cnt, 0, sizeof(cnt));
        memset(path, -1, sizeof(path));
        int r, c;
        int len = 0;
        while (scanf("%d %d", &r, &c) && r && c)
        {
            A[len].row = r;
            A[len].col = c;
            A[len].id = (r - 1) * m + c;
            ++len;
        }

        // 用id去排序，也就是創造LIS可以接的機會
        // 否則會錯
        sort(A, A + len, [=](Garbage& a, Garbage& b) {
            return a.id < b.id;
        });

        needToRemoveLast = 0; // 有沒有多創造一個垃圾在最後一格
        // 如果最後一格沒有垃圾就創造一個
        // 主要是為了方便LIS紀錄最大的那個路徑以及知道有幾種
        if (A[len - 1].row != n || A[len - 1].col != m)
        {
            A[len].row = n;
            A[len].col = m;
            A[len].id = n * m;
            ++len;
            needToRemoveLast = 1;
        }

        for (int i = 0; i < len; ++i)
        {
            LIS[i] = 0;
            cnt[i] = 1;
            path[i] = -1;
            for (int j = 0; j < i; ++j)
            {
                if (A[j] < A[i])
                {
                    if (LIS[j] > LIS[i])
                    {
                        LIS[i] = LIS[j];
                        cnt[i] = cnt[j];
                        path[i] = j;
                    }
                    else if (LIS[j] == LIS[i]) // 題目要求，需要知道有幾種
                    {
                        cnt[i] += cnt[j];
                    }
                }
            }
            ++LIS[i];
        }

        printf("CASE#%d: %d %d", ++Case, LIS[len - 1] - needToRemoveLast, cnt[len - 1]);
        if (needToRemoveLast == 0) // 原本在最後一格有垃圾
            printPath(len - 1);
        else
            printPath(path[len - 1]); // 最後一格沒有垃圾，不要印出最後一格
        puts("");
    }
    return 0;
}