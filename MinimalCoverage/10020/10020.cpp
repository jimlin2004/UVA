#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

struct Seg
{
    int left, right;
    bool operator < (const Seg& other)
    {
        if (left == other.left)
            return right > other.right;
        return left < other.left;
    }
};

int main()
{
    int k;
    int left, right;
    int M;
    bool firstTime = false;
    scanf("%d", &k);
    while (k--)
    {
        vector<Seg> segs;
        getchar();
        scanf("%d", &M);
        while (scanf("%d %d", &left, &right) && (left || right))
        {
            segs.push_back({left, right});
        }
        sort(segs.begin(), segs.end());

        vector<pair<int, int>> ans;
        int L = 0, R = -1;
        while (R < M)
        {
            int tmpLeft = -50001;
            for (int i = 0; segs[i].left <= L && i < segs.size(); ++i)
            {
                if (segs[i].right > R)
                {
                    R = segs[i].right;
                    tmpLeft = segs[i].left;
                }
            }
            if (tmpLeft == -50001) break;
            ans.push_back({tmpLeft, R});
            L = R;
        }

        if (firstTime)
            printf("\n");
        firstTime = true;
        if (R >= M)
        {
            printf("%d\n", ans.size());
            for (pair<int, int> p: ans)
            {
                printf("%d %d\n", p.first, p.second);
            }
        }
        else
            printf("0\n");
        
        segs.clear();
        ans.clear();
    }
    return 0;
}