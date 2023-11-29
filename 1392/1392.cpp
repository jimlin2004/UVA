#include <cstdio>
#include <algorithm>
using namespace std;

/*
[l, r]中
錯誤率為
(prefixSum[r] - prefixSum[l - 1]) / (r - l + 1) <= p
移向 => prefixSum[r] - prefixSum[l - 1]

key[i] = i * p - 100 * prefixSum[i]
*/

struct DNA
{
    int index;
    int key;
};

//單調遞減隊列
int monoSize;
DNA monoDec[150005];

int prefixSum[150005];//DNA不一樣的數量(1~n)
char strA[150005];
char strB[150005];
DNA DNAArray[150005];

//透過二分搜在monoDec中找到在DNAArray中小於等於我最左邊的DNA
int binarySearch(int key)
{
    int l = 0, r = monoSize - 1;
    int mid;
    while (l < r)
    {
        mid = (l + r) / 2;
        if (monoDec[mid].key <= key)
            r = mid;
        else
            l = mid + 1;
    }
    return monoDec[l].index;
}

int main()
{
    int n, p;
    
    monoDec[0] = {0, 0};
    while (scanf("%d %d", &n, &p) && (n + p))
    {
        monoSize = 1;

        scanf("%s", strA);
        scanf("%s", strB);
        
        int ans = 0;

        for (int i = 1; i <= n; ++i)
        {
            if (strA[i - 1] != strB[i - 1])
                prefixSum[i] = prefixSum[i - 1] + 1;
            else
                prefixSum[i] = prefixSum[i - 1];
        
            DNAArray[i] = {i, i * p - 100 * prefixSum[i]};
        
            if (DNAArray[i].key < monoDec[monoSize - 1].key)
            {
                monoDec[monoSize++] = DNAArray[i];
            }
            else
            {
                int res = binarySearch(DNAArray[i].key);
                ans = max(ans, DNAArray[i].index - res);
            }
        }
        
        if (ans != 0)
            printf("%d\n", ans);
        else
            puts("No solution.");
    }
    return 0;
}