#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define maxn 1000005

//用前綴和去檢查是否都是0或1

int prefixSum[maxn];
char input[maxn];

int main()
{
    prefixSum[0] = 0;
    int Case = 0;
    while (scanf("%s", &input) != EOF)
    {
        int size = strlen(input);
        for (int i = 1; i <= size; ++i)
        {
            prefixSum[i] = prefixSum[i - 1] + (input[i - 1] - '0');
        }
        int q;
        scanf("%d", &q);
        printf("Case %d:\n", ++Case);
        while (q--)
        {
            int i, j;
            scanf("%d %d", &i, &j);
            ++i, ++j;
            int l = min(i, j);
            int r = max(i, j);
            int sum = prefixSum[r] - prefixSum[l - 1];
            puts(((sum == r - l + 1) || (sum == 0)) ? "Yes" : "No");
        }
    }
    return 0;
}