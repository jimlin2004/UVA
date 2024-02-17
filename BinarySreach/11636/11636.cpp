#include <cstdio>
#include <vector>
using namespace std;

vector<int> prefixSum = {1};

int main()
{
    int sum = 0;
    int pow2 = 1;
    for (int i = 1;; ++i)
    {
        sum = prefixSum[i - 1] + pow2;
        pow2 *= 2;
        if (sum > 10001)
        {
            prefixSum.emplace_back(sum);
            break;
        }
        else
            prefixSum.emplace_back(sum);
    }
    int n;
    int count = 0;
    while (scanf("%d", &n) && (n > 0))
    {
        //搜第一個>=的
        int l = 0, r = prefixSum.size() - 1;
        int mid;
        while (l <= r)
        {
            mid = (l + r) / 2;
            if (prefixSum[mid] >= n)
                r = mid - 1;
            else
                l = mid + 1;
        }
        printf("Case %d: %d\n", ++count, l);
    }
    return 0;
}