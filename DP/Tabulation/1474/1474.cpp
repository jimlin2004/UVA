#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

struct Node
{
    int location, index;
    bool operator < (const Node& other) const
    {
        return this->location < other.location;
    }
};

// dp[i][j] 代表前i個隊伍，進前j個避難所的最小距離總和
long long dp[4005][4005]; 
bool path[4005][4005];
Node shelters[4005];
Node teams[4005];
int res[4005];
int n, m;

const long long INF = 0x3f3f3f3f3f3f3f3f;

/*
    dp轉移式:
        由於最後一個隊伍永遠去最後一個避難所會是最好的
        所以dp[i][j]: 只考慮前i個隊伍及前j隊時最小距離總和
        因此dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j]) + abs(teams[i].location - shelters[j].location)
        其中dp[i - 1][j - 1]: 不包含隊伍i(前i - 1個隊伍)只考慮前j - 1所避難所的最小
        dp[i - 1][j]: 不包含隊伍i(前i - 1個隊伍)只考慮前j所避難所的最小

        由於dp[i]只與dp[i - 1]有關，所以可以進一步空間壓縮
*/

void solve()
{
    memset(dp, 0x3f, sizeof(dp));
    memset(path, false, sizeof(path));
    sort(teams + 1, teams + n + 1);
    sort(shelters + 1, shelters + m + 1);

    dp[0][0] = 0;

    for (int j = 1; j <= m; ++j)
    {
        for (int i = j; i <= n; ++i)
        {
            if (dp[i - 1][j - 1] <= dp[i - 1][j])
            {
                dp[i][j] = dp[i - 1][j - 1] + abs(teams[i].location - shelters[j].location);
                path[i][j] = true;
            }
            else
            {
                dp[i][j] = dp[i - 1][j] + abs(teams[i].location - shelters[j].location);
                path[i][j] = false;
            }
        }
    }

    //此處第i個team與第j個shelter指的是location由小排到大的i、j
    //由於path[i][j]相當於在dp[i][j]時是否僅第i個team去到第j個shelter，
    //由後到前，利用currentShelter(目前第幾個shelter)，currentTeam(目前是第幾個team要找path)
    //currentShelter -= path[currentTeam][currentShelter] 實現維護currentShelter的效果
    //當currentShelter - 1時代表目前是第一個進入第currentShelter的team
    //所以自第一個team到第currentTeam - 1個team會是在前currentShelter - 1的shelter裡
    int currentShelter = m;
    for (int currentTeam = n; currentTeam > 0 && currentShelter > 0; --currentTeam)
    {
        res[teams[currentTeam].index] = shelters[currentShelter].index;
        currentShelter -= path[currentTeam][currentShelter];
    }

    printf("%lld\n", dp[n][m]);
    for (int i = 1; i < n; ++i)
        printf("%d ", res[i]);
    printf("%d\n", res[n]);
}

int main()
{
    while (scanf("%d", &n) != EOF)
    {
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &teams[i].location);
            teams[i].index = i;
        }
        scanf("%d", &m);
        for (int i = 1; i <= m; ++i)
        {
            scanf("%d", &shelters[i].location);
            shelters[i].index = i;
        }

        solve();
    }
    return 0;
}