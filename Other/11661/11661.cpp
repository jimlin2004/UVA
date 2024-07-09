#include <iostream>
#include <algorithm>
using namespace std;

/*
    就由右往左以及由左往右搜一遍D~R的最短距離
    如果有出現過Z答案一定是0
*/

int main()
{
    int n;
    while (cin >> n && n)
    {
        string line;
        cin >> line;
        int minDis = 0x3f3f3f3f;
        int lastD = -1;
        for (int i = 0; i < line.size(); ++i)
        {
            if (line[i] == 'D')
                lastD = i;
            else if (line[i] == 'R')
            {
                if (lastD != -1)
                {
                    minDis = min(minDis, (i - lastD));
                }
            }
            else if (line[i] == 'Z')
                minDis = 0;
        }

        lastD = -1;
        for (int i = line.size() - 1; i >= 0; --i)
        {
            if (line[i] == 'D')
                lastD = i;
            else if (line[i] == 'R')
            {
                if (lastD != -1)
                {
                    minDis = min(minDis, (lastD - i));
                }
            }
            else if (line[i] == 'Z')
                minDis = 0;
        }
        if (minDis == 0x3f3f3f3f)
            puts("0");
        else
            printf("%d\n", minDis);
    }
    return 0;
}