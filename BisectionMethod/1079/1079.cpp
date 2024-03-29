#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

/*
    用next_permutation去得到所有飛機的排程可能
    再用bisecttion method去得出最小在那個排程的最小gap
    二分時用Greedy去試試看gap能不能讓所有飛機降落
*/

#define maxn 15

struct Segment
{
    int l, r;
};

Segment segments[maxn];
//存對應segments的index
int order[maxn];

bool check(double gap, int n)
{
    double curT = segments[order[0]].l;
    for (int i = 1; i < n; ++i)
    {
        if (curT + gap > segments[order[i]].r)
            return false;
        if (curT + gap < segments[order[i]].l)
            curT = segments[order[i]].l;
        else
            curT += gap;
    }
    return true;
}

/*
    試過整數型的二分
    但會有兩筆測資與udebug答案差1秒
*/
double solve(int n)
{
    double l = 0;
    double r = 1440 * 60;
    double mid;
    while (r - l >= 1e-2)
    {
        mid = (l + r) / 2;
        if (check(mid, n))
            l = mid;
        else
            r = mid;
    }
    return mid;
}

int main()
{
    int Case = 0;
    int n;
    while (scanf("%d", &n) && n)
    {
        for (int i = 0; i < n; ++i)
        {
            scanf("%d %d", &segments[i].l, &segments[i].r);
            segments[i].l *= 60;
            segments[i].r *= 60;
            order[i] = i;
        }
        double gap = -1.0;
        do
        {
            gap = max(gap, solve(n));
        } while (next_permutation(order, order + n));
        
        int t = (int)round(gap);

        printf("Case %d: ", ++Case);
        printf("%d:%02d\n", t / 60, t % 60);
    }
    return 0;
}