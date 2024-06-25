#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int getSingleSum(int n)
{
    int res;
    while (n)
    {
        res = 0;
        while (n)
        {
            res += n % 10;
            n /= 10;
        }
        if (res >= 10)
            n = res;
    }
    return res;
}

int main()
{
    string p1;
    string p2;
    while (getline(cin, p1))
    {
        getline(cin, p2);
        int alphabetSum1 = 0;
        int alphabetSum2 = 0;

        for (int i = 0; i < p1.size(); ++i)
        {
            if (isalpha(p1[i]))
            {
                alphabetSum1 += tolower(p1[i]) - 'a' + 1;
            }
        }

        for (int i = 0; i < p2.size(); ++i)
        {
            if (isalpha(p2[i]))
            {
                alphabetSum2 += tolower(p2[i]) - 'a' + 1;
            }
        }

        int singleSum1 = getSingleSum(alphabetSum1);
        int singleSum2 = getSingleSum(alphabetSum2);

        double ratio = (double)min(singleSum1, singleSum2) / max(singleSum1, singleSum2);

        printf("%.2lf %\n", ratio * 100);
    }
    return 0;
}