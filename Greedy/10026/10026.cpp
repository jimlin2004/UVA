#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

/*
Greedy, sorting
觀察:
    對於工作a(t_a, f_a)、b(t_b, f_b)
    ab與ba的順序只影響a, b本身，對其他工作沒有改變
    所以關鍵在排序a, b
    如果ab比較好，此時
    t_a * f_b <= t_b * f_a
    同除f_a * f_b
    -> (t_a / f_a) <= (t_b / f_b)

    再來考慮工作超過2個時的情況
    有m + 1個工作
    設1~m是最佳順序，第(k + 1)個工作可以插入到任何位子
    因此現在的任務序列是(1 ~ k), (k + 1), (((k + 1) + 1) ~ m)
    由於(1~m)是最佳順序，(1~k)未改變，所以(1~k)亦為最佳
    子任務剩下(k + 1), (((k + 1) + 1) ~ m)，
    將後者看作一個工作
    這樣問題回到ab or ba
    同理，故成立
*/

const double eps = 1e-9;

struct Job
{
    int number;
    double ratio;

    bool operator < (const Job& other) const
    {
        if (abs(ratio - other.ratio) < eps)
            return this->number < other.number;
        return ratio < other.ratio;
    }
};

Job jobs[1005];

int main()
{
    int t;
    scanf("%d", &t);
    bool first = true;
    while (t--)
    {
        getchar(); //for \n
        int n;
        scanf("%d", &n);
        int time, fine;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d %d", &time, &fine);
            jobs[i].ratio = (time * 1.0) / fine;
            jobs[i].number = i + 1;
        }
        sort(jobs, jobs + n);
        if (first)
            first = false;
        else
            puts("");
        printf("%d", jobs[0].number);
        for (int i = 1; i < n; ++i)
            printf(" %d", jobs[i].number);
        puts("");
    }
    return 0;
}