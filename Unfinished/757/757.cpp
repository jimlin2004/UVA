#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

struct Task
{
    int fish;
    int d;
    int index;
    bool operator < (const Task& other) const
    {
        if (fish == other.fish)
            return index > other.index;
        return fish < other.fish;
    }
};

int main()
{
    int n;
    int h;
    bool flag = false;;
    while (scanf("%d", &n) != EOF)
    {
        if (n == 0)
            break;
        scanf("%d", &h);
        priority_queue<Task> pq;
        int f[26] = {0};
        int d[26] = {0};
        int t[26] = {0};
        int ans[26] = {0};
        int tmpAns[26];
        int maxFish = -99999;
        h *= 12; //1單位5分鐘
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &f[i]);
        }
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &d[i]);
        }
        t[0] = 0;
        for (int i = 1; i < n; ++i)
        {
            scanf("%d", &t[i]);
        }
        memset(ans, 0, sizeof(ans));
        int totolTime = h;
        Task current;
        int currentIndex = 0;
        int time;
        int tmpFish;
        while (currentIndex < n)
        {
            pq = {};
            time = totolTime;
            for (int i = 0; i <= currentIndex; ++i)
            {
                pq.push({f[i], d[i], i});
                if (f[i] == 0) continue;
                time -= t[i];
            }
            tmpFish = 0;
            memset(tmpAns, 0, sizeof(tmpAns));
            while (time > 0 && !pq.empty())
            {
                current = pq.top();
                pq.pop();
                time -= 1;
                tmpAns[current.index] += 5;
                tmpFish += current.fish;
                current.fish -= current.d;
                if (current.fish <= 0) continue;
                pq.push({current.fish, current.d, current.index});
            }
            if (time > 0)
                tmpAns[0] += (time) * 5;
            if (tmpFish > maxFish)
            {
                maxFish = tmpFish;
                for (int i = 0; i <= currentIndex; ++i)
                {
                    ans[i] = tmpAns[i];
                }
            }
            currentIndex++;
        }
        if (flag)
            printf("\n");
        flag = true;
        printf("%d", ans[0]);
        for (int i = 1; i < n; ++i)
        {
            printf(", %d", ans[i]);
        }
        printf("\nNumber of fish expected: %d\n", maxFish);
    }
}