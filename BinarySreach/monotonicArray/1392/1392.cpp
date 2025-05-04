#include <cstdio>
#include <algorithm>
using namespace std;

/*
prefixSum[i]為1到i在strA與strB中相同位置DNA不一樣的總個數
(概念類似prefixSum所以命名之)

[l, r]中錯誤率為
(prefixSum[r] - prefixSum[l - 1]) / (r - l + 1) <= p / 100
移項 => 100 * (prefixSum[r] - prefixSum[l - 1]) <= (r - l + 1) * p
整理 => (l - 1) * p - 100 * prefixSum[l - 1] <= r * p - 100 * prefixSum[r]
    ->位置l - 1              ->位置l - 1    ->位置r               ->位置r       

設key[i] = i * p - 100 * prefixSum[i]
上式即被簡化為key[l - 1] <= key[r] -(1)
因為要找出長度最長的，所以算出key[r]後要去找滿足(1)式最左邊的l - 1
此時總長度為r - l + 1 = r - (l - 1)
*/

struct DNA
{
    int index;
    int key;
};

//單調遞減數列
int monoSize;
DNA monoDec[150005];

int prefixSum[150005];//DNA不一樣的數量(1~n)
char strA[150005];
char strB[150005];
DNA DNAArray[150005];

//透過二分搜在monoDec(單調遞減數列)中找到在DNAArray中小於等於我最左邊的DNA
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