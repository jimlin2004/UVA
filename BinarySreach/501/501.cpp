#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//O(nlogn)

int nums[30005];
vector<int> blackBox;

int main()
{
    int K;
    int n, m;
    int numIndex;
    int index;
    int u;
    vector<int>::iterator it;
    scanf("%d", &K);
    while (K--)
    {
        blackBox.clear();
        numIndex = 0;
        index = 0;
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; ++i)
            scanf("%d", &nums[i]);
        while (m--)
        {
            scanf("%d", &u);
            while (blackBox.size() < u)
            {
                it = lower_bound(blackBox.begin(), blackBox.end(), nums[numIndex]);
                blackBox.insert(it, nums[numIndex++]);
            }
            printf("%d\n", blackBox[index++]);
        }
        if (K)
            printf("\n");
    }
    return 0;
}