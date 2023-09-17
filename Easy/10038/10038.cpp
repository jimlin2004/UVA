#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    int n;
    vector<int> diff;
    bool flag;
    int size;
    int prev, curr;
    while (scanf("%d", &n) != EOF)
    {
        diff.clear();
        flag = false;
        scanf("%d", &prev);
        if (n == 1)
        {
            puts("Jolly");
            continue;
        }
        for (int i = 1; i < n; ++i)
        {
            scanf("%d", &curr);
            diff.emplace_back(abs(curr - prev));
            prev = curr;
        }
        sort(diff.begin(), diff.end());
        for (int i = 0; i < diff.size(); ++i)
        {
            if (diff[i] != i + 1)
            {
                flag = true;
                break;
            }
        }
        if (flag)
            puts("Not jolly");
        else
            puts("Jolly");
    }
}