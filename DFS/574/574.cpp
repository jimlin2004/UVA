#include <cstdio>
#include <vector>
using namespace std;

/*
用dfs去一個個試試看
分: 用跟不用兩個狀態
注: 要處理重複項(方法在下面)
*/

#define maxn 1005

int nums[maxn];
int target, n;
vector<int> subset;
bool hasOutput = false;

void dfs(int sum, int index)
{
    if (target < sum)
        return;
    if (index > n)
        return;

    if (target == sum)
    {
        hasOutput = true;
        printf("%d", subset[0]);
        for (int i = 1; i < subset.size(); ++i)
            printf("+%d", subset[i]);
        puts("");
        return;
    }

    subset.emplace_back(nums[index]);
    dfs(sum + nums[index], index + 1);
    subset.pop_back();
    
    int i;
    //到了這步，後面重複的數字就不用再跑一次了，否則會出現重複項
    for (i = index + 1; i < n; ++i)
        if (nums[i] != nums[i - 1])
            break;
    dfs(sum, i);
}

int main()
{
    while (scanf("%d %d", &target, &n) && target && n)
    {
        hasOutput = false;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &nums[i]);
        }

        printf("Sums of %d:\n", target);

        dfs(0, 0);

        if (!hasOutput)
            puts("NONE");
    }
    return 0;
}