#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

/*
    sort就完了
    Key: 小的配給小的，如此差距會最小
*/

vector<int> heads;
vector<int> knights;

int main()
{
    int n, m;
    while (scanf("%d %d", &n, &m) && (n != 0 && m != 0))
    {
        heads.clear();
        knights.clear();

        int height;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &height);
            heads.emplace_back(height);
        }
        for (int i = 0; i < m; ++i)
        {
            scanf("%d", &height);
            knights.emplace_back(height);
        }

        sort(heads.begin(), heads.end());
        sort(knights.begin(), knights.end());

        int res = 0;

        int knightIndex = 0;
        bool ok = true;
        for (int i = 0; i < n; ++i)
        {
            if (knightIndex >= m)
            {
                ok = false;
                break;
            }
            while (knights[knightIndex] < heads[i])
                ++knightIndex;
            res += knights[knightIndex];
            ++knightIndex;
        }
        if (ok)
            printf("%d\n", res);
        else
            puts("Loowater is doomed!");
    }
    return 0;
}