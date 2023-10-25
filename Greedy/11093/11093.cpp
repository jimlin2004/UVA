#include <cstdio>
using namespace std;

/*
核心概念:
    從S0出發，到Si時發現到不了，此時[S0, Si-1]是被我們算過每個都是currFuel >= 0的，
    不必從S1再試一次(因為[S0, Si-1]是被我們算過每個都是currFuel >= 0)
    所以我們再度從Si當作起點出發一個個算(概念類似最大子數列)，
    當currFuel < 0代表Si到Sj時不能到，有兩種case:
        1. i < j:
            以Sj為起點再度出發
        2. i >= j:
            由於此狀況時可以知道Sj ~ Si-1(繞一圈)一樣不會成功(因為在選擇Sj為起點前，我們早已算過S0 ~ Sj - 1是不會成功的)
            ，此事實代表我們無法找到解法走完全程
*/

int n;
int fuel[100005];
int cost[100005];
int Case = 1;

void solve()
{
    for (int i = 0; i < n;)
    {
        int currFuel = fuel[i] - cost[i];
        if (currFuel < 0)
        {
            if (i == n - 1)
                break;
            i = (i + 1) % n;
            continue;
        }
        for (int j = (i + 1) % n; ; j = (j + 1) % n)
        {
            currFuel += fuel[j] - cost[j];
            if (currFuel < 0)
            {
                if (i >= j)
                {
                    printf("Case %d: Not possible\n", Case++);
                    return;
                }
                else
                {
                    i = j;
                    break;
                }
            }

            if (i == j)
            {
                printf("Case %d: Possible from station %d\n", Case++, i + 1);
                return;
            }
        }
    }

    printf("Case %d: Not possible\n", Case++);
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
            scanf("%d", &fuel[i]);
        for (int i = 0; i < n; ++i)
            scanf("%d", &cost[i]);
        
        solve();
    }
    return 0;
}