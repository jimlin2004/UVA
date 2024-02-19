#include <iostream>
#include <string>
using namespace std;

#define max(a, b) (a < b) ? b : a

//題目很長，但就只是求LCS長度

int dp[105][105];
string str1, str2;

int main()
{
    int Case = 0;
    while (getline(cin, str1))
    {
        if (str1[0] == '#')
            break;
        getline(cin, str2);
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
        printf("Case #%d: you can visit at most %d cities.\n", ++Case, dp[str1.size()][str2.size()]);
    }
    return 0;
}