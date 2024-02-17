#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

//注: 用cin不行，要用getline
//LCS靶題

int dp[1005][1005];

int main()
{
    string str1, str2;
    while (getline(cin, str1))
    {
        getline(cin, str2);
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= str1.size(); ++i)
        {
            for (int j = 1; j <= str2.size(); ++j)
            {
                if (str1[i - 1] == str2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        cout << dp[str1.size()][str2.size()] << '\n';
    }
    return 0;
}