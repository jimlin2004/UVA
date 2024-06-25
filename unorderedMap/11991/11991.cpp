#include <cstdio>
#include <unordered_map>
#include <vector>
using namespace std;

//用unordered_map紀錄元素出現的每個位置
unordered_map<int, vector<int>> mp;

int main()
{
    int n, m;
    while (scanf("%d %d", &n, &m) != EOF)
    {
        mp.clear();
        int input;
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &input);
            mp[input].emplace_back(i);
        }

        int k, v;
        for (int i = 0; i < m; ++i)
        {
            scanf("%d %d", &k, &v);

            if (mp.find(v) == mp.end())
            {
                puts("0");
            }
            else if (mp[v].size() < k)
            {
                puts("0");
            }
            else
            {
                printf("%d\n", mp[v][k - 1]);
            }
        }
    }
    return 0;
}