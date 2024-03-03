#include <cstdio>
#include <vector>
using namespace std;

/*
推導在推導.png
結論: 
    爆搜y, y in [k + 1, 2k]
    同時要檢查x = (ky) / (y - k), x是正整數
    => (y - k) 有沒有整除(ky)即可 
*/

vector<pair<int, int>> solutions;

void findSolutions(int k)
{
    solutions.clear();
    for (int y = k + 1; y <= 2 * k; ++y)
    {
        if ((k * y) % (y - k) == 0)
        {
            int x = (k * y) / (y - k);
            if (x >= y)
            {
                solutions.push_back({x, y});
            }
        }
    }
}

int main()
{
    int k;
    while (scanf("%d", &k) != EOF)
    {
        findSolutions(k);
        printf("%u\n", solutions.size());
        for (pair<int, int>& sol: solutions)
        {
            printf("1/%d = 1/%d + 1/%d\n", k, sol.first, sol.second);
        }
    }
    return 0;
}