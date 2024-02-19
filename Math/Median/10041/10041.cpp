#include <cstdio>
#include <algorithm>
using namespace std;

//中位數到數線上其他點的距離總和最小
int distances[505];

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &distances[i]);
        }
        sort(distances, distances + n);
        int mid = n / 2;
        int sum = 0;
        for (int i = 0; i < n; ++i)
        {
            sum += abs(distances[i] - distances[mid]);
        }
        printf("%d\n", sum);
    }
    return 0;
}